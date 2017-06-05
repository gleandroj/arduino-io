#include <Regexp.h>
#include <Cmd.h>
#include "Ethernet.h"
#include <SocketIOClient.h>

/*Callbacks*/
void _digitalWrite(MatchState *ms);
void _digitalRead(MatchState *ms);
void _pinMode(MatchState *ms);
void ondata(SocketIOClient client, String event, String data);
void reconnect();

/*Globals*/
SocketIOClient client;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "herokuapp.com";
char hostname[] = "arduino-webserver.herokuapp.com";
int port = 80;

/*Command's*/
Command_t cmds[] =
{
  { "^digital write (%d+) (%d+)$", _digitalWrite },
  { "^digital read (%d+)$", _digitalRead },
  { "^pin mode (%d+) (%d+)$", _pinMode },
  { NULL, NULL }
};

Cmd* cmdParser;

void ondata(SocketIOClient client, String event, String json) {
  cmdParser->process(json.substring(json.indexOf(":\"")+2, json.length() - 2));
}

void reconnect() {
  client.disconnect();
  if (Ethernet.begin(mac) != 0) {
    if (!client.connect(server, hostname, port)) {
      Serial.println(F("Cannot connect to server."));
    }
    else if (client.connected()) {
      client.emit("arduino connect", "{}");
      return;
    }
  }
  Serial.println(F("Check the internet connection, or restart the arduino.\nTrying reconnect Ethernet."));
  delay(10000);
}

void setup()
{
  Serial.begin(9600);
  cmdParser = new Cmd(&cmds[0]);
  if (Ethernet.begin(mac) == 0) Serial.println(F("Failed to configure Ethernet using DHCP."));
  else Serial.println(Ethernet.localIP());
  client.setDataArrivedDelegate(ondata);

  if (!client.connect(server, hostname, port)) reconnect();
  else {
    client.emit("arduino connect", "{}");
  }
  Serial.println(F("Setup Finish"));
}

void loop()
{
  if (!client.monitor() && !client.connected()) {
    reconnect();
  }
}

void _digitalWrite(MatchState *ms)
{
  if (ms->level > 0)
  {
    char cpin[20], cval[20];
    ms->GetCapture(&cpin[0], 0);
    ms->GetCapture(&cval[0], 1);
    int pin = atoi(&cpin[0]), value = atoi(&cval[0]);

    digitalWrite(pin, value);
    _digitalRead(ms);
  }
};

void _digitalRead(MatchState *ms)
{
  if (ms->level > 0)
  {
    char cpin[10];
    ms->GetCapture(&cpin[0], 0);
    int pin = atoi(&cpin[0]);
    char response[34];
    sprintf(response, "{\"response\":{\"pin\":%d,\"value\":%d}}", pin, digitalRead(pin));
    client.emit("arduino response", response);
  }
};

void _pinMode(MatchState *ms)
{
  if (ms->level > 0)
  {
    char cpin[20], cval[20];
    ms->GetCapture(&cpin[0], 0);
    ms->GetCapture(&cval[0], 1);
    int pin = atoi(&cpin[0]), value = atoi(&cval[0]);

    pinMode(pin, value == 0 ? OUTPUT : INPUT);
  }
};

