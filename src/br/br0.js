'use strict';

// Copyright (C) 2023-2024 bkil.hu
// Refer to the GNU GPL v2 in LICENSE for terms

function readFile(name, cb) {
  var fs = require('fs');
  fs.readFile(name, function(e, d) {
    if (e) {
      console.log(name + ': ' + e);
    } else {
      cb(d);
    }
  });
}

readFile('lib.js', function(libBrLib) {
  var libJs = new Object;
  libJs.s = libBrLib;
  readFile('br-lib.js', function(libBrLib) {
    var readFile;
    eval(libJs.s + libBrLib + 'libBrLib = null; brLibInit();');
  });
});
