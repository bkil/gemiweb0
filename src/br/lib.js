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
  var i = this.length - 1;
  var n = c.charCodeAt(0);
  while ((i >= 0) && (this.charCodeAt(i) !== n)) {
    i = i - 1;
  }
  return i;
}

String.prototype.toUpperCase = String.prototype.toUpperCase || function() {
  var o = '';
  var i = 0;
  while (i < this.length) {
    var c = this.charAt(i);
    var n = c.charCodeAt(0);
    if ((n >= 97) && (n <= 122)) {
      o = o + String.fromCharCode(n - 32);
    } else {
      o = o + c;
    }
    i = i + 1;
  }
  return o;
}

String.prototype.toLowerCase = String.prototype.toLowerCase || function() {
  var o = '';
  var i = 0;
  while (i < this.length) {
    var c = this.charAt(i);
    var n = c.charCodeAt(0);
    if ((n >= 65) && (n <= 90)) {
      o = o + String.fromCharCode(n + 32);
    } else {
      o = o + c;
    }
    i = i + 1;
  }
  return o;
}

String.prototype.substring = String.prototype.substring || function(from, to) {
  var o = '';
  if (!(from > 0)) {
    from = 0;
  }
  var i = from;
  if (to === undefined) {
    while (i < this.length) {
      o = o + this.charAt(i);
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
      o = o + this.charAt(i);
      i = i + 1;
    }
  }
  return o;
}

String.prototype.substr = String.prototype.substr || function(from, n) {
  if (from < 0) {
    return undefined;
  }
  var o = '';
  var i = from;
  if (n === undefined) {
    while (i < this.length) {
      o = o + this.charAt(i);
      i = i + 1;
    }
  } else {
    while (i < this.length) {
      if (n <= 0) {
        return o;
      }
      n = n - 1;
      o = o + this.charAt(i);
      i = i + 1;
    }
  }
  return o;
}

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
  var h = this;
  i = h.indexOf(s);
  while (i >= 0) {
    a[j] = h.substring(0, i);
    j = j + 1;
    h = h.substring(i + 1);
    i = h.indexOf(s);
  }
  a[j] = h;
  return a;
}

Array.prototype.join = Array.prototype.join || function(d) {
  if (d === undefined) {
    d = ',';
  }
  var s = '';
  if (this.length) {
    s = s + this[0];
    var i = 1;
    while (i < this.length) {
      s = (s + d) + this[i];
      i = i + 1;
    }
  }
  return s;
}

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

if (typeof Function === 'undefined') {
  function Function(param, body) {
    return eval((('(function(' + param) + ('){' + body)) + '})')
  }
}

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

if (typeof decodeURIComponent === 'undefined') {
  function decodeURIComponent(s) {
    return s; // TODO
  }
}

if ((typeof setInterval === 'undefined') && (typeof setTimeout === 'function')) {
  function setInterval(f, ms) {
    function g(self) {
      f();
      setTimeout(function() { self(self) }, ms);
    }
    setTimeout(function() { g(g) }, ms);
  }
}
