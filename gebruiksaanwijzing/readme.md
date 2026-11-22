# Gebruiksaanwijzing – LineFollower V2

Deze handleiding beschrijft de bediening van de huidige Arduino Nano-firmware en de afzonderlijke ESP32-Wi-Fi/UART-proof-of-concept. Controleer vóór gebruik dat de elektrische opbouw overeenkomt met de actuele bedrading.

## 1. Veiligheid

- Gebruik uitsluitend de voorziene 2S LiPo-batterij. De nominale spanning is 7,4 V; volledig geladen is dit 8,4 V.
- Controleer de polariteit van de batterijconnector vóór het inschakelen.
- Gebruik een geschikte 2S-balanslaadinstelling en volg de handleiding van de concrete lader. Laat een LiPo nooit onbeheerd laden.
- Gebruik geen beschadigde, opgezwollen of abnormaal warme LiPo.
- Zet de robot op een steun wanneer motoren of draairichtingen worden getest.
- Schakel de hoofdvoeding uit vóór je bedrading wijzigt.
- Controleer dat batterijplus en GND niet kortgesloten zijn.
- Laat motoren en DRV8833 niet langdurig blokkeren.

## 2. Inschakelen

1. Plaats de robot op een vlakke ondergrond.
2. Controleer of de sensorarray vrij boven de baan hangt en D1 links zit.
3. Controleer of de wielen vrij kunnen draaien.
4. Zet de hoofdschakelaar aan.
5. Wacht tot de Nano en eventuele ESP32 zijn opgestart.
6. Controleer de status-led en de Wi-Fi-verbinding indien de ESP32-POC actief is.

## 3. Starten en stoppen

De finale Arduino Nano-firmware gebruikt de fysieke drukknop op **D8**. De knop is aangesloten tussen D8 en GND en de software gebruikt INPUT_PULLUP.

- Eén druk start de robot.
- Een volgende druk stopt de robot.
- De status-led op D13 brandt volgens de software wanneer de robot actief is.

De knop op D8 wordt in de finale code via polling gelezen. De afzonderlijke interrupt-POC gebruikt D2 en is alleen bedoeld om hardware-interrupts te demonstreren.

## 4. Draadloze verbinding

Wanneer de ESP32-Wi-Fi/UART-POC is geladen:

1. Zoek op laptop of smartphone naar het Wi-Fi-netwerk Linefollower-V2.
2. Verbind met het wachtwoord dat in de ESP32-sketch staat (standaard in de POC: linefollow).
3. Open http://192.168.4.1 in een browser.
4. Gebruik START of STOP om een commando naar de Nano te sturen.

De POC toont de laatst ontvangen UART-regel. Dit is geen volledige grafische dashboardweergave. De definitieve ESP32-dashboardfirmware moet nog aan de repository worden toegevoegd zodra de gebruikte broncode beschikbaar is.

## 5. Seriële commando's van de Nano

De Nano gebruikt 115200 baud. Commando's worden afgesloten met een newline.

| Commando | Functie |
|---|---|
| START | Start de robot |
| STOP | Stopt de robot |
| CFG,... | Wijzigt de regelparameters |

### CFG-formaat

Stuur exact twaalf waarden in deze volgorde:

**CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi**

De twaalf waarden na CFG zijn:

1. base: basissnelheid (standaard 70)
2. max: maximale PWM (standaard 160)
3. kp: proportionele PID-factor (standaard 30)
4. ki: integrale PID-factor (standaard 0)
5. kd: differentiële PID-factor (standaard 0)
6. min: minimum PWM (standaard 0)
7. turn: bochtvertraging in procent (standaard 0)
8. timeout: lijnverlies-time-out in milliseconden (standaard 80)
9. speedPI: 0 = uit, 1 = aan (standaard 0)
10. targetPPS: gewenste encoderpulsen per seconde (standaard 800)
11. speedKp: proportionele snelheidsfactor (standaard 0,05)
12. speedKi: integrale snelheidsfactor (standaard 0,01)

Voorbeeld met de standaardinstellingen:

**CFG,70,160,30,0,0,0,0,80,0,800,0.05,0.01**

Na een geldige configuratie antwoordt de Nano met ACK,CFG.

De instellingen worden in deze firmware niet in EEPROM opgeslagen. Na een reset worden de standaardwaarden uit de broncode geladen.

## 6. Sensorcalibratie

De finale Nano-firmware gebruikt vaste calibratiewaarden:

- Wit: 688, 618, 643, 568, 590, 560, 588, 651
- Zwart: 1009, 994, 1003, 990, 997, 996, 994, 1005

Er is in deze firmware geen automatisch kalibratiecommando. Als sensorhoogte, sensorarray of ondergrond verandert, moeten de waarden opnieuw worden gemeten met de sensor-POC en gecontroleerd in de firmware worden aangepast.

Fysieke volgorde: D1 links (A0) tot D8 rechts (A7). De berekende lijnpositie loopt van -3500 links tot +3500 rechts.

## 7. Standaardinstellingen

| Parameter | Waarde |
|---|---:|
| Basissnelheid | 70 |
| Maximale PWM | 160 |
| Kp | 30 |
| Ki | 0 |
| Kd | 0 |
| Bochtvertraging | 0% |
| Lijnverlies-time-out | 80 ms |
| Snelheids-PI | Uit |

Verander bij het tunen één parameter tegelijk en noteer elke test. Verhoog de snelheid pas nadat de robot betrouwbaar stopt bij lijnverlies en de motoren correct reageren.

## 8. Telemetrie

De Nano stuurt ongeveer elke 100 ms een regel die begint met T,. De regel bevat run-status, lijn-detectiestatus, lijnpositie, acht ruwe sensorwaarden, acht genormaliseerde sensorwaarden, beide encodertellers, beide pulssnelheden en beide aangestuurde motorsnelheden.

## 9. Programma uploaden

1. Verbind de Nano via USB met de pc.
2. Selecteer het juiste Nano/ATmega328P-bord en de juiste processorvariant in de Arduino IDE.
3. Open code/finaal/Arduino_Programma.ino.
4. Selecteer de juiste COM-poort.
5. Upload de code.
6. Als uploaden mislukt, koppel dan de UART-draden naar de ESP32 tijdelijk los. De Nano-USB-interface deelt de seriële D0/D1-pinnen.
7. Test de robot eerst met de wielen vrij van de grond.

## 10. Probleemoplossing

| Probleem | Controle |
|---|---|
| Geen motorbeweging | Batterijspanning, gemeenschappelijke GND, DRV8833-voeding, nSLEEP van de breakout en motorbedrading |
| Motor draait verkeerd | Motorpolariteit en software-inversie controleren |
| Robot volgt lijn niet | Sensorvolgorde D1–D8, sensorhoogte, zwart/witwaarden en sensor-POC |
| Robot stopt onverwacht | Lijnsterkte, lijnverlies-time-out en sensorwaarden controleren |
| Geen UART-data | Baudrate 115200, TX/RX kruisen, GND en spanningsdeler controleren |
| Nano uploadt niet | UART naar ESP32 tijdelijk loskoppelen |
| Wi-Fi-pagina opent niet | ESP32-POC actief, juist netwerk en IP-adres 192.168.4.1 |
