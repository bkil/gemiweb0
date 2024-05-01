process.stdin.on('end', function(d) {
  console.log('EOF');
});
process.stdin.on('data', function(d) {
  d = d + '';
  if (d.charAt(0) === 'q') {
    console.log('quit');
    process.stdin.pause();
    process.stdin.removeAllListeners(['data', 'end']);
  } else {
    console.log(d + '.');
  }
});
