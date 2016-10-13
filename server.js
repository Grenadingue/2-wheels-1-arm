const config = require('./config/base.json');
config.rootFolder = __dirname;

const app = require('./libraries/express').init(config);
// const SocketIO = require('./libraries/socket-io');

const controllers = require('./controllers');

require('./routes').init(app, controllers);
const server = app.listen(config.port, function () {
    console.log('Listening on port ' + config.port);
});
// const socket = SocketIO.init(server);
