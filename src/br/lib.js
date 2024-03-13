'use strict';

// Copyright (C) 2023 bkil.hu
// Refer to the GNU GPL v2 in LICENSE for terms

// JS1
String.prototype.indexOf2 = String.prototype.indexOf2 || function(c) {
  var i = 0;
  var n = c.charCodeAt(0);
  while ((i < this.length) && (this.charCodeAt(i) !== n)) {
    i = i + 1;
  }
  if (i >= this.length) {
    i = -1;
  }
  return i;
}

String.prototype.lastIndexOf2 = String.prototype.lastIndexOf2 || function(c) {
// JS1
  var i = this.length - 1;
  var n = c.charCodeAt(0);
  while ((i >= 0) && (this.charCodeAt(i) !== n)) {
    i = i - 1;
  }
  return i;
}

// JS1
String.prototype.toUpperCase = String.prototype.toUpperCase || function() {
  var o = '';
  var i = 0;
  while (i < this.length) {
    var c = this.charAt(i);
    var n = c.charCodeAt(0);
    if ((n >= 97) && (n <= 122)) {
      c = String.fromCharCode(n - 32);
    }
    o = o + c;
    i = i + 1;
  }
  return o;
}

// JS1
String.prototype.toLowerCase = String.prototype.toLowerCase || function() {
  var o = '';
  var i = 0;
  while (i < this.length) {
    var c = this.charAt(i);
    var n = c.charCodeAt(0);
    if ((n >= 65) && (n <= 90)) {
      c = String.fromCharCode(n + 32);
    }
    o = o + c;
    i = i + 1;
  }
  return o;
}

// JS1
String.prototype.substring = String.prototype.substring || function(from, to) {
  var o = '';
  if (!(from > 0)) {
    from = 0;
  }
  var i = from;
  var c;
  if (to === undefined) {
    while (i < this.length) {
      c = this.charAt(i);
      o = o + c;
      i = i + 1;
    }
  } else {
    if (!(to > 0)) {
      to = 0;
    }
    if (from > to) {
      i = to;
      to = from;
    }
    while ((i < this.length) && (i < to)) {
      c = this.charAt(i);
      o = o + c;
      i = i + 1;
    }
  }
  return o;
}

// ES3, NS4
String.prototype.substr = String.prototype.substr || function(from, n) {
  if (from < 0) {
    return undefined;
  }
  var o = '';
  var i = from;
  var c;
  if (n === undefined) {
    while (i < this.length) {
      c = this.charAt(i);
      o = o + c;
      i = i + 1;
    }
  } else {
    while (i < this.length) {
      if (n <= 0) {
        return o;
      }
      n = n - 1;
      c = this.charAt(i);
      o = o + c;
      i = i + 1;
    }
  }
  return o;
}

// ES1, NS3
String.prototype.split = String.prototype.split || function(s) {
  var a = new Array;
  if (s === undefined) {
    a[0] = this;
    return a;
  }

  var i = 0;
  if (s === '') {
    while (i < this.length) {
      a[i] = s.charAt(i);
    }
    return a;
  }

  var j = 0;
  var from = 0;
  i = this.indexOf(s, from);
  while (i >= 0) {
    a[j] = this.substring(from, i);
    j = j + 1;
    from = i + s.length;
    i = this.indexOf(s, from);
  }
  a[j] = this.substring(from);
  return a;
}

// ES5
String.prototype.trim = String.prototype.trim || function() {
  var s = this;
  function isWs(i) {
    var n = s.charCodeAt(i);
    return (n === 32) || (n === 9) || (n === 10);
  }
  var i = 0;
  while ((i < s.length) && isWs(i)) {
    i = i + 1;
  }
  var j = s.length - 1;
  while ((j >= i) && isWs(j)) {
    j = j - 1;
  }
  return s.substring(i, j + 1);
};

// ES1, NS3
Array.prototype.join = Array.prototype.join || function(d) {
  if (d === undefined) {
    d = ',';
  }
  var s = '';
  var c;
  if (this.length) {
    c = this[0];
    s = s + c;
    var i = 1;
    while (i < this.length) {
      s = s + d;
      c = this[i];
      s = s + c;
      i = i + 1;
    }
  }
  return s;
}

// ES5
var Object_keys = Object.keys || function(o) {
  var k = new Array;
  var i;
  for (i in o) {
    k[k.length] = i;
  }
  return k;
}

// ES1, NS3
Array.prototype.reverse = Array.prototype.reverse || function() {
  var i = 0;
  var j = this.length - 1;
  var x;
  while (j > i) {
    x = this[i];
    this[i] = this[j];
    this[j] = x;
    i = i + 1;
    j = j - 1;
  }
  return this;
}

if ((typeof JSON === 'undefined') || !JSON.stringify) {
  function JSON_stringify(o) {
    function JSON_stringify_0(f, o) {
      var hex = '0123456789abcdef';
      var bu00 = String.fromCharCode(92) + 'u00';
      function escapeQuote(s) {
        var o = '"';
        var i = 0;
        var c;
        var n;
        while (i < s.length) {
          n = s.charCodeAt(i);
          if (n > 126) {
            return 'null';
          }
          if (((n === 34) || (n === 92)) || (n < 32)) {
            o = ((o + bu00) + hex[n >> 4]) + hex[n & 15];
          } else {
            o = o + s.charAt(i);
          }
          i = i + 1;
        }
        return o + '"';
      }

      var t = typeof o;
      if (t === 'string') {
        return escapeQuote(o);
      } else if (t === 'number') {
        return '' + o;
      } else if ((t === 'object') && (o !== null)) {
        var s = '';
        if (o.length !== undefined) {
          s = s + '[';
          if (o.length) {
            s = s + f(f, o[0]);
            var i = 1;
            while (i < o.length) {
              s = (s + ',') + f(f, o[i]);
              i = i + 1;
            }
          }
          return s + ']';
        } else {
          s = s + '{';
          var rest = 0;
          for (i in o) {
            if (rest) {
              s = s + ',';
            } else {
              rest = 1;
            }
            s = (s + f(f, i)) + (':' + f(f, o[i]));
          }
          return s + '}';
        }
      } else {
        return 'null';
      }
    }

    return JSON_stringify_0(JSON_stringify_0, o);
  }

  if (typeof JSON === 'undefined') {
    var JSON = new Object;
  }
  JSON.stringify = JSON.stringify || JSON_stringify;
}

// ES1, NS3
if (typeof Function === 'undefined') {
  function Function(param, body) {
    return eval((('(function(' + param) + ('){' + body)) + '})')
  }
}

// JS1
if (typeof parseInt === 'undefined') {
  function parseInt(s, b) {
    if (b === undefined) {
      b = 10;
    }
    if (b !== 10) {
      return NaN;
    }
    var k = 0;
    var i = 0;
    while (i < s.length) {
      var c = s.charCodeAt(i);
      if ((c < 48) || (c > 57)) {
        return NaN;
      }
      k = (k * 10) + (c - 48);
      i = i + 1;
    }
    return k;
  }
}

// ES3, NS5?
if (typeof encodeURIComponent === 'undefined') {
  function encodeURIComponent(s) {
    var hex = '0123456789abcdef';
    var o = '';
    var i = 0;
    while (i < s.length) {
      var c = s[i];
      var n = c.charCodeAt(0);
      if (((n >= 44) && (n <= 59)) || ((n >= 64) && (n <= 126))) {
        o = o + c;
      } else if (n < 128) {
        o = ((o + '%') + hex[n >> 4]) + hex[n & 15];
      } else {
        return undefined;
      }
      i = i + 1;
    }
    return o;
  }
}

// ES3, NS5?
if (typeof decodeURIComponent === 'undefined') {
  function decodeURIComponent(s) {
    function getHexDigit(n) {
      if ((n > 47) && (n < 58)) {
        return n - 48;
      } else if ((n > 96) && (n < 103)) {
        return n - 87;
      } else if ((n > 64) && (n < 71)) {
        return n - 55;
      } else {
        return -1;
      }
    }

    var o = '';
    var i = 0;
    var c;
    var n;
    var u;
    var v;
    while (i < s.length) {
      c = s.charAt(i);
      n = c.charCodeAt(0);
      if ((n === 37) && ((i + 2) < s.length)) {
        u = getHexDigit(s.charCodeAt(i + 1));
        v = getHexDigit(s.charCodeAt(i + 2));
        if ((u >= 0) && (v >= 0)) {
          c = String.fromCharCode((u << 4) | v);
        }
      }
      o = o + c;
      i = i + 1;
    }
    return o;
  }
}

// NS4
if ((typeof setInterval === 'undefined') && (typeof setTimeout === 'function')) {
  function setInterval(f, ms) {
    function g(self) {
      f();
      setTimeout(function() { self(self) }, ms);
    }
    setTimeout(function() { g(g) }, ms);
  }
}
