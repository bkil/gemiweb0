var net = require('node:net');

function onConnect(client) {
  client.on('data', function(d) {
    console.log(',' + d);
  });

  client.on('end', function() {
    console.log('!eof');
  });

  client.write(':connected');
  console.log('!connected');
  try {
    client.write(2);
  } catch (e) {
    console.log('!writebad,' + e);
  }
  client.end();
  console.log('!end');
}

var opt = new Object;
opt.host = 'localhost';
opt.port = 21198;
var client = net.createConnection(opt);
client.on('error', function() {
  console.log('!error');
});
client.on('connect', onConnect);
