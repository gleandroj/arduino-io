var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);
var morgan = require('morgan');

module.exports = {
    App: app,
    Http: http,
    SocketIo: io
};