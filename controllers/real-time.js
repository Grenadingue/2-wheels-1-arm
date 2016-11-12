const algorithm = require('../algorithm');
const io = require('../libraries/socket-io');
const config = require('../config/base.json');
const path = require('path');

module.exports.start = function(app) {
    var clientSocket;

    // Create socket.io instance
    io.on('connection', function (socket) {
        socket.on('launchSimulation', function (inputedParams) {
          let serverPort = config.algo_port;

          let appDir = path.dirname(require.main.filename);
          let fileName = new Date().getTime() + '.json';
          let backupFile = appDir + config.saved_file_path + fileName;

          // const paramObj = {
          //   serverPort: "8081",
          //   backupFile: '/home/foo/bar.csv',
          //   populationSize: "42",
          //   mutationRate: "0.01",
          //  };

           const paramObj = {
             serverPort: serverPort,
             backupFile: backupFile,
             populationSize: inputedParams.populationSize,
             populationRenewalRate: inputedParams.populationRenewalRate,
             mutationRate: inputedParams.mutationRate,
             simulationCycles: inputedParams.simulationCycles
            };

            console.log("[Node -> C++ params]");
            console.log(paramObj);

            clientSocket = socket;

            // Emit example for the set of ymax :  clientSocket.emit("set y axle", {theoreticalMaxScore: 55});
            algorithm.launchSimulation(paramObj);
        });

        var i = 0;
        socket.on('new result', function (result) {
            console.log('[WEB_SERVER] new result:', result);
            // Working with a result using this format {best: 1, mid: 1}
            clientSocket.emit('new_iteration', { best: i * 4, mid: i * 2 }); // Simulate a valid result
            ++i;
        });
    });
};
