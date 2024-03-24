'use strict';

// Copyright (C) 2024 bkil.hu
// Refer to the GNU GPL v2 in LICENSE for terms

var succ = 0;
var fails = 0;

function t(f, expect) {
  var got;
  try {
    got = eval(f);
  } catch (e) {
    fails = fails + 1;
    console.log('fail: ' + f + ', exception ' + e);
    return 0;
  }
  if (got === expect) {
    succ = succ + 1;
  } else {
    console.log('fail: ' + f + ', expected: ' + expect + ', got: ' + got);
    fails = fails + 1;
  }
}

function testLibInit() {
  var q = String.fromCharCode(34);
  t("encodeURIComponent('') === ''", 1);
  t("encodeURIComponent('0Az') === '0Az'", 1);
  t("var a = String.fromCharCode(39); var s = encodeURIComponent(' !" + q + "#$%&' + a + '()*+,-./;<=>?[\]^_`{|}~'); s.toLowerCase() === ('%20!%22%23%24%25%26' + a + '()*%2b%2c-.%2f%3b%3c%3d%3e%3f%5b%5d%5e_%60%7b%7c%7d~')", 1);
  t("var s = encodeURIComponent('xáx'); s.toLowerCase() === 'x%c3%a1x'", 1);
  t("var s = encodeURIComponent('x😼x'); s.toLowerCase() === 'x%f0%9f%98%bcx'", 1);

  if (fails === 0) {
    console.log('All ' + succ + ' test successful');
    return 0;
  } else {
    console.log(fails + ' tests failed');
    return 1;
  }
}
