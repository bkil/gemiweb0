var net = require('node:net');
var s = new Object;
s.buf = '';

function onConnect(client) {
  client.on('data', function(d) {
    s.buf = s.buf + d;
    if (s.buf.indexOf('?ping') >= 0) {
      client.write(':pong');
      console.log('!pong');
    }
    if (s.buf.indexOf('?bye') >= 0) {
      client.end();
      console.log('!bye,' + s.buf);
    }
  });

  client.on('end', function() {
    console.log('!eof,' + s.buf);
    client.removeAllListeners(['data', 'end', 'error', 'connect']);
  });

  client.write(':connected');
  console.log('!connected');
}

var opt = new Object;
opt.host = 'localhost';
opt.port = 21198;
var client = net.createConnection(opt);
client.on('error', function() {
  console.log('!error');
});
client.on('connect', onConnect);
