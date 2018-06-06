'use strict';

/* jshint node: true */

var express = require('express');

var portno = 3000;   // Port number to use

var app = express();

// We have the express static module (http://expressjs.com/en/starter/static-files.html) do all
// the work for us.
app.use(express.static(__dirname));

app.get('/', function (request, response) {
  response.send('Simple web server of files from ' + __dirname);
});



// app.get('/test/:p1', function (request, response) {
//   // Express parses the ":p1" from the URL and returns it in the request.params objects.
//   var param = request.params.p1;
//   console.log('/test called with param1 = ', param);
//   if (param !== "info") {
//     console.error("Nothing to be done for param: ", param);
//     response.status(400).send('Not found');
//     return;
//   }



var server = app.listen(portno, function () {
  var port = server.address().port;
  console.log('Listening at http://localhost:' + port + ' exporting the directory ' + __dirname);
});
