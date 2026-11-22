# Draadloze communicatie proof of concept

Dit programma is een afzonderlijke test van de Wi-Fi- en UART-communicatie tussen een browser, de ESP32-C3 en de Arduino Nano.

**POC-broncode:** [ESP32_WiFi_UART_POC.ino](./ESP32_WiFi_UART_POC.ino)

**Afzonderlijk POC-schema:** [Wireless_POC_Schema.svg](./Wireless_POC_Schema.svg)

De geïntegreerde dashboardfirmware staat apart in [code/esp32](../../esp32/).

## Architectuur

1. De ESP32-C3 maakt een eigen Wi-Fi-accesspoint.
2. Een laptop of smartphone verbindt met dat accesspoint.
3. De browser opent de lokale webpagina op de ESP32.
4. Een commando wordt via HTTP naar de ESP32 gestuurd.
5. De ESP32 stuurt het commando via UART door naar de Nano.
6. De Nano stuurt bijvoorbeeld een ACK- of T-telemetrieregel terug.
7. De ESP32 toont de laatst ontvangen UART-regel in de browser.

## Wi-Fi-configuratie van deze POC

| Instelling | Waarde |
|---|---|
| SSID | Linefollower-V2 (aanpasbaar in secrets.h) |
| Wachtwoord | Eigen waarde in lokale secrets.h; niet publiceren |
| IP-adres | 192.168.4.1 |
| Webpagina | http://192.168.4.1 |
| UART | 115200 baud, 8N1 |

Kopieer [secrets.example.h](./secrets.example.h) naar secrets.h in dezelfde map en stel een eigen wachtwoord van minstens acht tekens in. secrets.h staat in .gitignore en mag niet naar GitHub worden gepusht. De fallback in de broncode is alleen bedoeld om de CI-build te laten compileren; wijzig die vóór je de POC gebruikt.

## UART-aansluitingen

| Signaal | Van | Naar |
|---|---|---|
| Nano TX | D1 / TX | ESP32 GPIO20 / RX via spanningsdeler |
| ESP32 TX | GPIO21 / TX | Nano D0 / RX |
| GND | Nano GND | ESP32 GND |

De Nano werkt op 5V-logica en de ESP32-C3 op 3,3V-logica. Verbind Nano-TX niet rechtstreeks met ESP32-RX. De voorziene spanningsdeler gebruikt 10 kΩ in serie naar het RX-knooppunt en 20 kΩ van dat knooppunt naar GND.

## Verschil tussen POC en geïntegreerde firmware

- De POC toont de laatst ontvangen UART-regel en stuurt eenvoudige commando's door.
- De geïntegreerde firmware toont sensoren, lijnpositie, encoderwaarden, motorsnelheden, batterijspanning en PID-instellingen.
- De geïntegreerde firmware bewaart dashboardinstellingen in ESP32-NVS en stuurt de CFG-configuratie opnieuw naar de Nano.
- De POC is bedoeld om de communicatie afzonderlijk te testen; gebruik voor de normale robotbediening de geïntegreerde firmware uit `code/esp32`.

## Teststatus

De broncode van zowel de POC als de geïntegreerde dashboardfirmware staat in GitHub en beide sketches compileren in de automatische build. De gebruiker bevestigde op 22-11-2026 dat de oorspronkelijke browser↔ESP32↔UART↔Nano-keten werkt, inclusief START/STOP en CFG/ACK. De nieuwe secrets.h-configuratie moet na deze repository-update nog lokaal worden ingesteld en opnieuw getest. De meet- en statusnotitie staat in [TEST_RESULTS.md](../../../TEST_RESULTS.md).
