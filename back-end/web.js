var express = require('express');
function WebModule (App) {
    App.use('/static', express.static(__dirname +'/public'));

    App.get('/', (req, resp) => {
        resp.sendFile(__dirname +'/public/index.html');
    });
	
	App.get('/room', (req, resp) => {
        resp.sendFile(__dirname +'/public/room.html');
    });

}

module.exports = WebModule;