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

            algorithm.launchSimulation(paramObj);
        });

        socket.on('new result', function (result) {
            console.log('[WEB_SERVER] new result:', result);
            clientSocket.emit('new_iteration', result); // format: { iteration: 0, maxScore: 0, averageScore: 0, worstScore: 0 }
        });

        socket.on('theoretical max score', function (theoreticalMaxScore) {
            console.log('[WEB_SERVER] theoretical max score:', theoreticalMaxScore);
            clientSocket.emit("set y axle", {theoreticalMaxScore: theoreticalMaxScore});
        });

        socket.on('solution found', function (solution) {
            console.log('[WEB_SERVER] solution found:', solution);
        });
    });
};
