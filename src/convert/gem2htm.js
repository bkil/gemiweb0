'use strict';
var st = new Object;

// JS1
function strEqual(u, v) {
  return !(u.length - v.length) && !u.indexOf(v);
}

// JS1
function parseIntPlus(s) {
  if (!strEqual(typeof parseInt, 'undefined')) {
    return parseInt(s);
  }
  var k = NaN;
  var i = -1;
  var c;
  while (s.length > (i = i + 1)) {
    c = s.charCodeAt(i) - 48;
    if ((0 > c) || (c > 9)) {
      return k;
    }
    if (!i) {
      k = 0;
    }
    k = (k * 10) + c;
  }
  return k;
}

// JS1
function String_substring(th, from, to) {
  if (th.substring) {
    return th.substring(from, to);
  }
  var o = '';
  var c;
  if (to > th.length) {
    to = th.length;
  }
  from = from - 1;
  to = to - 1;
  while (to > from) {
    c = th.charAt(from = from + 1);
    o = o + c;
  }
  return o;
}

// JS1
function String_lastIndexOf(th, c) {
  if (th.lastIndexOf) {
    return th.lastIndexOf(c);
  }
  var i = th.length - 1;
  var n = c.charCodeAt(0);
  while ((i >= 0) && (th.charCodeAt(i) !== n)) {
    i = i - 1;
  }
  return i;
}

// ES1, NS3
function String_split(th, d) {
  if (th.split) {
    return th.split(d);
  }
  var a = new Array;
  var j = 0;
  var from = 0;
  var i = th.indexOf(d, from);
  while (i >= 0) {
    a[j] = String_substring(th, from, i);
    j = j + 1;
    from = i + d.length;
    i = th.indexOf(d, from);
  }
  a[j] = String_substring(th, from, th.length);
  return a;
}

// ES5
function String_trim(th) {
  if (th.trim) {
    return th.trim();
  }
  function isWs(i) {
    var n = th.charCodeAt(i);
    return (n === 32) || (n === 9) || (n === 10);
  }
  var i = 0;
  while ((i < th.length) && isWs(i)) {
    i = i + 1;
  }
  var j = th.length - 1;
  while ((j >= i) && isWs(j)) {
    j = j - 1;
  }
  return String_substring(th, i, j + 1);
}

function countMatch(s, d) {
  var j = 0;
  var i = -1;
  while ((i = s.indexOf(d, i + 1)) >= 0) {
    j = j + 1;
  }
  return j;
}

function truncateAtWord(s, n) {
  var o = String_substring(s, 0, n);
  if (s.length > n) {
    var i = String_lastIndexOf(o, ' ');
    if (i > 0) {
      o = String_substring(o, 0, i);
    }
  }
  return o;
}

function getRelativeRoot(file) {
  var s = '';
  var i = countMatch(file, '/') + 1;
  while (i = i - 1) {
    s = s + '../';
  }
  if (!s) {
    s = '.';
  }
  return s;
}

function getBasename(file) {
  var i = String_lastIndexOf(file, '/');
  if (i >= 0) {
    file = String_substring(file, i + 1, file.length);
  }

  i = String_lastIndexOf(file, '.');
  if (i >= 0) {
    file = String_substring(file, 0, i);
  }
  return file;
}

var escapeHtmlStatic;

function escapeHtmlInit() {
  if (escapeHtmlStatic) {
    return 0;
  }
  var zero = String.fromCharCode(0);
  var i = -1;
  escapeHtmlStatic = '';
  while (127 > (i = i + 1)) {
    if ((i === 34) || (i === 38) || (i === 39) || (i === 60) || (i === 62) || (i < 1)) {
      escapeHtmlStatic = escapeHtmlStatic + zero;
    } else {
      escapeHtmlStatic = escapeHtmlStatic + '1';
    }
  }
}

function escapeHtml(s, isBody) {
  escapeHtmlInit();
  var o = '';
  var i = -1;
  var n;
  var c;
  var y = escapeHtmlStatic;
  while (1) {
    c = s.charAt(i = i + 1);
    while (y.charCodeAt(n = c.charCodeAt(0))) {
      o = o + c;
      c = s.charAt(i = i + 1);
    }
    if (isNaN(n)) {
      return o;
    }

    if (n === 38) {
      c = '&amp;';
    } else if (n === 60) {
      c = '&lt;';
    } else if (n === 62) {
      c = '&gt;';
    } else if (!isBody) {
      if (n === 34) {
        c = '&quot;';
      } else if (n === 39) {
        c = '&apos;';
      }
    }
    o = o + c;
  }
}

function consume(s, pre, isBody) {
  if (s.indexOf(pre)) {
    return '';
  }
  return escapeHtml(String_trim(String_substring(s, pre.length, s.length)), isBody);
}

function genId(s) {
  var i = -1;
  var o = '';
  var n;
  var c;
  while (s.length > (i = i + 1)) {
    n = s.charCodeAt(i);
    if (n === 32) {
      c = '-';
    } else {
      c = s.charAt(i);
    }
    o = o + c;
  }
  return o;
}

var nl = String.fromCharCode(10);

function makeLink0(u, l) {
  return '<a href="' + u + '" target=_blank>' + l + '</a>';
}

function wrapIf(s, x, y) {
  s = '' + s;
  if (s) {
    return x + s + y;
  }
  return '';
}

function makeLink(u, l, nested) {
  var k = u;
  var i = u.indexOf('#');
  if (i >= 0) {
    k = String_substring(u, 0, i);
  }
  var o = st.ix[k];
  if (!o || (nested && (u !== l))) {
    return makeLink0(u, l);
  }

  var name = u;
  i = String_lastIndexOf(name, '/');
  if (i >= -1) {
    name = String_substring(name, i + 1, name.length);
  }
  i = name.indexOf('.');
  if (i >= -1) {
    name = String_substring(name, 0, i);
  }
  var time = o[4];
  if (o[6]) {
    time = o[6] + '/' + time;
  }
  var kb = parseIntPlus(o[2]);
  if (isNaN(kb)) {
    kb = '';
  } else {
    kb = (((kb + 1024) / 1024) | 0) + ' kB';
  }
  var title = kb + ' | ' + time + ' | ' + name;
  if (o[0]) {
    title = o[0] + ' | ' + title;
  }

  if (nested) {
    return makeLink0(u, title);
  }
  if (u !== l) {
    return makeLink0(u, l) + nl +
      wrapIf(o[0], '<blockquote>', '</blockquote>' + nl) +
      wrapIf(o[1], '<blockquote>', '</blockquote>' + nl) +
      '<blockquote>' + kb + ' | ' + time + '</blockquote>';
  }
  if (o[0]) {
    l = o[0];
  }
  return makeLink0(u, l) + nl +
    wrapIf(o[1], '<blockquote>', '</blockquote>' + nl) +
    '<blockquote>' + kb + ' | ' + time + ' | ' + name + '</blockquote>';
}

function autolink(t, nested) {
  var l;
  var i = t.indexOf('](');
  if (!t.indexOf('[') && (i > 0) && (t.charAt(t.length - 1) === ')')) {
    l = String_substring(t, 1, i);
    t = makeLink(String_substring(t, i + 2, t.length - 1), l, nested);
  } else if ((0 > t.indexOf(' ')) && (!t.indexOf('http://') || !t.indexOf('https://'))) {
    t = makeLink(t, t, nested);
  }
  return t;
}

function gemtext2htmBody(t, pr) {
  var title = '';
  var first = '';
  var desc = '';
  var pretoc = '';
  var toc = '';
  var o = nl;
  var lin = String_split(t, nl);
  var i = -1;
  var line;
  var literal;
  var j;
  var inList = 0;
  while (lin.length > (i = i + 1)) {
    line = lin[i];
    if (literal = consume(line, '*', 1)) {
      if (!inList) {
        o = o + '<ul>' + nl;
      }
      literal = autolink(literal, 1);
      o = o + '<li>' + literal + '</li>';
      inList = 1;
    } else {
      if (inList) {
        o = o + '</ul>' + nl;
        inList = 0;
      }
      if (literal = consume(line, '###', 0)) {
        if (!pretoc) {
          pretoc = o;
          o = '';
        }
        if (desc) {
          desc = desc + '; ';
        }
        desc = desc + literal;
        line = genId(literal);
        o = o + '<a href="#' + line + '" name="' + line + '"><h3 id="' + line + '">' + literal + '</h3></a>';
        toc = toc + '<li><a href="#' + line + '"> &nbsp; ' + literal + '</a></li>' + nl;
      } else if (literal = consume(line, '##', 0)) {
        if (!pretoc) {
          pretoc = o;
          o = '';
        }
        if (desc) {
          desc = desc + '; ';
        }
        desc = desc + literal;
        line = genId(literal);
        o = o + '<a href="#' + line + '" name="' + line + '"><h2 id="' + line + '">' + literal + '</h2></a>';
        toc = toc + '<li><a href="#' + line + '">' + literal + '</a></li>' + nl;
      } else if (literal = consume(line, '#', 0)) {
        if (!title) {
          title = literal;
        }
        o = o + '<h1>' + literal + '</h1>';
      } else if (literal = consume(line, '>', 1)) {
        o = o + '<blockquote>' + literal + '</blockquote>';
      } else if (literal = consume(line, '=>', 0)) {
        j = line.indexOf(' ');
        if (0 > j) {
          line = literal;
        } else {
          line = String_substring(literal, 0, j);
          literal = String_substring(literal, j + 1, literal.length);
        }
        literal = makeLink(line, literal, 0);
        o = o + literal;
      } else if (line === '```html') {
        while ((lin.length > (i = i + 1)) && ((line = lin[i]) !== '```')) {
          o = o + line + nl;
        }
      } else if (line === '```') {
        o = o + '<pre>';
        while ((lin.length > (i = i + 1)) && ((line = escapeHtml(lin[i], 1)) !== '```')) {
          o = o + line + nl;
        }
        o = o + '</pre>';
      } else {
        literal = escapeHtml(line, 1);
        line = autolink(literal, 0);
        if ((literal === line) && !first) {
          first = literal;
        }
        o = o + line + '<p>';
      }
    }
    o = o + nl;
  }
  escapeHtmlStatic = undefined;
  if (!title) {
    title = first;
    first = '';
  }
  if (first) {
    if (desc) {
      desc = first + '; ' + desc;
    } else {
      desc = first;
    }
  }
  if (inList) {
    o = o + '</ul>' + nl;
  }
  if (toc) {
    toc = '<ul>' + nl + toc + '</ul>' + nl;
  }
  o = pretoc + toc + o;
  pr.title = title;
  pr.desc = desc;
  return o;
}

function parseIndex(t) {
  var o = new Object;
  if (!t) {
    return o;
  }
  var l = String_split(t, nl);
  var n = l.length;
  var u;
  var r;
  var i = -1;
  while (n > (i = i + 3)) {
    r = String_split(l[i-2], ' ');
    u = r[0];
    r[0] = l[i - 1];
    r[1] = l[i];
    o[u] = r;
  }
  return o;
}

function gemtext2htmFile(t, name) {
  var pr = new Object;
  var o = gemtext2htmBody(t, pr);
  var title = pr.title;
  var desc = pr.desc;
  pr = undefined;
  var root;
  var basename = getBasename(name);

  if (!title) {
    title = baseName;
  }
  title = truncateAtWord(title, 1024);
  if (desc) {
    desc = truncateAtWord(desc, 2048);
    desc = '<meta property="og:description" content="' +
      desc +
      '" name="description">';
  }

  var pre = 'https://bkil.gitlab.io/gemiweb0/';
  var url = pre;
  if (name !== 'README.md') {
    url = url + basename + '.html';
    root = getRelativeRoot(name);
    o = o + '<h2>Navigation</h2><ul><li><a href="' + root + '">Back to gemiweb0</a></li></ul>';
  }

  o = '<!DOCTYPE html>' + nl +
    '<html lang=en prefix="og: http://ogp.me/ns#">' + nl +
    '<head>' + nl +
    '<meta charset="utf-8">' + nl +
    '<meta http-equiv=content-type content="text/html; charset=UTF-8">' + nl +
    '<meta http-equiv=x-content-type-options content=nosniff>' + nl +
    '<title>' +
    title +
    '</title>' + nl +
    '<link rel="shortcut icon" href="/gemiweb0/favicon.ico">' + nl +
    '<meta property="og:title" content="' + title + '">' + nl +
    '<meta property="og:type" content="article">' + nl +
    '<meta property="og:url" content="' + url + '">' + nl +
    '<meta property="og:image" content="' + pre + 'gemiweb0-avatar.png">' + nl +
    '<meta name=author content=bkil.hu>' + nl +
    '<meta name=viewport content="width=device-width, initial-scale=1">' + nl +
    '<meta name=referrer content=unsafe-url>' + nl +
    '<meta http-equiv=x-dns-prefetch-control content=off>' + nl +
    "<meta name=color-scheme content='light dark'>" + nl +
    desc + nl +
    '<style>' + nl +
    ':target { border-style: solid; }' + nl +
    'blockquote { border-left: solid; padding-left: 1em; }' + nl +
    '</style>' + nl +
    '</head>' + nl +
    '<body>' +
    o +
    '</body>' + nl +
    '</html>';
  return o;
}

var fs = require('fs');

function processInput(files) {
  files = String_split(String_trim('' + files), nl);
  if (files.length - 2) {
    console.log('usage: [file-index.csv] [input.md]');
    return 0;
  }
  var ixn = files[0];
  var md  = files[1];
  fs.readFile(ixn, function(e, ixd) {
    st.ix = parseIndex(ixd);
    fs.readFile(md, function(e, d) {
      if (e) {
        console.log(md + ': ' + e);
      } else {
        console.log(gemtext2htmFile('' + d, md));
      }
    });
  });
}

function init() {
  var b = '';
  process.stdin.on('end', function(d) {
    processInput(b);
    process.stdin.pause();
    process.stdin.removeAllListeners(['data', 'end']);
  });
  process.stdin.on('data', function(d) {
    b = b + d;
  });
}

init();
