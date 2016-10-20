const path = require('path');
const fs = require('fs');

module.exports.init = function(app, controllers) {
    // Index
    app.get('/', function(req, res) {
        res.sendFile(path.join(__dirname + '/views/index.html'));
    });


    app.get('/save/', function(red, res) {
      fs.readdir('save/', (err, files) => {
         res.send(files);
      })
    });

   // Some Problem to get my front files
   app.get('/service.js', function(req, res) {
         res.sendFile(path.join(__dirname + '/front/' + '/service.js'));
   });
   app.get('/draw.js', function(req, res) {
         res.sendFile(path.join(__dirname + '/front/' + '/draw.js'));
   });
   app.get('/init.js', function(req, res) {
         res.sendFile(path.join(__dirname + '/front/' + '/init.js'));
   });
}