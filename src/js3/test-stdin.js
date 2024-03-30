process.stdin.on('data', function(d) {
  if (d === undefined) {
    console.log('EOF');
    process.stdin.removeAllListeners(['data']);
  } else {
    d = d + '';
    if (d.charAt(0) === 'q') {
      console.log('quit');
      process.stdin.pause();
      process.stdin.removeAllListeners(['data']);
    } else {
      console.log(d + '.');
    }
  }
});
