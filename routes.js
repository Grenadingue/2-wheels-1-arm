const path = require('path');

module.exports.init = function(app) {
    // Index
    app.get('/', function(req, res) {
        res.sendFile(path.join(__dirname + '/views/index.html'));
    });
}