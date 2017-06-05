var _ = require('lodash');
var arduino =  null;
var responseLine = [];

function IoModule(io) {

    io.on('connect', function (socket) {
        console.log("Connected: " + socket.id);
		socket.emit("connected", {});
		
        socket.on("disconnect", () => {
			if(arduino != null && socket.id == arduino.id) {
				arduino = null;
				console.log("Arduino disconnected: " + socket.id);
			}
			
			console.log("Disconnected: " + socket.id);
        });
		
		socket.on("arduino connect", () => {
            arduino = socket;
			console.log("Arduino connected: " + arduino.id);
			
			arduino.on("arduino response", function(response){
				//console.log(JSON.stringify(response));
				arduino.broadcast.emit("arduino response", response);
			});
        });
		
		socket.on("arduino command", (cmd, fn) => {
			if(arduino) {
				arduino.emit("arduino command", cmd);
				console.log('arduino command sent: ' + JSON.stringify(cmd));
			}
		});
		
		 socket.on('ping', function() {
			console.log('ping');
	    });
    });
};

module.exports = IoModule;