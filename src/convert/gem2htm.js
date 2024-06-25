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

function escapeHtml(s) {
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

    if (n === 34) {
      c = '&quot;';
    } else if (n === 38) {
      c = '&amp;';
    } else if (n === 39) {
      c = '&apos;';
    } else if (n === 60) {
      c = '&lt;';
    } else if (n === 62) {
      c = '&gt;';
    }
    o = o + c;
  }
}

function consume(s, pre) {
  if (s.indexOf(pre)) {
    return '';
  }
  return escapeHtml(String_trim(String_substring(s, pre.length, s.length)));
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
  var n = lin.length;
  var l;
  var p;
  var j;
  var inList = 0;
  while (n > (i = i + 1)) {
    l = lin[i];
    if (p = consume(l, '*')) {
      if (!inList) {
        o = o + '<ul>';
      }
      l = autolink(p);
      o = o + '<li>' + l + '</li>';
      inList = 1;
    } else {
      if (inList) {
        o = o + '</ul>';
        inList = 0;
      }
      if (p = consume(l, '###')) {
        desc = desc + ' ' + p;
        l = genId(p);
        o = o + '<a href="#' + l + '" name="' + l + '"><h3 id="' + l + '">' + p + '</h3></a>';
      } else if (p = consume(l, '##')) {
        desc = desc + ' ' + p;
        l = genId(p);
        o = o + '<a href="#' + l + '" name="' + l + '"><h2 id="' + l + '">' + p + '</h2></a>';
      } else if (p = consume(l, '#')) {
        if (!title) {
          title = p;
        }
        o = o + '<h1>' + p + '</h1>';
      } else if (p = consume(l, '>')) {
        o = o + '<blockquote>' + p + '</blockquote>';
      } else if (p = consume(l, '=>')) {
        j = l.indexOf(' ');
        if (0 > j) {
          l = p;
        } else {
          l = String_substring(p, 0, j);
          p = String_substring(p, j + 1, p.length);
        }
        o = o + '<a href="' + l + '">' + p + '</a>';
      } else if (l === '```') {
        o = o + '<pre>';
        while ((n > (i = i + 1)) && ((l = escapeHtml(lin[i])) !== '```')) {
          o = o + l + nl;
        }
        o = o + '</pre>';
      } else {
        p = escapeHtml(l);
        l = autolink(p);
        if ((p === l) && !first) {
          first = p;
        }
        o = o + l + '<p>';
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

  if (!title) {
    title = getBasename(name);
  }
  title = String_substring(title, 0, 1024);
  if (desc) {
    desc = String_substring(desc, 0, 1024);
    desc = '<meta property="og:description" content="' +
      desc +
      '" name="description">';
  }

  o = '<!DOCTYPE html><html lang=en><head><meta charset=utf-8><title>' +
    title +
    '</title><link rel="shortcut icon" type=image/gif href=/gemiweb0/favicon.ico><meta property="og:image" content="https://bkil.gitlab.io/gemiweb0/favicon.ico"><meta name=viewport content="width=device-width, initial-scale=1">' +
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
