process.stdin.on('data', function(d) {
  if (d === undefined) {
    console.log('EOF');
    process.stdin.on('data', undefined);
  }  else {
    console.log(d + '.');
  }
});
