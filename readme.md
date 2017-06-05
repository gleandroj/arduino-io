# Arduino IO
###### Connect Arduino and WebSocket (SocketIO) from everywhere simple and real time.
### Dependencies
 - [CMD](https://github.com/gleandroj/Cmd) - Simple Arduino Command Processor Library
 - [Socket Io 1.x.x](https://socket.io/) - WebSocket Library
 
### Compatibility
*   ###### Tested with Socket Io Version 1.7.2
*   ###### Tested with Arduino Uno and Ethernet Library

### Get Started
```sh
$ git clone ...
$ npm install
$ npm start
```

##### Now you upload the arduino-io.ino into your arduino.
###
##
```
#include <Regexp.h>
#include <Cmd.h>
#include "Ethernet.h"
#include <SocketIOClient.h>

/*Callbacks*/
    ...
/*Globals*/
    SocketIOClient client;
    byte mac[] = { }; // Your Ethernet Mac Address 
    char server[] = "herokuapp.com"; // Your host server, it's not necessary if are using local
    char hostname[] = "arduino-webserver.herokuapp.com"; // Your server Address or your server ip (local)
    int port = 80; // Your Server Websocket port
/*Command's*/
    ...
```

#### Enjoy!
Found this project useful? Please star this project! 😄