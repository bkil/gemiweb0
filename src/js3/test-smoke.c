/* Copyright (C) 2023 bkil.hu
Refer to the GNU GPL v2 in LICENSE for terms */

#include "testutil.h"

int
main(void) {
  /* error messages and return values */
  setDebug(true);
  t(":", -1);
  t("if", -1);
  t("u", -2);
  t("throw 'u'", -2);
  t("return 0", -2);
  setDebug(false);

  /* non-conforming */
  t("(new Date) + 0", -2);

  /* non-conforming */
  t("var s = ''; s + (s.charCodeAt)) === 'Method'", -1);

  /* non-conforming */
  t("3 - null", -2);

  t("process.stdin.on('data', function(d) { process.stdin.on('data', undefined); })", 0);
  t("process.stdin.on('end', function(){})", 0);
  t("process.stdin.on('x', function(d) {})", -2);
  t("process.stdin.removeAllListeners()", -2);
  t("process.stdin.removeAllListeners(2)", -2);
  t("process.stdin.removeAllListeners(['data', 'end'])", 0);
  t("process.stdin.pause()", 0);

  t("require()", -2);
  t("require(null)", -2);
  t("require('x') === undefined", 1);

  t("var f = require('fs'); f.readFile()", -2);
  t("var f = require('fs'); f.readFile('x')", -2);
  t("var f = require('fs'); f.readFile('x', 2)", -2);
  t("var f = require('fs'); var o = new Object; f.readFile('test-vm-1.txt', function(e, d) {o.e = e; o.d = d}); (o.e === undefined) && (o.d === 'abc')", 1);
  t("var f = require('fs'); var o = new Object; f.readFile('x', function(e, d) {o.e = e; o.d = d}); (o.d === undefined) && (o.e.charAt(0))", 1);

  t("var f = require('fs'); f.writeFile()", -2);
  t("var f = require('fs'); f.writeFile('test-vm-w.txt')", -2);
  t("var f = require('fs'); f.writeFile('test-vm-w.txt', null)", -2);
  t("var f = require('fs'); f.writeFile('test-vm-w.txt', 'x', 2)", -2);
  t("var f = require('fs'); var o = new Object; f.writeFile('.', 'x', function(e){o.e=e}); o.e.charAt(0)", 1);
  t("var f=require('fs'); var d='' + (new Date/1000); var o=new Object; f.writeFile('test-vm-w.out', d, function(e) {if (e === undefined) { f.readFile('test-vm-w.out', function(e, d){o.e = e; o.d = d}) } else {o.e = e}}); (o.e === undefined) && (o.d === d)", 1);

  t("var f = require('fs'); f.readdir()", -2);
  t("var f = require('fs'); f.readdir('.')", -2);
  t("var f = require('fs'); f.readdir('.', 2)", -2);
  t("var f=require('fs'); var o=new Object; f.readdir('', function(e,l){o.e=e;o.l=l}); (o.e.charAt(0)) && (o.l.length===0)", 1);
  t("var f=require('fs'); var o=new Object; f.readdir('.', function(e,l){o.e=e;o.l=l}); var s=o.l[0]; (o.e===undefined) && (o.l.length > 2) && (s.charAt(0))", 1);

  t("setTimeout()", -2);
  t("setTimeout(function(){})", -2);
  t("setTimeout(function(){}, null)", -2);
  t("setTimeout(0, function(){})", -2);
  t("var o = new Object; setTimeout(function() { o.i = 9 }, 0); o.i === undefined", 1);
  te("var o = new Object; setTimeout(function() { o.i = 9 }, 0)", "o.i", 9);
  t("var v = require('vm'); var p = new Object; v.createContext(p); v.runInContext('setTimeout(function() { }, 9)', p); p['.timeoutMs']", 9);
  t("var v = require('vm'); var p = new Object; v.createContext(p); v.runInContext('var o = new Object; setTimeout(function() { o.i = 9 }, 0)', p); var f = p['.onTimeout']; v.runInContext(f, p); v.runInContext('o.i', p)", 9);

  /* non-conforming */
  te("var o = new Object; setTimeout(function() { o.i = 9 }, 0); setTimeout(function(){}, 0)", "o.i === undefined", 1);

  /* non-conforming */
  t("var v = require('vm'); var p = new Object; v.createContext(p); v.runInContext('var o = new Object; setTimeout(function() { o.i = 9 }, 0)', p); v.runInContext('setTimeout(function() {}, 0)', p); var f = p['.onTimeout']; v.runInContext(f, p); v.runInContext('o.i === undefined', p)", 1);

  t("var n=require('node:net'); n.createConnection()", -2);
  t("var n=require('node:net'); n.createConnection(2)", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.on()", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.on('u', function(){})", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.on('connect')", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.on('connect', 2)", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.on('connect', function(){})", 0);
  t("var n=require('node:net'); var o=new Object; o.host='localhost'; var c=n.createConnection(o); var e=new Object; c.on('error', function(m){e.e=m}); c.on('connect',function(){}); e.e==='expecting port'", 1);
  t("var n=require('node:net'); var o=new Object; o.port=1; var c=n.createConnection(o); var e=new Object; c.on('error', function(m){e.e=m}); c.on('connect',function(){}); e.e==='expecting host'", 1);
  t("var n=require('node:net'); var o=new Object; o.host='localhost'; var c=n.createConnection(o); var e=new Object; c.on('error', function(m){e.e=m;return m}); c.on('connect',function(){}); e.e==='expecting port'", 1);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.removeAllListeners()", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.removeAllListeners(2)", -2);
  t("var n=require('node:net'); var c=n.createConnection(new Object); c.removeAllListeners(['connect','data','end','error'])", 0);

  return exitWithErrorCount("smoke");
}
