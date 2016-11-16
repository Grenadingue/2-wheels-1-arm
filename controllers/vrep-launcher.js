const config = require('../config/base.json');
var exec = require('child_process').spawn;
var internalData = [];

module.exports.launch = function(instance_number) {
   var path = process.argv.length > 2 ? process.argv[2] : config.vrep_path;
   var portArray = [];

   function isPortTaken(path, port, instanceLauncher, chainer) {
     var net = require('net');
     var tester = net.createServer()
     .once('error', function (err) {
         console.log("Connection failed on " + path);
         chainer();
     })
     .once('listening', function() {
       tester.once('close', function() {

         portArray.push(port);
         instanceLauncher(path, port);
         console.log("Connection success on " + path);

         chainer();

       })
       .close()
     })
     .listen(port);
   }

   function launchOneInstance(path, inputed_port) {
      console.log(path + " -h -gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE -s10000 -q " + process.cwd() +"/2w1a.ttt");

      var new_process = exec(path, [
            "-h",
            "-gREMOTEAPISERVERSERVICE_" + inputed_port + "_TRUE_FALSE",
            "-q " + process.cwd() + "/2w1a.ttt"]);

      new_process.resp = "";
      new_process.stdout.on('data', function(data) {
         new_process.resp += data.toString();
      });

      new_process.stdout.on('data', function(data) {
         //console.log(inputed_port + ' stdout ------->');
         //console.log(new_process.resp);
      });

      new_process.stderr.on('data', function(data) {
         //console.log(inputed_port + ' stderr ------->');
         //console.log(data);
      });

      new_process.on('exit', (code) => {
        console.log(`Child exited with code ${code}`);
      });

      internalData.push({
         port: inputed_port,
         process: new_process
      });
   }

   /* Recusive call until we have enough vrek instance */
   var port = 8070;
   function Chaining() {
      if (portArray.length == instance_number)
         return;
      port += 10;
      console.log("Trying to connect on " + port);
      isPortTaken(path, port, launchOneInstance, Chaining);
   }
   return new Promise(function (fulfill, reject) {
      Chaining();
      fulfill(portArray);
   });
}

module.exports.stop = function(){
   for (var i = 0; i < internalData.length; i++) {
      internalData[i].process.kill();
      console.log("killed");
   }
   internalData = [];
}