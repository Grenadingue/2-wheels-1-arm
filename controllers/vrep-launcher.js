const config = require('../config/base.json');
var exec = require('child_process').spawn;

module.exports.launch = function(instance_number) {
   var path = process.argv.length > 2 ? process.argv[2] : config.vrep_path;
   var internalData = [];

   function launchOneInstance(path, inputed_port) {
      console.log(path + " -h -gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE -s10000 -q 2w1a.ttt");

      var new_process = exec(path, [
            "-h",
            "-gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE",
            "-s10000",
            "-q 2w1a.ttt"]);

      new_process.stdout.on('data', function(data) {
         console.log(inputed_port + ' stdout -------> ${data}');
         console.log(data);
      });
      new_process.stderr.on('data', function(data) {
         console.log(inputed_port + ' stderr ------->');
         console.log(data);
      });

      new_process.on('exit', (code) => {
        console.log(`Child exited with code ${code}`);
      });

      internalData.push({
         port: inputed_port,
         process: new_process
      });
   }

   var port = 19997;
   for (var i = 0; i < instance_number; ++i) {
      launchOneInstance(path, port);
      port += 10;
   }
   return internalData;
}
