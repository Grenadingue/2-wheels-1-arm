const algorithm = require('../algorithm');
const io = require('../libraries/socket-io.js'); //Not sure about syntax...

module.exports.start = function(app) {
    //Create socket.io instance
    io.on('connection', function (socket) {
	socket.on('data_stream', function (value1, value2) {
	    // Do logging of data}
	});
    });
    //Start c++ side
}
