# Draadloze communicatie proof of concept

Doel: aantonen dat gegevens in twee richtingen kunnen worden uitgewisseld tussen een laptop/smartphone en de Arduino Nano via Wi-Fi en de ESP32-C3.

**ESP32-broncode:** [ESP32_WiFi_UART_POC.ino](./ESP32_WiFi_UART_POC.ino)

## Architectuur

1. De ESP32-C3 maakt een eigen Wi-Fi access point.
2. Een laptop of smartphone verbindt met dat access point.
3. De browser opent de lokale webpagina op de ESP32.
4. Een commando wordt via HTTP naar de ESP32 gestuurd.
5. De ESP32 stuurt het commando via UART door naar de Nano.
6. De Nano stuurt bijvoorbeeld een ACK- of T-telemetrieregel terug.
7. De ESP32 toont de laatst ontvangen UART-regel in de browser.

## Wi-Fi-configuratie van deze POC

| Instelling | Waarde |
|---|---|
| SSID | Linefollower-V2 |
| Wachtwoord | linefollow |
| IP-adres | 192.168.4.1 |
| Webpagina | http://192.168.4.1 |
| UART | 115200 baud, 8N1 |

Het wachtwoord staat als standaardwaarde in de POC-broncode en kan daar worden aangepast. Dit zijn de instellingen van deze testsketch; ze bewijzen niet dat dezelfde instellingen in een andere ESP32-firmware actief zijn.

## UART-aansluitingen

| Signaal | Van | Naar |
|---|---|---|
| Nano TX | D1 / TX | ESP32 GPIO20 / RX via spanningsdeler |
| ESP32 TX | GPIO21 / TX | Nano D0 / RX |
| GND | Nano GND | ESP32 GND |

De Nano werkt op 5V-logica en de ESP32-C3 op 3,3V-logica. Verbind een 5V-TX-signaal niet rechtstreeks met de ESP32-RX. De voorziene spanningsdeler gebruikt 10 kΩ in serie naar het RX-knooppunt en 20 kΩ van dat knooppunt naar GND. Controleer de werkelijk gemonteerde weerstandswaarden en de spanning op het knooppunt.

De ESP32-TX naar de Nano-RX is in de huidige ontwerpnotities rechtstreeks verbonden. Controleer de logicaniveaus en betrouwbare werking op de concrete borden.

## Testprocedure

1. Upload deze sketch naar de ESP32-C3 Super Mini.
2. Verbind de UART volgens het schema en verbind de GND's.
3. Upload de finale Nano-firmware. Verbreek de UART-verbinding tijdelijk als die de USB-upload verstoort.
4. Schakel de robotvoeding in.
5. Verbind laptop of smartphone met Linefollower-V2.
6. Open http://192.168.4.1.
7. Verstuur START en STOP. Controleer of de Nano hierop reageert.
8. Controleer of telemetrie van de Nano op de webpagina verschijnt.

## Belangrijke beperking

Dit is een minimale communicatie-POC en geen volledige definitieve dashboardapplicatie. De sketch toont alleen de laatst ontvangen UART-regel en stuurt tekstcommando's door. De code is nog niet als definitieve firmware op de robot gevalideerd.

## Veiligheid en foutopsporing

- Verbind altijd de GND van beide microcontrollers.
- Gebruik de spanningsdeler op Nano-TX naar ESP32-RX.
- Controleer GPIO20 en GPIO21 op de gebruikte Super Mini-revisie.
- Als USB-upload naar de Nano mislukt, koppel dan de UART-signalen tijdelijk los.
- Als de webpagina werkt maar er geen data verschijnt, controleer baudrate, TX/RX-kruising, GND en of de Nano telemetrie uitstuurt.
