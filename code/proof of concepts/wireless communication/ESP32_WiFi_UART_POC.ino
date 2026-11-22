#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ESP32-C3 Super Mini proof-of-concept.
// Browser <-> ESP32 access point <-> UART <-> Arduino Nano.
// Copy secrets.example.h to secrets.h and configure a unique password.
#if __has_include("secrets.h")
#include "secrets.h"
#define LINEFOLLOWER_WIFI_CONFIGURED true
#else
#define LINEFOLLOWER_WIFI_SSID "Linefollower-V2"
#define LINEFOLLOWER_WIFI_PASSWORD "CHANGE_ME_BEFORE_USE"
#define LINEFOLLOWER_WIFI_CONFIGURED false
#endif

const char *AP_SSID = LINEFOLLOWER_WIFI_SSID;
const char *AP_PASSWORD = LINEFOLLOWER_WIFI_PASSWORD;
const int NANO_RX_PIN = 20;  // ESP32 ontvangt van Nano TX
const int NANO_TX_PIN = 21;  // ESP32 zendt naar Nano RX

HardwareSerial NanoSerial(1);
WebServer server(80);
String nanoLine;
String lastNanoLine = "Nog geen data ontvangen";

const char PAGE[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="nl">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>LineFollower V2 – UART test</title>
<style>
body{font-family:Arial,sans-serif;max-width:760px;margin:24px auto;padding:0 16px}
input,button{font-size:1rem;padding:10px;margin:4px 0}
input{width:70%;max-width:420px}button{cursor:pointer}
pre{background:#eee;padding:12px;white-space:pre-wrap;overflow-wrap:anywhere}
</style>
</head>
<body>
<h1>LineFollower V2</h1>
<p>Wi-Fi/UART proof of concept</p>
<form id="sendForm">
<input id="cmd" name="cmd" value="START" autocomplete="off">
<button type="submit">Verstuur naar Nano</button>
</form>
<p><button onclick="setCmd('START')">START</button>
<button onclick="setCmd('STOP')">STOP</button></p>
<h2>Laatste UART-bericht van Nano</h2>
<pre id="data">Wachten...</pre>
<script>
const cmd=document.getElementById('cmd');
function setCmd(v){cmd.value=v;sendCommand(v);}
async function sendCommand(v){
  const body=new URLSearchParams(); body.set('cmd',v);
  await fetch('/send',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});
}
document.getElementById('sendForm').addEventListener('submit',async e=>{
  e.preventDefault(); await sendCommand(cmd.value);
});
async function refresh(){
  try{document.getElementById('data').textContent=await (await fetch('/data')).text();}
  catch(e){document.getElementById('data').textContent='Geen verbinding';}
}
setInterval(refresh,500); refresh();
</script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", PAGE);
}

void handleSend() {
  String command = server.arg("cmd");
  command.trim();
  if (command.length() == 0 || command.length() > 120 ||
      command.indexOf('\n') >= 0 || command.indexOf('\r') >= 0) {
    server.send(400, "text/plain", "Ongeldig commando");
    return;
  }
  NanoSerial.println(command);
  server.send(200, "text/plain", "Verzonden: " + command);
}

void handleData() {
  server.send(200, "text/plain; charset=utf-8", lastNanoLine);
}

void setup() {
  Serial.begin(115200);
  NanoSerial.begin(115200, SERIAL_8N1, NANO_RX_PIN, NANO_TX_PIN);
  WiFi.mode(WIFI_AP);
  bool apStarted = false;
  if (LINEFOLLOWER_WIFI_CONFIGURED) {
    apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD);
  } else {
    Serial.println(F("Wi-Fi AP disabled: copy secrets.example.h to secrets.h and set a private password."));
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/send", HTTP_POST, handleSend);
  server.on("/data", HTTP_GET, handleData);
  server.begin();

  Serial.println();
  Serial.println(F("LineFollower Wi-Fi/UART POC"));
  Serial.print(F("AP gestart: "));
  Serial.println(apStarted ? F("ja") : F("nee"));
  Serial.print(F("SSID: "));
  Serial.println(AP_SSID);
  Serial.print(F("IP: "));
  Serial.println(WiFi.softAPIP());
}

void loop() {
  server.handleClient();
  while (NanoSerial.available() > 0) {
    char c = (char)NanoSerial.read();
    if (c == '\n') {
      nanoLine.trim();
      if (nanoLine.length() > 0) {
        lastNanoLine = nanoLine;
        Serial.println(lastNanoLine);
      }
      nanoLine = "";
    } else if (c != '\r') {
      if (nanoLine.length() < 200) nanoLine += c;
      else nanoLine = "";
    }
  }
}
