'use strict';

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

function autolink(t) {
  var l;
  var i = t.indexOf('](');
  if (!t.indexOf('[') && (i > 0) && (t.charAt(t.length - 1) === ')')) {
    l = String_substring(t, 1, i);
    t = String_substring(t, i + 2, t.length - 1);
    t = '<a href="' + t + '">' + l + '</a>';
  } else if ((0 > t.indexOf(' ')) && (!t.indexOf('http://') || !t.indexOf('https://'))) {
    t = '<a href="' + t + '" target=_blank>' + t + '</a>';
  }
  return t;
}

function gemtext2htmBody(t, pr) {
  var title = '';
  var first = '';
  var desc = '';
  var o = '';
  var nl = String.fromCharCode(10);
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
        o = o + '<ul>';
      }
      literal = autolink(literal);
      o = o + '<li>' + literal + '</li>';
      inList = 1;
    } else {
      if (inList) {
        o = o + '</ul>';
        inList = 0;
      }
      if (literal = consume(line, '###', 0)) {
        desc = desc + ' ' + literal;
        line = genId(literal);
        o = o + '<a href="#' + line + '" name="' + line + '"><h3 id="' + line + '">' + literal + '</h3></a>';
      } else if (literal = consume(line, '##', 0)) {
        desc = desc + ' ' + literal;
        line = genId(literal);
        o = o + '<a href="#' + line + '" name="' + line + '"><h2 id="' + line + '">' + literal + '</h2></a>';
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
        o = o + '<a href="' + line + '">' + literal + '</a>';
      } else if (line === '```') {
        o = o + '<pre>';
        while ((lin.length > (i = i + 1)) && ((line = escapeHtml(lin[i], 1)) !== '```')) {
          o = o + line + nl;
        }
        o = o + '</pre>';
      } else {
        literal = escapeHtml(line, 1);
        line = autolink(literal);
        if ((literal === line) && !first) {
          first = literal;
        }
        o = o + line + '<p>';
      }
    }
  }
  escapeHtmlStatic = undefined;
  if (!title) {
    title = first;
    first = '';
  }
  desc = first + desc;
  if (inList) {
    o = o + '</ul>';
  }
  pr.title = title;
  pr.desc = desc;
  return o;
}

function gemtext2htmFile(t, name) {
  var pr = new Object;
  var o = gemtext2htmBody(t, pr);
  var title = pr.title;
  var desc = pr.desc;
  pr = undefined;
  var root;

  if (!title) {
    title = getBasename(name);
  }
  title = truncateAtWord(title, 1024);
  if (desc) {
    desc = truncateAtWord(desc, 2048);
    desc = '<meta property="og:description" content="' +
      desc +
      '" name="description">';
  }

  if (name !== 'README.md') {
    root = getRelativeRoot(name);
    o = o + '<h2>Navigation</h2><ul><li><a href="' + root + '">Back to gemiweb0</a></li></ul>';
  }

  o = '<!DOCTYPE html><html lang=en><head><meta charset="utf-8"><title>' +
    title +
    '</title><link rel="shortcut icon" type="image/png" href="/gemiweb0/favicon.ico"><meta property="og:image" content="/gemiweb0/favicon.ico"><meta name=viewport content="width=device-width, initial-scale=1">' +
    desc +
    '</head><body>' +
    o +
    '</body></html>';
  return o;
}

var fs = require('fs');

function init() {
  process.stdin.on('data', function(name) {
    process.stdin.removeAllListeners(['data']);
    process.stdin.pause();
    name = String_trim('' + name);
    fs.readFile(name, function(e, d) {
      if (e) {
        console.log(name + ': ' + e);
      } else {
        console.log(gemtext2htmFile('' + d, name));
      }
    });
  });
}

init();
