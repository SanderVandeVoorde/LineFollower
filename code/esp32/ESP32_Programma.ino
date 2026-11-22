/*
===========================================================
 HOGENT LINEFOLLOWER V2 - ESP32-C3 V2.1
===========================================================

 WIFI:
 SSID: Linefollower-V2
 PASS: linefollow
 IP:   192.168.4.1

 UART:
 GPIO20 RX <- Nano D1 TX
 GPIO21 TX -> Nano D0 RX

 BATTERIJ:
 GPIO0
 Boven: 147k (100k + 47k)
 Onder: 47k
 ADC condensator: 100nF naar GND

===========================================================
*/

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

const char* WIFI_SSID = "Linefollower-V2";
const char* WIFI_PASSWORD = "linefollow";

WebServer server(80);
HardwareSerial NanoSerial(1);
Preferences preferences;

const int NANO_RX_PIN = 20;
const int NANO_TX_PIN = 21;
const int BATTERY_PIN = 0;

const float BATTERY_FACTOR = 194.0 / 47.0;

struct Settings {
  float baseSpeed = 70;
  int maxPWM = 160;
  int minMotorPWM = 0;
  float kp = 30;
  float ki = 0;
  float kd = 0;
  float turnSlowdown = 0;
  int lineLostTimeout = 80;
  bool speedPIEnabled = false;
  float targetPPS = 800;
  float speedKp = 0.05;
  float speedKi = 0.01;
};

struct Telemetry {
  bool running = false;
  bool lineDetected = false;
  int position = 0;
  int raw[8] = {0};
  int normalized[8] = {0};
  long leftCount = 0;
  long rightCount = 0;
  float leftPPS = 0;
  float rightPPS = 0;
  int leftPWM = 0;
  int rightPWM = 0;
};

Settings settings;
Telemetry telemetry;

float batteryVoltage = 0;
unsigned long lastBatteryRead = 0;
unsigned long lastTelemetryReceived = 0;
unsigned long lastConfigSend = 0;

bool configAcknowledged = false;


// =========================================================
// 1. HTML DASHBOARD
// =========================================================

const char DASHBOARD[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="nl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Linefollower V2</title>
<style>
body{margin:0;padding:15px;background:#10141c;color:#f0f4fa;
font-family:Arial,sans-serif}
main{max-width:1000px;margin:auto}
.card{background:#1a2230;border:1px solid #2b394c;
border-radius:13px;padding:16px;margin-bottom:14px}
h1{font-size:24px}h2{font-size:17px;margin-top:0}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(190px,1fr));gap:10px}
.metric{font-size:25px;font-weight:bold}
.muted{color:#98a8bd;font-size:12px}
.row{display:flex;justify-content:space-between;gap:10px}
.setting{margin:15px 0}
input[type=range]{width:100%;accent-color:#48a9ff}
input[type=number]{width:100%;padding:9px;background:#202b3b;color:white;
border:1px solid #394b61;border-radius:7px}
button{border:0;border-radius:8px;padding:12px 16px;
font-weight:bold;color:white;background:#348ee0;margin:3px}
.green{background:#168b65}.red{background:#c94350}.gray{background:#45546a}
.value{color:#48a9ff;font-weight:bold}
.sensors{display:grid;grid-template-columns:repeat(8,1fr);gap:4px}
.sensor{background:#202b3b;text-align:center;padding:6px 1px;border-radius:6px}
.bar{height:75px;display:flex;align-items:end;justify-content:center}
.fill{width:65%;background:#48a9ff;border-radius:4px 4px 0 0}
.sensor small{font-size:10px}
canvas{width:100%;height:120px;background:#202b3b;border-radius:8px}
@media(max-width:450px){body{padding:8px}.sensor small{font-size:8px}}
</style>
</head>
<body>
<main>
<h1>LINEFOLLOWER V2</h1>
<p class="muted" id="connection">Verbinden...</p>

<div class="grid">
<div class="card"><div class="muted">Batterij</div>
<div class="metric" id="battery">-- V</div></div>
<div class="card"><div class="muted">Lijnpositie</div>
<div class="metric" id="position">0</div>
<div class="muted" id="lineStatus">--</div></div>
<div class="card"><div class="muted">Linker pulsen/s</div>
<div class="metric" id="leftPPS">0</div></div>
<div class="card"><div class="muted">Rechter pulsen/s</div>
<div class="metric" id="rightPPS">0</div></div>
</div>

<div class="card">
<h2>Robotbediening</h2>
<button class="green" onclick="fetch('/start')">START</button>
<button class="red" onclick="fetch('/stop')">STOP</button>
<div class="grid">
<div><p class="muted">Links PWM</p><div class="metric" id="leftPWM">0</div></div>
<div><p class="muted">Rechts PWM</p><div class="metric" id="rightPWM">0</div></div>
<div><p class="muted">Encoder links</p><div id="leftCount">0</div></div>
<div><p class="muted">Encoder rechts</p><div id="rightCount">0</div></div>
</div>
</div>

<div class="card">
<h2>HY-S301 sensoren</h2>
<div class="sensors" id="sensors"></div>
<p class="muted">D1 is links, D8 is rechts. Balken zijn genormaliseerde waarden.</p>
</div>

<div class="card">
<h2>PID lijnvolging</h2>
<div class="setting"><div class="row"><label>Kp</label><span class="value" id="kpVal">30</span></div>
<input id="kp" type="range" min="0" max="100" step=".5" value="30"></div>
<div class="setting"><div class="row"><label>Ki</label><span class="value" id="kiVal">0</span></div>
<input id="ki" type="range" min="0" max="5" step=".01" value="0"></div>
<div class="setting"><div class="row"><label>Kd</label><span class="value" id="kdVal">0</span></div>
<input id="kd" type="range" min="0" max="100" step=".5" value="0"></div>
</div>

<div class="card">
<h2>Snelheid en bochten</h2>
<div class="setting"><div class="row"><label>Basissnelheid</label><span class="value" id="baseVal">70</span></div>
<input id="base" type="range" min="0" max="160" value="70"></div>
<div class="setting"><div class="row"><label>Maximale PWM</label><span class="value" id="maxVal">160</span></div>
<input id="max" type="range" min="50" max="255" value="160"></div>
<div class="setting"><div class="row"><label>Minimale PWM</label><span class="value" id="minVal">0</span></div>
<input id="min" type="range" min="0" max="150" value="0"></div>
<div class="setting"><div class="row"><label>Bochtvertraging</label><span class="value" id="turnVal">0%</span></div>
<input id="turn" type="range" min="0" max="80" value="0"></div>
</div>

<div class="card">
<h2>Encoder snelheidsregeling</h2>
<label><input type="checkbox" id="speedPI"> PI-snelheidsregeling inschakelen</label>
<div class="setting"><label>Gewenste snelheid (pulsen/s)</label>
<input type="number" id="targetPPS" value="800" min="50" max="3000"></div>
<div class="setting"><label>PI Kp</label>
<input type="number" id="speedKp" value=".05" min="0" max="1" step=".01"></div>
<div class="setting"><label>PI Ki</label>
<input type="number" id="speedKi" value=".01" min="0" max=".5" step=".001"></div>
<p class="muted">Laat PI uit tot de gewone lijnvolging goed werkt.</p>
</div>

<div class="card">
<h2>Lijnverlies</h2>
<div class="row"><label>Time-out</label><span class="value" id="timeoutVal">80 ms</span></div>
<input id="timeout" type="range" min="20" max="1000" step="10" value="80">
</div>

<div class="card">
<h2>Instellingen</h2>
<button onclick="applySettings()">TOEPASSEN</button>
<button class="green" onclick="saveSettings()">OPSLAAN</button>
<button class="gray" onclick="defaults()">STANDAARDWAARDEN</button>
<p class="muted" id="message">Instellingen nog niet gewijzigd.</p>
</div>

<div class="card">
<h2>Lijnpositie - live</h2>
<canvas id="chart" width="900" height="220"></canvas>
</div>
</main>

<script>
const ids=['kp','ki','kd','base','max','min','turn','timeout'];
const suffix={turn:'%',timeout:' ms'};
for(const id of ids){
 document.getElementById(id).addEventListener('input',()=>{
  document.getElementById(id+'Val').textContent=
   document.getElementById(id).value+(suffix[id]||'');
 });
}
const sensorBox=document.getElementById('sensors');
for(let i=0;i<8;i++){
 let e=document.createElement('div');
 e.className='sensor';
 e.innerHTML='<small>D'+(i+1)+'</small><div class="bar"><div class="fill" id="bar'+i+'"></div></div><small id="s'+i+'">0</small>';
 sensorBox.appendChild(e);
}
function val(id){return document.getElementById(id).value}
function settingsFromUI(){
 return {
  base:val('base'),max:val('max'),min:val('min'),
  kp:val('kp'),ki:val('ki'),kd:val('kd'),
  turn:val('turn'),timeout:val('timeout'),
  speedPI:document.getElementById('speedPI').checked?1:0,
  targetPPS:val('targetPPS'),
  speedKp:val('speedKp'),speedKi:val('speedKi')
 };
}
function setUI(s){
 const m={base:'baseSpeed',max:'maxPWM',min:'minMotorPWM',
 kp:'kp',ki:'ki',kd:'kd',turn:'turnSlowdown',timeout:'lineLostTimeout'};
 for(const id in m){
  document.getElementById(id).value=s[m[id]];
  document.getElementById(id+'Val').textContent=s[m[id]]+(suffix[id]||'');
 }
 document.getElementById('speedPI').checked=s.speedPIEnabled;
 document.getElementById('targetPPS').value=s.targetPPS;
 document.getElementById('speedKp').value=s.speedKp;
 document.getElementById('speedKi').value=s.speedKi;
}
async function waitForConfigAck(timeoutMs=1500){
 const deadline=Date.now()+timeoutMs;
 while(Date.now()<deadline){
  const r=await fetch('/api');
  const d=await r.json();
  if(d.configAcknowledged)return true;
  await new Promise(resolve=>setTimeout(resolve,100));
 }
 return false;
}
async function applySettings(){
 try{
  const q=new URLSearchParams(settingsFromUI());
  const r=await fetch('/set?'+q);
  const d=await r.json();
  const ack=d.ok?await waitForConfigAck():false;
  document.getElementById('message').textContent=
   ack?'Configuratie bevestigd door Nano.':
   'Niet bevestigd door Nano. Controleer de verbinding.';
  return ack;
 }catch(e){
  document.getElementById('message').textContent='Verzenden mislukt.';
  return false;
 }
}
async function saveSettings(){
 const ack=await applySettings();
 try{
  const r=await fetch('/save');
  const d=await r.json();
  document.getElementById('message').textContent=
   !d.ok?'Opslaan mislukt.':
   (ack?'Opgeslagen op ESP32 en bevestigd door Nano.':
   'Opgeslagen op ESP32; Nano heeft de configuratie niet bevestigd.');
 }catch(e){
  document.getElementById('message').textContent='Opslaan mislukt.';
 }
}
async function defaults(){
 if(!confirm('Terug naar standaardwaarden?'))return;
 try{
  const r=await fetch('/defaults');
  const d=await r.json();
  if(d.settings)setUI(d.settings);
  const ack=await waitForConfigAck();
  document.getElementById('message').textContent=
   ack?'Standaardwaarden opgeslagen en bevestigd door Nano.':
   'Standaardwaarden opgeslagen op ESP32; Nano heeft niet bevestigd.';
 }catch(e){
  document.getElementById('message').textContent='Herstellen mislukt.';
 }
}
let history=[];
function draw(p){
 history.push(p);if(history.length>100)history.shift();
 const c=document.getElementById('chart'),x=c.getContext('2d');
 x.clearRect(0,0,c.width,c.height);
 x.strokeStyle='#405067';
 for(let i=0;i<5;i++){x.beginPath();x.moveTo(0,i*c.height/4);x.lineTo(c.width,i*c.height/4);x.stroke();}
 x.strokeStyle='#48a9ff';x.lineWidth=3;x.beginPath();
 history.forEach((v,i)=>{
  const px=i*c.width/99,py=c.height/2-v/3500*c.height/2;
  if(i===0)x.moveTo(px,py);else x.lineTo(px,py);
 });
 x.stroke();
}
async function update(){
 try{
  const r=await fetch('/api');const d=await r.json();
  document.getElementById('connection').textContent=
   !d.connected?'Nano niet verbonden':
   (d.configAcknowledged?'Nano verbonden · configuratie bevestigd':'Nano verbonden · configuratie wordt bevestigd');
  document.getElementById('battery').textContent=d.battery.toFixed(2)+' V';
  document.getElementById('position').textContent=d.position;
  document.getElementById('lineStatus').textContent=d.lineDetected?'Lijn gedetecteerd':'Geen lijn';
  document.getElementById('leftPPS').textContent=d.leftPPS.toFixed(1);
  document.getElementById('rightPPS').textContent=d.rightPPS.toFixed(1);
  document.getElementById('leftPWM').textContent=d.leftPWM;
  document.getElementById('rightPWM').textContent=d.rightPWM;
  document.getElementById('leftCount').textContent=d.leftCount;
  document.getElementById('rightCount').textContent=d.rightCount;
  for(let i=0;i<8;i++){
   const v=d.normalized[i]||0;
   document.getElementById('s'+i).textContent=v;
   document.getElementById('bar'+i).style.height=(v/1000*75)+'px';
  }
  draw(d.position);
 }catch(e){
  document.getElementById('connection').textContent='Dashboardverbinding verloren';
 }
}
async function initialize(){
 try{const r=await fetch('/api');const d=await r.json();setUI(d.settings);}catch(e){}
}
initialize();
update();
setInterval(update,250);
</script>
</body>
</html>
)rawliteral";


// =========================================================
// 2. INSTELLINGEN OPSLAAN EN LADEN
// =========================================================

void saveSettings() {
  preferences.begin("linefollower", false);

  preferences.putFloat("base", settings.baseSpeed);
  preferences.putInt("max", settings.maxPWM);
  preferences.putInt("min", settings.minMotorPWM);

  preferences.putFloat("kp", settings.kp);
  preferences.putFloat("ki", settings.ki);
  preferences.putFloat("kd", settings.kd);

  preferences.putFloat("turn", settings.turnSlowdown);
  preferences.putInt("timeout", settings.lineLostTimeout);

  preferences.putBool("speedPI", settings.speedPIEnabled);
  preferences.putFloat("targetPPS", settings.targetPPS);
  preferences.putFloat("speedKp", settings.speedKp);
  preferences.putFloat("speedKi", settings.speedKi);

  preferences.end();
}


void loadSettings() {
  preferences.begin("linefollower", true);

  settings.baseSpeed = preferences.getFloat("base", 70);
  settings.maxPWM = preferences.getInt("max", 160);
  settings.minMotorPWM = preferences.getInt("min", 0);

  settings.kp = preferences.getFloat("kp", 30);
  settings.ki = preferences.getFloat("ki", 0);
  settings.kd = preferences.getFloat("kd", 0);

  settings.turnSlowdown = preferences.getFloat("turn", 0);
  settings.lineLostTimeout = preferences.getInt("timeout", 80);

  settings.speedPIEnabled = preferences.getBool("speedPI", false);
  settings.targetPPS = preferences.getFloat("targetPPS", 800);
  settings.speedKp = preferences.getFloat("speedKp", 0.05);
  settings.speedKi = preferences.getFloat("speedKi", 0.01);

  preferences.end();
}


// =========================================================
// 3. CONFIGURATIE NAAR NANO
// =========================================================

void sendConfiguration() {
  NanoSerial.printf(
    "CFG,%.2f,%d,%.3f,%.3f,%.3f,%d,%.2f,%d,%d,%.1f,%.4f,%.4f\n",
    settings.baseSpeed,
    settings.maxPWM,
    settings.kp,
    settings.ki,
    settings.kd,
    settings.minMotorPWM,
    settings.turnSlowdown,
    settings.lineLostTimeout,
    settings.speedPIEnabled ? 1 : 0,
    settings.targetPPS,
    settings.speedKp,
    settings.speedKi
  );

  configAcknowledged = false;
  lastConfigSend = millis();
}


// =========================================================
// 4. TELEMETRIE PARSEN
// =========================================================

void parseTelemetry(String line) {
  if (line.startsWith("ACK,CFG")) {
    configAcknowledged = true;
    return;
  }

  if (!line.startsWith("T,")) return;

  char buffer[350];
  line.toCharArray(buffer, sizeof(buffer));

  char* tokens[30];
  byte count = 0;

  char* token = strtok(buffer, ",");

  while (token != NULL && count < 30) {
    tokens[count++] = token;
    token = strtok(NULL, ",");
  }

  if (count < 26) return;

  telemetry.running = atoi(tokens[1]) != 0;
  telemetry.lineDetected = atoi(tokens[2]) != 0;
  telemetry.position = atoi(tokens[3]);

  for (byte i = 0; i < 8; i++) {
    telemetry.raw[i] = atoi(tokens[4 + i]);
    telemetry.normalized[i] = atoi(tokens[12 + i]);
  }

  telemetry.leftCount = atol(tokens[20]);
  telemetry.rightCount = atol(tokens[21]);

  telemetry.leftPPS = atof(tokens[22]);
  telemetry.rightPPS = atof(tokens[23]);

  telemetry.leftPWM = atoi(tokens[24]);
  telemetry.rightPWM = atoi(tokens[25]);

  lastTelemetryReceived = millis();
}


void readNanoSerial() {
  static String input = "";

  while (NanoSerial.available()) {
    char c = NanoSerial.read();

    if (c == '\n') {
      input.trim();
      if (input.length() > 0) parseTelemetry(input);
      input = "";
    } else if (c != '\r') {
      if (input.length() < 300) input += c;
      else input = "";
    }
  }
}


// =========================================================
// 5. BATTERIJMETING
// =========================================================

void updateBattery() {
  if (millis() - lastBatteryRead < 500) return;

  lastBatteryRead = millis();

  uint32_t millivolts = analogReadMilliVolts(BATTERY_PIN);

  float adcVoltage = millivolts / 1000.0;
  float measured = adcVoltage * BATTERY_FACTOR;

  if (batteryVoltage == 0) {
    batteryVoltage = measured;
  } else {
    batteryVoltage = batteryVoltage * 0.8 + measured * 0.2;
  }
}


// =========================================================
// 6. JSON
// =========================================================

String settingsJSON() {
  String j = "{";

  j += "\"baseSpeed\":" + String(settings.baseSpeed, 2) + ",";
  j += "\"maxPWM\":" + String(settings.maxPWM) + ",";
  j += "\"minMotorPWM\":" + String(settings.minMotorPWM) + ",";

  j += "\"kp\":" + String(settings.kp, 3) + ",";
  j += "\"ki\":" + String(settings.ki, 3) + ",";
  j += "\"kd\":" + String(settings.kd, 3) + ",";

  j += "\"turnSlowdown\":" + String(settings.turnSlowdown, 2) + ",";
  j += "\"lineLostTimeout\":" + String(settings.lineLostTimeout) + ",";

  j += "\"speedPIEnabled\":";
  j += settings.speedPIEnabled ? "true" : "false";
  j += ",";

  j += "\"targetPPS\":" + String(settings.targetPPS, 1) + ",";
  j += "\"speedKp\":" + String(settings.speedKp, 4) + ",";
  j += "\"speedKi\":" + String(settings.speedKi, 4);

  j += "}";

  return j;
}


String telemetryJSON() {
  bool connected =
    lastTelemetryReceived != 0 &&
    millis() - lastTelemetryReceived < 1500;

  String j = "{";

  j += "\"connected\":";
  j += connected ? "true" : "false";
  j += ",";

  j += "\"configAcknowledged\":";
  j += configAcknowledged ? "true" : "false";
  j += ",";
  
  j += "\"battery\":" + String(batteryVoltage, 3) + ",";
  j += "\"running\":";
  j += telemetry.running ? "true" : "false";
  j += ",";

  j += "\"lineDetected\":";
  j += telemetry.lineDetected ? "true" : "false";
  j += ",";

  j += "\"position\":" + String(telemetry.position) + ",";

  j += "\"leftCount\":" + String(telemetry.leftCount) + ",";
  j += "\"rightCount\":" + String(telemetry.rightCount) + ",";

  j += "\"leftPPS\":" + String(telemetry.leftPPS, 1) + ",";
  j += "\"rightPPS\":" + String(telemetry.rightPPS, 1) + ",";

  j += "\"leftPWM\":" + String(telemetry.leftPWM) + ",";
  j += "\"rightPWM\":" + String(telemetry.rightPWM) + ",";

  j += "\"normalized\":[";
  for (byte i = 0; i < 8; i++) {
    j += String(telemetry.normalized[i]);
    if (i < 7) j += ",";
  }

  j += "],\"settings\":";
  j += settingsJSON();
  j += "}";

  return j;
}


// =========================================================
// 7. HTTP HANDLERS
// =========================================================

void handleRoot() {
  server.send_P(200, "text/html", DASHBOARD);
}


void handleAPI() {
  server.send(200, "application/json", telemetryJSON());
}


void updateSettingsFromRequest() {
  if (server.hasArg("base"))
    settings.baseSpeed = constrain(server.arg("base").toFloat(), 0, 200);

  if (server.hasArg("max"))
    settings.maxPWM = constrain(server.arg("max").toInt(), 50, 255);

  if (server.hasArg("min"))
    settings.minMotorPWM = constrain(server.arg("min").toInt(), 0, 150);

  if (server.hasArg("kp"))
    settings.kp = constrain(server.arg("kp").toFloat(), 0, 100);

  if (server.hasArg("ki"))
    settings.ki = constrain(server.arg("ki").toFloat(), 0, 5);

  if (server.hasArg("kd"))
    settings.kd = constrain(server.arg("kd").toFloat(), 0, 100);

  if (server.hasArg("turn"))
    settings.turnSlowdown = constrain(server.arg("turn").toFloat(), 0, 80);

  if (server.hasArg("timeout"))
    settings.lineLostTimeout = constrain(server.arg("timeout").toInt(), 20, 1000);

  if (server.hasArg("speedPI"))
    settings.speedPIEnabled = server.arg("speedPI").toInt() == 1;

  if (server.hasArg("targetPPS"))
    settings.targetPPS = constrain(server.arg("targetPPS").toFloat(), 50, 3000);

  if (server.hasArg("speedKp"))
    settings.speedKp = constrain(server.arg("speedKp").toFloat(), 0, 1);

  if (server.hasArg("speedKi"))
    settings.speedKi = constrain(server.arg("speedKi").toFloat(), 0, 0.5);
}


void handleSet() {
  updateSettingsFromRequest();
  sendConfiguration();

  server.send(200, "application/json", "{\"ok\":true}");
}


void handleSave() {
  saveSettings();
  server.send(200, "application/json", "{\"ok\":true}");
}


void handleDefaults() {
  settings = Settings();

  saveSettings();
  sendConfiguration();

  String j = "{\"ok\":true,\"settings\":";
  j += settingsJSON();
  j += "}";

  server.send(200, "application/json", j);
}


void handleStart() {
  NanoSerial.println("START");
  server.send(200, "application/json", "{\"ok\":true}");
}


void handleStop() {
  NanoSerial.println("STOP");
  server.send(200, "application/json", "{\"ok\":true}");
}


// =========================================================
// 8. SETUP
// =========================================================

void setup() {
  Serial.begin(115200);

  NanoSerial.begin(
    115200,
    SERIAL_8N1,
    NANO_RX_PIN,
    NANO_TX_PIN
  );

  pinMode(BATTERY_PIN, INPUT);

  analogReadResolution(12);
  analogSetPinAttenuation(BATTERY_PIN, ADC_11db);

  loadSettings();

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(
    IPAddress(192, 168, 4, 1),
    IPAddress(192, 168, 4, 1),
    IPAddress(255, 255, 255, 0)
  );

  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api", HTTP_GET, handleAPI);
  server.on("/set", HTTP_GET, handleSet);
  server.on("/save", HTTP_GET, handleSave);
  server.on("/defaults", HTTP_GET, handleDefaults);
  server.on("/start", HTTP_GET, handleStart);
  server.on("/stop", HTTP_GET, handleStop);

  server.begin();

  sendConfiguration();
}


// =========================================================
// 9. LOOP
// =========================================================

void loop() {
  server.handleClient();

  readNanoSerial();
  updateBattery();

  // Detecteer een Nano die opnieuw opstart. Zodra telemetrie terugkomt,
  // stuur de bewaarde instellingen opnieuw naar de Nano.
  static bool nanoWasConnected = false;
  bool nanoConnected =
    lastTelemetryReceived != 0 &&
    millis() - lastTelemetryReceived < 1500;

  if (nanoConnected && !nanoWasConnected) {
    sendConfiguration();
  }
  nanoWasConnected = nanoConnected;

  // Herhaal configuratie tot de Nano de instellingen bevestigt.
  if (!configAcknowledged &&
      millis() - lastConfigSend > 1000) {
    sendConfiguration();
  }
}
