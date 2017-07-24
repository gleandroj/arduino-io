var config = require('./back-end/config');
require('./back-end/io')(config.SocketIo, config.Redis);
require('./back-end/web')(config.App);

var PORT = process.env.PORT || 3000;

config.Http.listen(PORT, () => {

  console.log(`Listening on ${PORT}`);

});