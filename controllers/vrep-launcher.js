const config = require('../config/base.json');
var sys = require('sys')
var exec = require('child_process').exec;

module.exports.launch = function(instance_number) {
   var path = process.argv.length > 2 ? process.argv[2] : config.vrep_path;
   var port_list = [];

   function puts(error, stdout, stderr) {
      console.log("<------- error ------->")
      console.log(error);
      console.log("<------- stdout ------->")
      console.log(stdout);
      console.log("<------- stderr ------->")
      console.log(stderr);
   }

   function launchOneInstance(path, inputed_port) {
      console.log(path + " -h -gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE -s10000 -q 2w1a.ttt");
      exec(path + " -h -gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE -s10000 -q 2w1a.ttt", puts);
      port_list.push(port);
   }

   var port = 19997;
   for (var i = 0; i < instance_number; ++i) {
      launchOneInstance(path, port);
      port += 10;
   }
   return port_list;
}
