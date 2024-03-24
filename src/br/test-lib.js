'use strict';

// Copyright (C) 2024 bkil.hu
// Refer to the GNU GPL v2 in LICENSE for terms

function readFile(name, cb) {
  var fs = require('fs');
  fs.readFile(name, function(e, d) {
    if (e) {
      console.log(name + ': ' + e);
    } else {
      cb(d + '');
    }
  });
}

readFile('lib.js', function(libBrLib) {
  var libJs = new Object;
  libJs.s = libBrLib;
  libBrLib = undefined;
  readFile('test-br-body.js', function(libBrLib) {
    libJs.s = libJs.s + libBrLib;
    libJs.s = libJs.s + 'testLibInit();';
    libBrLib = undefined;
    var readFile;
    eval(libJs.s);
  });
});
