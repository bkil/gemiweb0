'use strict';

eval((function() {
  var o = new Object;
  var fs = require('fs');
  fs.readFile('lib.js', function(e, d) {
    if (e) {
      console.log(e)
    } else {
      o.d = d
    }
  });
  return o.d;
})());

function eval2To(j, prog) {
  function eval2To0(self, j, prog) {
    var g = j.vars;
    var o = eval2(g, prog);
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

function escapedChar(c) {
  if (c === '&') {
    c = '&amp;';
  } else if (c === '<') {
    c = '&lt;';
  } else if (c === '>') {
    c = '&gt;';
  } else if (c === '"') {
    c = '&quot;';
  } else if (c === "'") {
    c = '&apos;';
  }
  return c;
}

function escaped(x) {
  var o = '';
  var i = 0;
  while (i < x.length) {
    o = o + escapedChar(x[i]);
    i = i + 1;
  }
  return o;
}

function isWs(c) {
  return (c === ' ') || (c.charCodeAt(0) === 10)
}

// "\n"
var nl = String.fromCharCode(10);

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
  if (s.ctx === 'style') {
  } else if (s['ctx']) {
    o = o + c;
  } else {
    b = isWs(c);
    if (!b) {
      o = o + c;
    } else if (!s['lastWs']) {
      o = o + ' ';
    }
    s['lastWs'] = b;
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
      var get = j['get'];
      var body = get(attr['src']);
      if (body === undefined) {
        eval2To(j, s['textContent']);
      } else {
        eval2To(j, body);
      }
    } else {
      eval2To(j, s['textContent']);
    }

    var d = j.d;
    if (d['documentWritten'] !== undefined) {
      var h = s['h'];
      s['h'] = h.substr(0, s['i']) + (d['documentWritten'] + h.substr(s['i']));
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

    var fs = require('fs');
    fs.readFile('lib.js', function(e, lib) {
      if (lib) {
        eval2To(j, lib);
      }
    });
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
    html = eval2To(j, decodeURIComponent(url.substr(11)));
    if (html === undefined) {
      var d = j.d;
      html = d['documentWritten'];
      if (html !== undefined) {
        browseData(j, url, '' + html, 0, brows);
      }
    } else {
      browseData(j, url, '' + html, 0, brows);
    }
  } else {
    var get = j['get'];
    html = get(url);
    if (html === undefined) {
      html = "<!DOCTYPE html><html><head><meta charset=utf-8><title>title</title></head><body><h1>404 not found</h1>"  + (escaped(url) + "</body></html>");
    }
    browseData(j, url, html, 1, brows);
  }
}

function fetchLocal(url) {
  var i = url.indexOf('?');
  if (i >= 0) {
    url = url.substr(0, i);
  }
  var o = new Object;
  var fs = require('fs');
  fs.readFile(url, function (e, d) {
    if (e !== undefined) {
      console.log(('fetch failed: ' + e) + nl);
    } else {
      o.d = d;
    }
  });
  return o.d;
}

function getUh() {
  return function(j, html) {
    return browseData(j, j.vars.window.location.href, html, 0, browse);
  };
}

function callMeMaybe(self, acc, multiLine, cb) {
  return function(data) {
    process.stdin.on('data', undefined);
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
  console.log(text + nl);
  var i = process.stdin;
  if (cb === undefined) {
    i.on('data', undefined);
  } else {
    if (multiLine) {
      console.log('Please type in multiple lines of input terminated with a dot (".")' + nl);
    } else {
      console.log('Please type in a single line of input: ' + nl);
    }
    if (defVal !== undefined) {
      console.log((' default: ' + escaped(defVal)) + nl);
    }
    i.on('data', callMeMaybe(callMeMaybe, undefined, multiLine, cb));
  }
}

function main() {
  var j = new Object;
  j.shutdown = 0;
  j.show = show;
  setInitState(j, '', '');
  j.get = fetchLocal;
  j.updateHtml = getUh();
  browse(j, 'index.htm', browse);
}

main();
