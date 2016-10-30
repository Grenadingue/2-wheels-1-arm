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
    //Create socket.io instance
    io.on('connection', function (socket) {
   	socket.on('data_stream', function (value1, value2) {
   	    // Do logging of data}
   	});
    });
        //Start c++ side
//    console.log(algorithm.launchSimulation(paramObj, "lol"));
}
