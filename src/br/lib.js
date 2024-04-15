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

// JS1
String.prototype.lastIndexOf = String.prototype.lastIndexOf || function(c) {
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

// ES5
function JSON_stringify(o) {
  if ((typeof JSON !== 'undefined') && JSON.stringify) {
    return JSON.stringify(o);
  } else {
    var hex = '0123456789abcdef';
    var bs = String.fromCharCode(92);
    var bu00 = bs + 'u00';
    var zero = String.fromCharCode(0);
    var i = 0;
    var safe = '';
    while (i < 127) {
      if ((i === 34) || (i === 92) || (i < 32)) {
        safe = safe + zero;
      } else {
        safe = safe + '1';
      }
      i = i + 1;
    }

    function escapeQuote(s) {
      var o = '"';
      var i = -1;
      var n;
      var c;
      while (1) {
        c = s.charAt(i = i + 1);
        while (safe.charCodeAt(n = c.charCodeAt(0))) {
          o = o + c;
          c = s.charAt(i = i + 1);
        }
        if (isNaN(n)) {
          o = o + '"';
          return o;
        }
        if (n === 34) {
          c = bs + '"';
        } else if (n === 92) {
          c = bs + bs;
        } else if (n === 10) {
          c = bs + 'n';
        } else if (n < 127) {
          o = o + bu00;
          c = hex[n >> 4] + hex[n & 15];
        }
        o = o + c;
      }
    }

    function JSON_stringify_0(f, o) {
      var c;
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
            c = f(f, o[0]);
            s = s + c;
            var i = 1;
            while (i < o.length) {
              s = s + ',';
              c = f(f, o[i]);
              s = s + c;
              i = i + 1;
            }
          }
          s = s + ']';
          return s;
        } else {
          s = s + '{';
          var rest = 0;
          for (i in o) {
            if (rest) {
              s = s + ',';
            } else {
              rest = 1;
            }
            c = f(f, i);
            s = s + c + ':';
            c = f(f, o[i]);
            s = s + c;
          }
          s = s + '}';
          return s;
        }
      } else {
        return 'null';
      }
    }

    return JSON_stringify_0(JSON_stringify_0, o);
  }
}

// ES5
function JSON_parse(s) {
  if ((typeof JSON !== 'undefined') && JSON.parse) {
    return JSON.parse(s);
  } else {
    var i = 0;
    var n;
    var hex = '0123456789abcdef';
    function hex2dec(c) {
      var j = hex.indexOf(c);
      if (j < 0) {
        throw 'invalid hex character code "' + c + '" at position ' + i;
      }
      return j;
    }

    function peekCh() {
      if (i < s.length) {
        n = s.charCodeAt(i);
      } else {
        n = 0;
      }
    }

    function nextCh() {
      i = i + 1;
      peekCh();
    }

    function parseString() {
      var o = '';
      if (n !== 34) {
        throw 'expected " character instead "' + s.charAt(i) + '" at position ' + i;
      }
      nextCh();
      var c;
      while (n !== 34) {
        if (((i + 5) < s.length) && (n === 92) && (s.charCodeAt(i + 1) === 117) &&
            (s.charCodeAt(i + 2) === 48) && (s.charCodeAt(i + 3) === 48)) {
          c = String.fromCharCode((hex2dec(s.charAt(i + 4)) << 4) + hex2dec(s.charAt(i + 5)));
          i = i + 6;
        } else if (((i + 1) < s.length) && (n === 92)) {
          nextCh();
          if (n === 110) {
            c = String.fromCharCode(10);
          } else {
            c = s.charAt(i);
          }
          i = i + 1;
        } else {
          c = s.charAt(i);
          i = i + 1;
        }
        o = o + c;
        peekCh();
      }
      nextCh();
      return o;
    }

    function JSON_parse_0(y) {
      var o;
      var saved;

      if (n === 34) {
        o = parseString();
      } else if (((n > 47) && (n < 58)) || (n === 45)) {
        saved = i;
        o = 0;
        var sign = 0;
        if (n === 45) {
          sign = 1;
          nextCh();
          if ((n < 48) || (n > 57)) {
            throw 'expected number instead "' + s.charAt(i) + '" at position ' + i;
          }
        }
        while ((n > 47) && (n < 58)) {
          o = ((o * 10) + n) - 48;
          nextCh();
        }
        if (n === 46) {
          nextCh();
          while ((n > 47) && (n < 58)) {
            nextCh();
          }
          o = s.substring(saved, i);
        } else if (sign) {
          o = 0 - o;
        }
      } else if (n === 91) {
        var j = 0;
        o = new Array;
        nextCh();
        if (n !== 93) {
          o[j] = y(y);
          j = j + 1;
          while (n === 44) {
            nextCh();
            o[j] = y(y);
            j = j + 1;
          }
          if (n !== 93) {
            throw 'expected ] character instead "' + s.charAt(i) + '" at position ' + i;
          }
        }
        nextCh();
      } else if (n === 123) {
        o = new Object;
        nextCh();
        var k;
        while (n !== 125) {
          k = parseString();
          if (n !== 58) {
            throw 'expected : character instead "' + s.charAt(i) + '" at position ' + i;
          }
          nextCh();
          o[k] = y(y);
          if (n === 44) {
            nextCh();
          }
        }
        nextCh();
      } else if (((i + 3) < s.length) && (n === 110) && (s.charCodeAt(i + 1) === 117) &&
          (s.charCodeAt(i + 2) === 108) && (s.charCodeAt(i + 3) === 108)) {
        o = null;
        i = i + 4;
        peekCh();
      } else if (((i + 3) < s.length) && (n === 116) && (s.charCodeAt(i + 1) === 114) && (s.charCodeAt(i + 2) === 117) &&
          (s.charCodeAt(i + 3) === 101)) {
        o = 1;
        i = i + 4;
        peekCh();
      } else if (((i + 4) < s.length) && (n === 102) && (s.charCodeAt(i + 1) === 97) && (s.charCodeAt(i + 2) === 108) &&
          (s.charCodeAt(i + 3) === 115) && (s.charCodeAt(i + 4) === 101)) {
        o = 0;
        i = i + 5;
        peekCh();
      } else {
        throw 'unexpected character "' + s.charAt(i) + '" at position ' + i;
      }

      return o;
    }

    peekCh();
    var o = JSON_parse_0(JSON_parse_0);
    if (i < s.length) {
      throw 'extra characters at end "' + s.charAt(i) + '" at position ' + i;
    }
    return o;
  }
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
  var encodeURIComponent2 = String.fromCharCode(256);
  if (encodeURIComponent2.charCodeAt(0) === 256) {

    var encodeURIComponent = function(s) {
      var hex = '0123456789abcdef';
      var o = '';
      var c;
      function push(x) {
        o = o + '%';
        c = hex[x >> 4] + hex[x & 15];
        o = o + c;
      }
      var i = 0;
      var u;
      var n;
      var m;
      while (i < s.length) {
        n = s.charCodeAt(i);
        i = i + 1;

        if (((n >= 44) && (n <= 59)) || ((n >= 64) && (n <= 126))) {
          o = o + String.fromCharCode(n);
        } else if (n < 128) {
          push(n);
        } else if (n < 2048) {
          push(192 | (n >> 6));
          push(128 | (n & 63));
        } else if ((n < 55296) || (n > 57344)) {
          push(224 | (n >> 12));
          push(128 | ((n >> 6) & 63));
          push(128 | (n & 63));
        } else {
          if ((n > 56319) || (i >= s.length)) {
            throw 'URIError';
          }
          m = s.charCodeAt(i);
          i = i + 1;
          if ((n > 56319) || (n < 55296)) {
            throw 'URIError';
          }
          u = ((n >> 6) & 15) + 1;
          push(240 + (u >> 2));
          push(128 | ((u & 3) << 4) | ((n >> 2) & 15));
          push(128 | ((n & 3) << 4) | ((m >> 6) & 15));
          push(128 | (m & 63));
        }
      }
      return o;
    }
  } else {

    var encodeURIComponent = function(s) {
      var zero = String.fromCharCode(0);
      var i = 1;
      var safeList = "!'()*-._~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      var safe = zero;
      var hex = '0123456789abcdef';
      while (i < 127) {
        if (safeList.indexOf(String.fromCharCode(i)) < 0) {
          safe = safe + zero;
        } else {
          safe = safe + '1';
        }
        i = i + 1;
      }

      var o = '';
      i = -1;
      var n;
      var c;
      while (1) {
        c = s.charAt(i = i + 1);
        while (safe.charCodeAt(n = c.charCodeAt(0))) {
          o = o + c;
          c = s.charAt(i = i + 1);
        }
        if (isNaN(n)) {
          return o;
        }
        if (n > 255) {
          return undefined;
        }
        c = hex[n >> 4] + hex[n & 15];
        o = o + '%';
        o = o + c;
      }
    }
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
