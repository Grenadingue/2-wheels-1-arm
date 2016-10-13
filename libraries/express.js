module.exports.init = function(conf) {
    const express = require('express');
    const bodyParser = require('body-parser');

    const app = express();

    app.use(bodyParser.json());
    app.use(bodyParser.urlencoded({ extended: true }));

    app.use(function(req, res, next) {
        if (req.get('origin'))
            res.setHeader('Access-Control-Allow-Origin', req.get('origin'));
        res.setHeader('Access-Control-Allow-Credentials', true);
        res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
        next();
    });

    return app;
};