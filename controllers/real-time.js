const algorithm = require('../algorithm');
const io = require('../libraries/socket-io');

module.exports.start = function(app) {
    var clientSocket;

    // Create socket.io instance
    io.on('connection', function (socket) {
        socket.on('launchSimulation', function (inputedParams) {
          const paramObj = {
            serverPort: "8081",
            backupFile: '/home/foo/bar.csv',
            populationSize: "42",
            mutationRate: "0.01",
           }; // `paramObj` shouldn't be raw filled

            clientSocket = socket;

            // Emit example for the set of ymax :  clientSocket.emit("set y axle", {yMax: 55});
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
