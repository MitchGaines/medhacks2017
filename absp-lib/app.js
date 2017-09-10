// app.js
var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var SerialPort = require("serialport");
// spPortName may need to be configured until we resolve automatic detection!
var spPortName = "COM3";
var port = 3000;

app.use(express.static('public'));

app.get('/', function(req, res, next) {
  res.sendFile(__dirname + '/index.html');
});


io.on('connection', function(client) {
  client.on('join', function(data) {
    console.log(data);

    
    setTimeout(function () {
      var receivedData = "";
      var serialport = new SerialPort(spPortName, {
           baudrate: 9600
      });

      var buffer = "";
      serialport.on('data', function(data){
          var match = /\r|\n/.exec(data);
          if (match) {
              buffer += data;
              sendData = buffer.replace(/[\r\n]/g, "");
              if(sendData != "") io.emit('update', {sendData});
              buffer = "";
          } else buffer += data;
      });
    }, 50);
  });

});

io.on('error', function(err) {
  console.log(err);
});

server.listen(port, function() {
  console.log("ABSP Server running on port " + port);
});



