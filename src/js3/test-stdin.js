process.stdin.on('data', function(d) {
  if (d === undefined) {
    console.log('EOF');
    process.stdin.removeAllListeners(['data']);
  } else {
    console.log(d + '.');
  }
});
