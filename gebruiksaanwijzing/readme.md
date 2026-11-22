# Gebruiksaanwijzing – LineFollower V2

Deze handleiding beschrijft het gebruik van de Nano-firmware en het ESP32-C3-dashboard. De software is in GitHub opgenomen; voer de controles uit de projectstatus uit voordat je een nieuwe firmwareversie als getest beschouwt.

## 1. Veiligheid

- Gebruik uitsluitend de voorziene 2S LiPo-batterij: 7,4 V nominaal en 8,4 V volledig geladen.
- Controleer de polariteit van de batterijconnector vóór het inschakelen.
- Gebruik een geschikte 2S-balanslaadinstelling en volg de handleiding van de concrete lader.
- Gebruik geen beschadigde, opgezwollen of abnormaal warme LiPo.
- Zet de robot op een steun wanneer motoren of draairichtingen worden getest.
- Schakel de hoofdvoeding uit vóór je bedrading wijzigt.
- Controleer dat batterijplus en GND niet kortgesloten zijn.
- Laat motoren en DRV8833 niet langdurig blokkeren.
- Test draadloze START/STOP eerst met de aangedreven wielen vrij van de grond.

## 2. Inschakelen

1. Plaats de robot op een vlakke ondergrond.
2. Controleer of de sensorarray vrij boven de baan hangt; de gemeten sensorhoogte is 3 mm.
3. Controleer dat D1 links en D8 rechts zit.
4. Controleer of de wielen vrij kunnen draaien.
5. Zet de hoofdschakelaar aan.
6. Wacht tot Nano en ESP32-C3 zijn opgestart.

## 3. Starten en stoppen

De fysieke start/stopknop is aangesloten op Nano D8 naar GND en gebruikt INPUT_PULLUP.

- De robot wacht na het inschakelen op de startknop.
- Eén druk start de robot.
- Een volgende druk stopt de robot.
- De power-on-led op D13 brandt zodra de Nano is opgestart en blijft branden zolang de controller gevoed is.

Het dashboard kan eveneens START en STOP naar de Nano sturen.

## 4. ESP32-dashboard

1. Schakel de robot in.
2. Verbind laptop of smartphone met het SSID dat in de lokale `code/esp32/secrets.h` is ingesteld (standaard: **Linefollower-V2**).
3. Gebruik het zelfgekozen wachtwoord uit `secrets.h`; de repository bevat geen werkend wachtwoord.
4. Open **http://192.168.4.1**.
5. Controleer of de status aangeeft dat de Nano verbonden is.

Het dashboard toont:
- Batterijspanning.
- Lijnpositie en lijn-detectiestatus.
- Acht genormaliseerde sensorkanalen.
- Linker- en rechter encoderpulsen per seconde.
- Encodertellers.
- Aangestuurde PWM-waarden.
- Livegrafiek van de lijnpositie.

Het dashboard biedt ook PID-, basissnelheid-, maximale PWM-, minimum PWM-, bochtvertraging-, lijnverlies- en encoder-PI-instellingen.

## 5. Instellingen

- **TOEPASSEN:** stuurt de actuele waarden naar de Nano.
- **OPSLAAN:** past de waarden toe, bewaart ze in ESP32-NVS en stuurt SAVE naar de Nano zodat dezelfde instellingen in de interne Nano-EEPROM worden opgeslagen. Wacht op de bevestiging in het dashboard.
- **STANDAARDWAARDEN:** herstelt en bewaart de standaardwaarden in beide geheugens.
- **Debug:** toont ruwe sensorwaarden en PID-/PI-diagnostiek.
- **WIT VASTLEGGEN / ZWART VASTLEGGEN:** stop de robot, plaats alle sensoren volledig boven de betreffende ondergrond en leg beide oppervlakken afzonderlijk vast. De Nano controleert het contrast en bewaart de waarden in EEPROM.

De Nano laadt de laatste geldige configuratie en calibratie uit EEPROM bij het opstarten. De ESP32 bewaart daarnaast een kopie van de dashboardinstellingen in NVS.

Verhoog de basissnelheid stapsgewijs. Houd de PI-snelheidsregeling uit totdat de gewone lijnvolging stabiel is.

## 6. Seriële communicatie

De Nano en ESP32 gebruiken 115200 baud, 8N1.

Nano-commando's:
- `START`
- `STOP`
- `CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi,debug`

Na een geldige CFG-regel stuurt de Nano `ACK,CFG` terug. De Nano stuurt ongeveer elke 100 ms een telemetrieregel die begint met `T,`.

## 7. Sensorcalibratie

De EPLAN-koppeling is:
- D8 → A0
- D7 → A1
- D6 → A2
- D5 → A3
- D4 → A4
- D3 → A5
- D2 → A6
- D1 → A7

De Nano-code leest daarom A7 tot A0 zodat de logische kanalen D1–D8 van links naar rechts lopen. De acht sensoren zijn eerder fysiek op wit en zwart gemeten; de meetresultaten staan in TEST_RESULTS.md. Herhaal de afzonderlijke sensor-POC alleen wanneer sensorbedrading, sensorarray of pinmapping verandert. De firmware voert geen automatische calibratie bij het opstarten uit. Gebruik de twee dashboardknoppen om handmatig wit en zwart vast te leggen. Doe dit bij stilstaande robot, met alle sensoren volledig boven hetzelfde oppervlak.

## 8. Batterijmeting

De bevestigde spanningsdeler is 147 kΩ boven (100 kΩ + 47 kΩ in serie) en 47 kΩ onder. De ESP32 meet het middelpunt via GPIO0 en gebruikt factor 194/47. Vergelijk de dashboardwaarde met een multimeter; pas de factor alleen aan op basis van een echte meting.

## 9. Sensor- en snelheidsmetingen

De geregistreerde baseline is drie ronden van 4,144 m in 26,08 s, gemiddeld 0,477 m/s. Noteer bij elke nieuwe test:
- baanvariant en gemeten rondeafstand;
- aantal ronden en totale tijd;
- batterijspanning vóór en na de test;
- Kp, Ki, Kd, basissnelheid en maximale PWM;
- lijnverlies, botsingen of mechanische trillingen.

Verhoog snelheid pas nadat de robot betrouwbaar lijnverlies detecteert en veilig stopt.

## 10. Programma's uploaden

1. Upload `code/finaal/Arduino_Programma.ino` naar de Nano.
2. Upload `code/esp32/ESP32_Programma.ino` naar de ESP32-C3 met de juiste boarddefinitie.
3. Koppel zo nodig de UART tijdelijk los tijdens het uploaden van de Nano via USB.
4. Test na upload eerst sensorvolgorde, motoren, encoderwaarden en UART.
5. Voer pas daarna een volledige baanproef uit.
