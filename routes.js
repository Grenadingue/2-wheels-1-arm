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
      var file_name = req.params.file_name;
      fs.readFile('save/' + file_name, 'utf8', function(err, data) {
        res.send(JSON.parse(data));
      });
    });

  app.post('/params', function (req, res) {
    // body...
      res.send({});
  });


  // Get Front JS files
  app.get('/views/:file_name', function(req, res) {
      var file_name = req.params.file_name;
      res.sendFile(path.join(__dirname + '/views/js/' + file_name));
  });

  app.get('/chart.js', function(req, res) {
       res.sendFile(path.join(__dirname + '/node_modules/chart.js/dist/Chart.js'));
  });
}