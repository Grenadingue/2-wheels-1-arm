const config = require('./config/base.json');
config.rootFolder = __dirname;

const app = require('./libraries/express').init(config);
// var SocketIO = require('./libraries/socket-io');

const controller = require('./controller');

require('./routes').init(app);
const server = app.listen(config.port, function () {
    console.log('Listening on port ' + config.port);
});
// var socket = SocketIO.init(server);
