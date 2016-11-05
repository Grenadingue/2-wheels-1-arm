const algorithm = require('../algorithm');
const io = require('../libraries/socket-io');
const paramObj =
{
 serverPort: "8081",
 backupFile: '/home/foo/bar.csv',
 populationSize: "42",
 mutationRate: "0.01",
};

module.exports.start = function(app) {

    var clientSocket;

    // Create socket.io instance
    io.on('connection', function (socket) {

        socket.on('launchSimulation', function (inputedParams) {
          clientSocket = socket;
          algorithm.launchSimulation(inputedParams);
        });

        socket.on('new result', function (result) {
            console.log('[Node.js] new result:', result);
            clientSocket.emit('new_iteration', result);
        });
    });
}
