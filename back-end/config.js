var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);
var morgan = require('morgan');
var Redis = require('ioredis');

module.exports = {
    App: app,
    Http: http,
    SocketIo: io,
    Redis: new Redis('redis://:authpassword@ec2-18-231-25-84.sa-east-1.compute.amazonaws.com:6379/0')
};