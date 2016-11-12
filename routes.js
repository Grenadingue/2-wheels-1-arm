const path = require('path');
const fs = require('fs');

module.exports.init = function(app, controllers) {
    // Index
    app.get('/', function(req, res) {
        res.sendFile(path.join(__dirname + '/views/index.html'));
    });


    app.get('/save/', function(req, res) {
      fs.readdir('save/', (err, files) => {
         res.send(files);
      })
    });

    app.get('/save/:file_name', function(req, res) {
      let dataJSON = require(__dirname + '/save/' + req.params.file_name);
      res.send(dataJSON);
    });

  app.post('/params', function (req, res) {
    // body...
      res.send({});
  });

  // Get Front CSS files
  app.get('/views/css/:file_name', function(req, res) {
      var file_name = req.params.file_name;
      res.sendFile(path.join(__dirname + '/views/css/' + file_name));
  });

  // Get Front JS files
  app.get('/views/js/:file_name', function(req, res) {
      var file_name = req.params.file_name;
      res.sendFile(path.join(__dirname + '/views/js/' + file_name));
  });

  app.get('/chart.js', function(req, res) {
       res.sendFile(path.join(__dirname + '/node_modules/chart.js/dist/Chart.js'));
  });

  app.get('/socket.io.js', function(req, res) {
       res.sendFile(path.join(__dirname + '/node_modules/socket.io-client/socket.io.js'));
  });

  // Get socket port
  app.get('/socket_port', function(req, res) {
    let dataJSON = require(__dirname + '/config/base.json');
    res.send({socket_port: dataJSON.algo_port});
  });
}
