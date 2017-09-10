// app.js
var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var five = require("johnny-five");
var board = new five.Board();
var port = 3000;

app.use(express.static('public'));

app.get('/', function(req, res, next) {
  res.sendFile(__dirname + '/index.html');
});


board.on('ready', function() {
  board.digitalWrite(22, 0);
  board.digitalWrite(23, 0);
  board.digitalWrite(24, 0);
  board.digitalWrite(25, 0);
  io.on('connection', function(client) {
  
    client.on('join', function(data) {
      console.log(data);
    });

    client.on('coords', function(data) {
      console.log(data);
      if(data.x < 860 && data.x > 780 && data.y > 550 && data.y < 600){
        //inflate upper left
        board.digitalWrite(22, 1);
        setTimeout(function() {
          board.digitalWrite(22, 0);
        }, 2000);
      } else if(data.x < 860 && data.x > 780){
        //inflate lower left
        board.digitalWrite(23, 1);
        setTimeout(function() {
          board.digitalWrite(23, 0);
        }, 2000);
      } else if(data.x < 980 && data.x > 880 &&  data.y > 550 && data.y < 600){
        //inflate upper right
        board.digitalWrite(24, 1);
        setTimeout(function() {
          board.digitalWrite(24, 0);
        }, 2000);
      } else if(data.x < 980 && data.x > 880){
        //inflate lower right
        board.digitalWrite(25, 1);
        setTimeout(function() {
          board.digitalWrite(25, 0);
        }, 2000);
      }
      
    });
    
  });
});





io.on('error', function(err) {
  console.log(err);
});

server.listen(port, function() {
  console.log("ABSP Server running on port " + port);
});



