const port = require('../config/base.json').algo_port;
module.exports = require('socket.io')(port);
