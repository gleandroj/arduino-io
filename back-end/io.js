var _ = require('lodash');
var arduino =  null;
var responseLine = [];

function IoModule(io, redis) {

	var debug = function(msg){
		io.emit("debug", {message: msg});
	};

	redis.subscribe('test-channel', function(err, count) {

	});

	redis.on('message', function(channel, message) {
		console.log('Message Recieved: ' + message);
		message = JSON.parse(message);
		io.emit(channel + ':' + message.event, message.data);
	});

    /*io.on('connect', function (socket) {
        console.log("Connected: " + socket.id);
		socket.emit("connected", {});
		
        socket.on("disconnect", () => {
			console.log("Disconnected: " + socket.id);
        });
		
		socket.on("fatura_processada", () => {
			socket.broadcast.emit('fatura_processada', "this is a test");
			console.log("fatura processada");
        });
		
    });*/
};

module.exports = IoModule;