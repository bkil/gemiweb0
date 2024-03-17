'use strict';

// Copyright (C) 2023-2024 bkil.hu
// Refer to the GNU GPL v2 in LICENSE for terms

// "\n"
var nl = String.fromCharCode(10);

var safeHtml = new Object;

function fillSafeHtml() {
  if (safeHtml.s) {
    return 0;
  }
  var zero = String.fromCharCode(0);
  var i = 0;
  var safe = '';
  while (i < 127) {
    if ((i === 34) || (i === 38) || (i === 39) || (i === 60) || (i === 62) || (i < 32)) {
      safe = safe + zero;
    } else {
      safe = safe + '1';
    }
    i = i + 1;
  }
  safeHtml.s = safe;
}

function escapeHtml(h) {
  fillSafeHtml();
  var s = safeHtml.s;
  var o = '';
  var i = -1;
  var n;
  var c;
  while (1) {
    c = h.charAt(i = i + 1);
    while (s.charCodeAt(n = c.charCodeAt(0))) {
      o = o + c;
      c = h.charAt(i = i + 1);
    }
    if (isNaN(n)) {
      return o;
    }
    if (n > 126) {
      o = o + c;
    } else if (n === 34) {
      o = o + '&quot;';
    } else if (n === 38) {
      o = o + '&amp;';
    } else if (n === 39) {
      o = o + '&apos;';
    } else if (n === 60) {
      o = o + '&lt;';
    } else if (n === 62) {
      o = o + '&gt;';
    }
  }
}

function httpGet(host, port, path, ok, err) {
  var crlf = String.fromCharCode(13) + nl;
  var net = require('node:net');
  var s = new Object;
  s.buf = '';

  function onConnect(client) {
    client.on('data', function(d) {
      s.buf = s.buf + d;
    });

    client.on('end', function() {
      var i = s.buf.indexOf(crlf + crlf);
      if ((i < 0) || ((s.buf.indexOf('HTTP/1.0 200') !== 0) && (s.buf.indexOf('HTTP/1.1 200') !== 0))) {
        err('non-200 response');
      } else {
        ok(s.buf.substring(i + 4), 200);
      }
    });

    client.write(
      'GET ' + path + ' HTTP/1.1' + crlf +
      'Host: ' + host + ':' + port + crlf +
      'Connection: close' + crlf +
      crlf
    );
  }

  var opt = new Object;
  opt.host = host;
  opt.port = port;
  var client = net.createConnection(opt);
  client.on('error', function() {
    err('network error');
  });
  client.on('connect', onConnect);
}

function newURL(url) {
  var o = new Object;
  o.protocol = undefined;
  o.hostname = '';
  o.port = '';
  o.pathname = '/';
  o.search = '';
  o.hash = '';

  var i = url.indexOf('//');
  if (i < 0) {
    return o;
  }
  o.protocol = url.substring(0, i);

  i = i + 2;
  var j;
  if (o.protocol !== 'file:') {
    j = url.indexOf('/', i);
    if (j < 0) {
      o.hostname = url.substring(i);
      return o;
    }
    o.hostname = url.substring(i, j);
    i = j;

    j = o.hostname.indexOf(':');
    if (j >= 0) {
      o.port = o.hostname.substring(j + 1);
      o.hostname = o.hostname.substring(0, j);
    }
  }

  j = url.indexOf('#');
  if (j >= 0) {
    o.hash = url.substring(j);
    url = url.substring(0, j);
  }

  j = url.indexOf('?');
  if (j >= 0) {
    o.search = url.substring(j);
    url = url.substring(0, j);
  }

  o.pathname = url.substring(i);
  return o;
}

function readLocalFile(pathname, onload, onerror) {
  var fs = require('fs');
  fs.readFile(pathname, function (e, d) {
    if (e) {
      onerror('fetch local file failed: ' + e);
    } else {
      onload('' + d);
    }
  });
}

function newFetch(location) {
  if (typeof fetch === 'function') {
    return fetch(location);
  }

  return function(url) {
    function then(onload, onerror) {
      var u = newURL(url);
      if (!u.protocol) {
        var orig = newURL(location.href);
        u.protocol = orig.protocol;
        u.hostname = orig.hostname;
        u.port = orig.port;
        if (u.pathname.charAt(0) !== '/') {
          var i = orig.pathname.lastIndexOf('/');
          if (i >= 0) {
            u.pathname = orig.pathname.substring(0, i) + '/' + u.pathname;
          }
        }
      }

      var wrappedOnload = function(d) {
        function getText() {
          return '' + d;
        }
        var o = new Object;
        o.text = getText;
        onload(o);
      };
      if (u.protocol === 'http:') {
        var port = 80;
        if (u.port.length) {
          port = parseInt(u.port);
          if (isNaN(port)) {
            onerror('invalid port');
            return undefined;
          }
        }
        httpGet(u.hostname, port, u.pathname + u.search, wrappedOnload, onerror);
      } else if (u.protocol === 'file:') {
        readLocalFile(u.pathname, wrappedOnload, onerror);
      } else {
        onerror('unknown protocol');
      }
    }
    var o = new Object;
    o.then = then;
    return o;
  }
}

function eval2To(j, prog) {
  function eval2To0(self, j, prog) {
    var g = j.vars;
    var o;
    try {
      o = eval2(g, prog);
    } catch (e) {
      var msg = '<pre>Exception running JavaScript:' + nl + e + '</pre>';
      if (j.d.documentWritten === undefined) {
        j.d.documentWritten = '';
      }
      j.d.documentIsOpen = 1;
      j.d.documentWritten = j.d.documentWritten + msg;
    }
    var f = g['.onTimeout'];
    var t = g['.timeoutMs'];
    if (t && (t < 1000)) {
      t = 1000;
    }
    g['.onTimeout'] = undefined;
    g['.timeoutMs'] = 0;
    if (f && !j.shutdown) {
      setTimeout(function() {
        self(self, j, f);
        var d = j.d;
        if (d.documentWritten !== undefined) {
          j.updateHtml(j, d.documentWritten);
          d.documentWritten = undefined;
        }
      }, t);
    }
    return o;
  }

  return eval2To0(eval2To0, j, prog);
}

function isWs(c) {
  return (c === ' ') || (c.charCodeAt(0) === 10)
}

function copyLiteral(s) {
  var o = s['o'];
  if (!s['pushTag']) {
    if (!s['inline']) {
      if (s['br']) {
        o = o + nl;
      } else {
        o = o + (nl + nl);
      }
      s['inline'] = 1;
    }
    s['br'] = 0;
  }

  var h = s['h'];
  var c = h[s['i']];
  var b;
  s['i'] = s['i'] + 1;
  if (!s['ctx']) {
    b = isWs(c);
    if (!b) {
      o = o + c;
    } else if (!s['lastWs']) {
      o = o + ' ';
    }
    s['lastWs'] = b;
  } else if (s.ctx === 'style') {
  } else  {
    o = o + c;
  }
  s['o'] = o;
}

function copyText(s) {
  if (s['textContent'] === undefined) {
    copyLiteral(s);
  } else {
    var h = s['h'];
    s['textContent'] = s['textContent'] + h[s['i']];
    s['i'] = s['i'] + 1;
  }
}

function more(s) {
  var h = s['h'];
  return s['i'] < h.length;
}

function accFun(s, fun) {
  var h = s['h'];
  var b;
  if (more(s) && fun(h[s['i']])) {
    s['i'] = s['i'] + 1;
    b = 1;
  }
  return b;
}

function accWhileFun(s, fun) {
  var h = s['h'];
  var o;
  if (more(s)) {
    o = '';
    while (more(s) && fun(h[s['i']])) {
      o = o + h[s['i']];
      s['i'] = s['i'] + 1;
    }
  }
  return o;
}

function acc1(s, expect) {
  return accFun(s, function(c) { return c === expect });
}

function accWs(s) {
  return accFun(s, isWs);
}

function getLowerChar(s) {
  var c = s.charCodeAt(0);
  if (((c >= 97) && (c <= 122)) || ((c >= 48) && (c <= 57))) {
    return s;
  } else if ((c >= 65) && (c <= 90)) {
    return String.fromCharCode(c + 32);
  } else {
    return undefined;
  }
}

function isWChar(c) {
  return (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) || ((c >= '0') && (c <= '9'));
}

function readWhileFun(s, fun) {
  var h = s['h'];
  var o;
  if (more(s)) {
    o = '';
    var b = 1;
    var c;
    while (b) {
      b = 0;
      c = fun(h[s['i']]);
      if (c !== undefined) {
        o = o + c;
        s['i'] = s['i'] + 1;
        b = more(s);
      }
    }
  }
  return o;
}

function readLW(s) {
  return readWhileFun(s, getLowerChar);
}

function readWord(s) {
  return accWhileFun(s, isWChar);
}

function readQuoted(s) {
  var o;
  if (acc1(s, '"')) {
    o = accWhileFun(s, function(c) { return c !== '"' });
    acc1(s, '"');
  } else if (acc1(s, "'")) {
    o = accWhileFun(s, function(c) { return c !== "'" });
    acc1(s, "'");
  } else {
    o = accWhileFun(s, function(c) { return (c !== ' ') && (c !== '>')});
  }
  return o;
}

function closeLastTag(j) {
  var s = j['s'];
  var tag = s['pushTag'];
  var attr = s['pushAttr'];
  var t;
  if (tag === 'a') {
    s['o'] = (s['o'] + ' [') + (s['link'] + ']');
    s['link'] = s['link'] + 1;
  } else if (tag === 'pre') {
    s['o'] = s['o'] + (nl + '```');
  } else if (tag === 'textarea') {
    s['default'] = s['textContent'];
  } else if ((tag === 'script') && (s['textContent'] !== undefined)) {
    if (attr['src']) {
      function after(body) {
        eval2To(j, body.text());
      }
      function error(err) {
        if (attr['onerror'] !== undefined) {
          eval2To(j, attr['onerror']);
        } else {
          eval2To(j, s['textContent']);
        }
      }

      var g = newFetch(j.vars.window.location);
      g = g(attr['src']);
      g = g.then(after, error);
    } else {
      eval2To(j, s['textContent']);
    }

    var d = j.d;
    if (d['documentWritten'] !== undefined) {
      var h = s['h'];
      s['h'] = h.substring(0, s['i']) + (d['documentWritten'] + h.substring(s['i']));
      d['documentWritten'] = undefined;
    }
  }

  s['raw'] = 0;
  s['ctx'] = 0;
  s['br'] = 0;
  s['pushTag'] = undefined;
  s['pushAttr'] = undefined;
  s['textContent'] = undefined;
}

function processTag(j, tag, fin, attr) {
  var s = j['s'];
  var ignore;
  var memo = 1;
  var br;
  var inline;
  var displayLi;
  var ctx;
  var raw;
  var needText;
  var t = '';
  if (tag === 'a') {
    if (attr['href']) {
      t = ('=> ' + attr['href']) + ' ';
      var l = s['links'];
      var link = s['link'];
      l[link] = attr['href'];
    }
  } else if (tag === 'blockquote') {
    if (!fin) {
      t = '> ';
    }
  } else if (tag === 'pre') {
    if (!fin) {
      t = '```' + nl;
    }
    ctx = 1;
  } else if (tag === 'title') {
    if (!fin) {
      t = '# ';
    }
    raw = 1;
  } else if (tag === 'h1') {
    if (!fin) {
      t = '# ';
    }
  } else if (tag === 'h2') {
    if (!fin) {
      t = '## ';
    }
  } else if (tag === 'h3') {
    if (!fin) {
      t = '### ';
    }
  } else if (tag === 'form') {
    if (!fin) {
      s['formName'] = attr['name'];
      s['formAction'] = attr['action'];
    }
    ignore = 1;
  } else if (tag === 'input') {
    if (attr['type'] !== 'submit') {
      s['inputName'] = attr['name'];
      s['default'] = attr['value'];
      s['multiLine'] = 0;
    }
    ignore = 1;
  } else if (tag === 'textarea') {
    if (!fin) {
      s['inputName'] = attr['name'];
      s['multiLine'] = 1;
      needText = 1;
    }
    ignore = 1;
    ctx = 1;
    raw = 1;
  } else if (tag === 'li') {
    if (!fin) {
      t = '* ';
    }
    displayLi = 1;
  } else if ((tag === 'script') || (tag === 'style')) {
    needText = 1;
    ctx = 1;
    raw = 1;
  } else if (tag === 'br') {
    br = 1;
    memo = 0;
  } else if (tag === 'div') {
    br = 1;
    memo = 0;
  } else if (tag === 'p') {
    br = 1;
    memo = 0;
  } else {
    memo = 0;
    inline = 1;
    ignore = 1;
  }

  if ((((!br) && (inline && s['inline'])) || ignore) || (!s['o'])) {
  } else if (((displayLi !== s['displayLi']) || (((!displayLi) && (!s['displayLi'])) && ((!br) && ((!inline) || (!s['inline']))))) && (!s['br'])) {
    s['o'] = s['o'] + (nl + nl);
  } else {
    s['o'] = s['o'] + nl;
    if (s['pushTag'] === 'blockquote') {
      s['o'] = s['o'] + '> ';
    }
  }

  if (memo && (!ignore)) {
    closeLastTag(j);
    if (!fin) {
      s['pushTag'] = tag;
      s['pushAttr'] = attr;
    }
  }
  if ((!br) && (!ignore)) {
    s['inline'] = inline;
    s['displayLi'] = displayLi;
  }
  s['br'] = br;
  if ((!fin) && needText) {
    s['textContent'] = '';
  }

  s['o'] = s['o'] + t;

  if (!ignore) {
    s['lastWs'] = 0;
  }

  if (ctx) {
    if (fin) {
      s['ctx'] = 0;
    } else {
      s['ctx'] = tag;
    }
  }

  if (raw) {
    if (fin) {
      s['raw'] = 0;
    } else {
      s['raw'] = tag;
    }
  }
}

function dropToTagEnd(s) {
  while (accFun(s, function(c) { return c !== '>' })) {
  }
  return acc1(s, '>');
}

function parseMeta(s) {
  var i = s['i'];
  var b;
  var found;

  if (acc1(s, '-')) {
    if (acc1(s, '-')) {
      found = 1;
      b = more(s);
      while (b) {
        i = s['i'];
        b = !(acc1(s, '-') && (acc1(s, '-') && acc1(s, '>')));
        if (b) {
          s['i'] = i + 1;
          b = more(s);
        }
      }
    }
  }

  if (!found) {
    s['i'] = i;
    dropToTagEnd(s);
  }
}

function parseTag(j) {
  var s = j['s'];
  var key;
  var val;
  var fin = acc1(s, '/');
  var tag = readLW(s);
  var attr = new Object;
  var b = tag !== undefined;
  while (b) {
    b = 0;
    while (accWs(s)) {
      b = 1;
    }
    if (b) {
      b = 0;
      key = readLW(s);
      if (key !== undefined) {
        val = undefined;
        if (acc1(s, '=')) {
          val = readQuoted(s);
        }
        if (val !== undefined) {
          attr[key] = val;
        } else {
          attr[key] = '';
        }
        b = 1;
      }
    }
  }
  if (acc1(s, '/')) {
    fin = 1;
  }
  dropToTagEnd(s);
  if (tag !== undefined) {
    if (fin && (tag === s['pushTag'])) {
      closeLastTag(j);
    } else {
      processTag(j, tag, fin, attr);
    }
  }
}

function render(j, h) {
  var s = new Object;
  s.h = h;
  s.i = 0;
  s.textContent = undefined;
  s.inline = 1;
  s.lastWs = 1;
  s.o = '';
  s.link = 0;
  s.links = new Object;
  s.formName = undefined;
  s.formAction = undefined;
  s.inputName = undefined;
  s.multiLine = undefined;
  s.default = undefined;
  j['s'] = s;
  var i;
  var k;
  var key;

  while (more(s)) {
    i = s['i'];
    if (acc1(s, '<')) {
      if (acc1(s, '!')) {
        parseMeta(s);
      } else {
        if (s['raw']) {
          k = s['i'];
          key = undefined;
          if (acc1(s, '/')) {
            key = readLW(s);
          }
          if (key === s['raw']) {
            s['i'] = k;
            parseTag(j);
          } else {
            s['i'] = i;
            copyText(s);
          }
        } else {
          parseTag(j);
        }
      }
    } else {
      copyText(s);
    }
  }
  closeLastTag(j);
}

function Document_write(d) {
  return function(x) {
    if (!(d['documentIsOpen'])) {
      d['documentIsOpen'] = 1;
      d['documentWritten'] = x;
    } else if (d['documentWritten'] === undefined) {
      d['documentWritten'] = x;
    } else {
      d['documentWritten'] = s['documentWritten'] + x;
    }
  }
}

function Document_close(d) {
  return function() {
    d['documentIsOpen'] = 0;
  };
}

function setInitState(j, href, html) {
  var d = new Object;
  d['documentWritten'] = '';
  j['d'] = d;

  var l = new Object;
  l.href = href;
  var w = new Object;
  w.location = l;
  var g = new Object;
  g.window = w;
  var e = new Object;
  e.innerHTML = html;
  j['vars'] = g;

  if ((href !== '') || (html !== '')) {
    var doc = new Object;
    doc.documentElement = e;
    doc.write = Document_write(d);
    doc.close = Document_close(d);
    g.document = doc;

    g.require = undefined;
    g.fetch = newFetch(l);
    eval2To(j, libJs.s);
  }
}
function browseData(j, url, html, isFile, brows) {
  var g = j['vars'];
  var w = g['window'];
  var l = w['location'];
  if ((url !== l['href']) && isFile) {
    setInitState(j, url, html);
  } else {
    var d = g['document'];
    var de = d['documentElement'];
    de['innerHTML'] = html;
  }

  var d = j.d;
  d['documentIsOpen'] = 1;
  d['documentWritten'] = undefined;
  render(j, html);
  d['documentIsOpen'] = 0;

  var shw = j['show'];
  var s = j['s'];
  var text = '';
  if (isFile) {
    text = (url + nl) + s['o'];
  } else {
    text = s['o'];
  }

  if (s['multiLine'] === undefined) {
    shw(text, undefined, 0, function(r) {
      if (r === undefined) {
        j.shutdown = 1;
        return 0;
      }
      var links = s['links'];
      if (links[r]) {
        brows(j, links[r], brows);
      }
    });
  } else {
    shw(text, s['default'], s['multiLine'], function(r) {
      if (r === undefined) {
        j.shutdown = 1;
        return 0;
      }
      if (s['formAction']) {
        url = s['formAction'];
      }
      if (s.inputName) {
        if (s.formName) {
          var g = j.vars.window;
          if (!g[s.formName]) {
            g[s.formName] = new Object;
          }
          var n = g[s.formName];
          if (!n[s.inputName]) {
            n[s.inputName] = new Object;
          }
          var o = n[s.inputName];
          o.value = r;
        }

        if (url.indexOf('javascript:') !== 0) {
          var i = url.indexOf('?');
          var arg = (encodeURIComponent(s['inputName']) + '=') + encodeURIComponent(r);
          if (i < 0) {
            url = url + ('?' + arg);
          } else {
            url = url + ('&' + arg); // TODO
          }
        }
      }
      brows(j, url, brows);
    });
  }
}

function browse(j, url, brows) {
  var html;
  if (url.indexOf('javascript:') === 0) {
    html = eval2To(j, decodeURIComponent(url.substring(11)));
    if (typeof html === 'string') {
      browseData(j, url, html, 0, brows);
    } else {
      var d = j.d;
      html = d['documentWritten'];
      if (html !== undefined) {
        browseData(j, url, '' + html, 0, brows);
      }
    }
  } else {
    function after(html) {
      browseData(j, url, html.text(), 1, brows);
    }
    function error(err) {
      var html = "<!DOCTYPE html><html><head><meta charset=utf-8><title>title</title></head><body><h1>404 not found</h1>"  + (escapeHtml(url) + "</body></html>");
      browseData(j, url, html, 1, brows);
    }
    var g = newFetch(j.vars.window.location);
    g = g(url);
    g = g.then(after, error);
  }
}

function getUh() {
  return function(j, html) {
    return browseData(j, j.vars.window.location.href, html, 0, browse);
  };
}

function callMeMaybe(self, acc, multiLine, cb) {
  return function(data) {
    process.stdin.removeAllListeners(['data']);
    if ((data === undefined) || (data === null)) {
      cb(undefined);
    }
    if (multiLine) {
      if (data === '.') {
        if (acc === undefined) {
          acc = '';
        }
        cb(acc);
      } else {
        if (acc !== undefined) {
          data = (acc + nl) + data;
        }
        process.stdin.on('data', self(self, data, multiLine, cb));
      }
    } else {
      cb(data);
    }
  }
}

function show(text, defVal, multiLine, cb) {
  console.log(text);
  var i = process.stdin;
  if (cb === undefined) {
    i.removeAllListeners(['data']);
  } else {
    if (multiLine) {
      console.log('Please type in multiple lines of input terminated with a dot (".")');
    } else {
      console.log('Please type in a single line of input: ');
    }
    if (defVal !== undefined) {
      console.log(' default: ' + defVal);
    }
    i.on('data', callMeMaybe(callMeMaybe, undefined, multiLine, cb));
  }
}

function getInitState() {
  var j = new Object;
  j.shutdown = 0;
  j.show = show;
  setInitState(j, '', '');
  j.updateHtml = getUh();
  return j;
}

function brLibInit() {
  browse(getInitState(), 'file://index.htm', browse);
}
