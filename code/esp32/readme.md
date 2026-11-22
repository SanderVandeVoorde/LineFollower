# Definitieve ESP32-C3-dashboardsoftware

**Broncode:** [ESP32_Programma.ino](./ESP32_Programma.ino)

Dit is de door de gebruiker aangeleverde ESP32-C3 V2.1-firmware voor het LineFollower V2-dashboard. De broncode staat in GitHub. Toevoegen aan de repository is niet hetzelfde als compileren of testen op de robot.

## Functies

- Maakt een eigen Wi-Fi-accesspoint.
- Levert een browserdashboard op `http://192.168.4.1`.
- Ontvangt Nano-telemetrie via UART.
- Stuurt START, STOP en twaalf configuratiewaarden naar de Nano.
- Toont batterijspanning, lijnpositie, genormaliseerde sensorgegevens, encoderpulsen/s, encodertellers en motor-PWM.
- Biedt PID-, snelheid-, bocht- en lijnverliesinstellingen.
- Slaat instellingen op in de ESP32-C3-NVS via Preferences.

## Wi-Fi

| Instelling | Waarde |
|---|---|
| SSID | `Linefollower-V2` |
| Wachtwoord | `linefollow` |
| IP-adres | `192.168.4.1` |
| Dashboard | `http://192.168.4.1` |

Verbind laptop of smartphone met het accesspoint en open het IP-adres in een browser. Het accesspoint heeft geen internetverbinding nodig.

## Aansluitingen

| Signaal | ESP32-C3 | Andere zijde |
|---|---:|---|
| UART RX | GPIO20 | Nano D1/TX via 10 kΩ serie en 20 kΩ naar GND |
| UART TX | GPIO21 | Nano D0/RX |
| Batterijmeting | GPIO0 / ADC | Middelpunt spanningsdeler |
| GND | GND | Gemeenschappelijke GND |
| Voeding | 5V | Gereguleerde 5V volgens het schema |

De Nano werkt met 5V-logica en de ESP32-C3 met 3,3V-logica. Het Nano-TX-signaal mag niet rechtstreeks op ESP32-RX worden aangesloten. Controleer de fysieke UART-schakelaars en spanningsdeler vóór gebruik.

## Batterijspanningsmeting

De bevestigde fysieke spanningsdeler is:
- Bovenste tak: 147 kΩ (100 kΩ + 47 kΩ in serie).
- Onderste tak: 47 kΩ.
- ADC: GPIO0.
- Filtercondensator: 100 nF naar GND.

De code gebruikt:
`BATTERY_FACTOR = (147 + 47) / 47 = 194 / 47`

Bij een volledig geladen 2S LiPo van 8,4 V is de ADC-knooppuntspanning theoretisch ongeveer 2,04 V. De weergegeven spanning moet nog met een multimeter worden vergeleken en zo nodig met een gemeten kalibratiefactor worden gecorrigeerd. De EPLAN-PDF vermeldt momenteel 150 kΩ voor de bovenste tak; pas de EPLAN-bron aan naar 100 kΩ + 47 kΩ in serie en exporteer daarna de PDF opnieuw.

## UART-protocol

Baudrate: 115200, 8N1.

De Nano stuurt telemetrie in deze volgorde:
`T,run,line,pos,raw0..7,norm0..7,leftCount,rightCount,leftPPS,rightPPS,leftPWM,rightPWM`

De ESP32 stuurt:
- `START`
- `STOP`
- `CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi`

De Nano antwoordt op een geldige configuratie met `ACK,CFG`. De ESP32 herhaalt de configuratie totdat deze bevestiging ontvangen is.

## Instellingen bewaren

- **TOEPASSEN:** stuurt de waarden naar de Nano.
- **OPSLAAN:** past de waarden toe en bewaart ze in de ESP32-NVS.
- **STANDAARDWAARDEN:** herstelt de standaardwaarden en bewaart ze.

De instellingen staan dus in de ESP32-opslag, niet in de Nano-EEPROM.

## Starten en stoppen

De robot kan via de fysieke knop op de Nano (D8) worden gestart/gestopt. Het dashboard kan daarnaast START en STOP naar de Nano sturen. Test de draadloze stopfunctie eerst met de aangedreven wielen vrij van de grond.

## Teststatus en beperkingen

- De broncode is door de gebruiker aangeleverd en in GitHub opgenomen.
- De spanningsdelerfactor is afgestemd op de bevestigde fysieke waarden 147 kΩ + 47 kΩ.
- De UART-velden en CFG-volgorde zijn inhoudelijk vergeleken met de Nano-firmware.
- De ESP32-C3-sketch is succesvol gecompileerd door GitHub Actions (run 45034700313). De gecombineerde praktijktest met de Nano en de fysieke batterijmeting moeten nog worden uitgevoerd.
- De batterijmeting moet met een multimeter worden gekalibreerd.
- De gebruiker heeft bevestigd dat de motordrivermodule de DRV8833 is en dat EPLAN de juiste bedrading weergeeft.
