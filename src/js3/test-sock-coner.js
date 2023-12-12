var net = require('node:net');

function onConnect(client) {
  console.log('!fatal');
  u
}

var opt = new Object;
opt.host = 'localhost';
opt.port = 21198;
var client = net.createConnection(opt);
client.on('error', function() {
  console.log('!error');
});
client.on('connect', onConnect);
