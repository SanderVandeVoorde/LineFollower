# Definitieve ESP32-C3-dashboardsoftware

**Broncode:** [ESP32_Programma.ino](./ESP32_Programma.ino)

Dit is de ESP32-C3 V2.1-firmware voor het LineFollower V2-dashboard. De gebruiker bevestigde op 22-11-2026 dat de vorige dashboardintegratie fysiek werkte. De nieuwe debug-, EEPROM-ACK-, calibratie- en secrets-aanpassingen moeten nog op de robot worden getest.

## Functies

- Maakt een eigen Wi-Fi-accesspoint.
- Levert een browserdashboard op `http://192.168.4.1`.
- Ontvangt Nano-telemetrie via UART.
- Stuurt START, STOP, dertien configuratiewaarden en calibratiecommando's naar de Nano.
- Toont batterijspanning, lijnpositie, ruwe en genormaliseerde sensorgegevens, encoderpulsen/s, encodertellers en motor-PWM. Een optionele debugweergave toont PID- en snelheidsintegratoren.
- Biedt PID-, snelheid-, bocht-, lijnverlies- en debuginstellingen. De gebruiker kan witte en zwarte sensorwaarden handmatig vastleggen.
- Slaat instellingen op in de ESP32-C3-NVS via Preferences.

## Wi-Fi

| Instelling | Waarde |
|---|---|
| SSID | `Linefollower-V2` |
| Wachtwoord | Eigen waarde in lokaal `secrets.h`; niet in GitHub opslaan |
| IP-adres | `192.168.4.1` |
| Dashboard | `http://192.168.4.1` |

Kopieer `secrets.example.h` naar `secrets.h` in deze map en stel een uniek wachtwoord in. Het echte bestand wordt door .gitignore uitgesloten. Verbind daarna laptop of smartphone met het accesspoint en open het IP-adres in een browser. Het accesspoint heeft geen internetverbinding nodig. De fallback in de broncode is alleen voor compilatie; zonder secrets.h start het accesspoint niet. De fallback is geen productiewachtwoord.

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

EPLAN vermeldt 150 kΩ als nominale ontwerpwaarde. De gemonteerde robot gebruikt 147 kΩ (100 kΩ + 47 kΩ in serie), 47 kΩ naar GND, GPIO0 als ADC en 100 nF naar GND. De gebruiker wil EPLAN bewust op 150 kΩ laten staan; de firmwarefactor blijft afgestemd op de werkelijk gemonteerde 147 kΩ.

De code gebruikt de werkelijke gemonteerde deler:
`BATTERY_FACTOR = (147 + 47) / 47 = 194 / 47`

Bij een volledig geladen 2S LiPo van 8,4 V is de ADC-knooppuntspanning theoretisch ongeveer 2,04 V met de fysieke 147 kΩ-deler. Er is geen reden om de EPLAN-PDF aan te passen.

## UART-protocol

Baudrate: 115200, 8N1.

De Nano stuurt telemetrie in deze volgorde:
`T,run,line,pos,raw0..7,norm0..7,leftCount,rightCount,leftPPS,rightPPS,leftPWM,rightPWM`

De ESP32 stuurt:
- `START`
- `STOP`
- `CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi`

De Nano antwoordt op een geldige configuratie met `ACK,CFG`. De ESP32 herhaalt de configuratie totdat deze bevestiging ontvangen is. Als de Nano later opnieuw opstart en de telemetrie terugkomt, stuurt de ESP32 de opgeslagen instellingen opnieuw.

## Instellingen bewaren en sensorcalibratie

- **TOEPASSEN:** stuurt de waarden naar de Nano en wacht op `ACK,CFG`.
- **OPSLAAN:** bewaart de waarden in ESP32-NVS én stuurt `SAVE` naar de Nano. De Nano bewaart alle configuratie-instellingen en de wit-/zwartcalibratie in zijn interne EEPROM. Het dashboard wacht op `ACK,EEPROM`.
- **STANDAARDWAARDEN:** herstelt de standaardwaarden en bewaart ze in beide niet-vluchtige geheugens.
- **Debug:** schakelt een aanvullende diagnostische UART-regel in; de dashboardweergave toont ruwe ADC-waarden en PID-/PI-integratoren.
- **Wit/zwart vastleggen:** stop de robot en plaats de volledige sensorarray eerst boven wit en daarna boven zwart. De Nano neemt 32 monsters per kanaal, controleert het contrast en bewaart de waarden in EEPROM.

De Nano laadt de laatst geldige configuratie en calibratie uit EEPROM bij het opstarten. De ESP32 laadt daarnaast zijn eigen dashboardinstellingen uit NVS en synchroniseert die via UART.

## Starten en stoppen

De robot kan via de fysieke knop op de Nano (D8) worden gestart/gestopt. Het dashboard kan daarnaast START en STOP naar de Nano sturen. Test de draadloze stopfunctie eerst met de aangedreven wielen vrij van de grond.

## Teststatus en beperkingen

- De broncode is door de gebruiker aangeleverd en in GitHub opgenomen.
- De spanningsdelerfactor is afgestemd op de bevestigde fysieke waarden 147 kΩ + 47 kΩ.
- De UART-velden en CFG-volgorde zijn inhoudelijk vergeleken met de Nano-firmware.
- De eerdere ESP32-C3-sketch en Nano-sketch compileerden succesvol via GitHub Actions. De nieuwe EEPROM-, debug-, calibratie- en secrets-aanpassingen moeten na deze revisie opnieuw worden gecompileerd en fysiek getest.
- Na een herstart van de Nano detecteert de ESP32 de terugkerende telemetrie en stuurt de bewaarde instellingen opnieuw.
- De gebruiker bevestigt dat de batterijspanningsmeting fysiek werkt. Een exacte afwijking ten opzichte van de multimeter is niet als numerieke waarde geregistreerd in deze repository.
- De gebruiker heeft bevestigd dat de motordrivermodule de DRV8833 is en dat EPLAN de juiste bedrading weergeeft.
