# Definitieve Arduino Nano-software

**Broncode:** [Arduino_Programma.ino](./Arduino_Programma.ino)

Deze firmware verzorgt de realtime lijnvolging, motorsturing, sensormeting, encoders, start/stop en seriële communicatie met de ESP32-C3.

## Aansluitingen Arduino Nano

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| Startknop | D8 |
| Power-on-led | D13 (brandt zolang de firmware gevoed is) |
| HY-S301 D1 (links) | A0 |
| HY-S301 D2 | A1 |
| HY-S301 D3 | A2 |
| HY-S301 D4 | A3 |
| HY-S301 D5 | A4 |
| HY-S301 D6 | A5 |
| HY-S301 D7 | A6 |
| HY-S301 D8 (rechts) | A7 |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

**Fysieke sensorvolgorde (bevestigd 11-11-2026):** D1 links is aangesloten op A0, D2 op A1, ... en D8 rechts op A7. De firmware leest daarom A0 tot A7. De calibratie-arrays en de posities -3500 (links) tot +3500 (rechts) staan in dezelfde fysieke volgorde D1–D8.

**EPLAN-correctie nodig:** blad 3 van de op 22-11-2026 geüploade EPLAN-PDF toont nog de omgekeerde verbinding (D8→A0 ... D1→A7). Die sensorverbindingen moeten in het EPLAN-bronproject worden omgewisseld en opnieuw geëxporteerd. Gebruik voor de fysieke sensorbedrading de mapping in deze tabel; de motorsturing op blad 4 blijft overeenkomen met de firmware. De eerdere fysieke wit-/zwartmetingen staan in TEST_RESULTS.md.

De startknop gebruikt INPUT_PULLUP en verbindt D8 met GND. De finale firmware leest deze knop via polling en debounce; de aparte interrupt-POC gebruikt D2.

## Standaardinstellingen

| Parameter | Startwaarde |
|---|---:|
| Basissnelheid | 70 |
| Maximale PWM | 160 |
| Minimum PWM | 0 |
| Kp | 30 |
| Ki | 0 |
| Kd | 0 |
| Bochtvertraging | 0% |
| Lijnverlies-time-out | 80 ms |
| PI-snelheidsregeling | Uit |
| Gewenste encoderfrequentie | 800 pulsen/s |
| Sensorruisgrens | 150 |
| Minimale lijnsterkte | 300 |

Sensorcalibratie in de code:
- Wit: 688, 618, 643, 568, 590, 560, 588, 651
- Zwart: 1009, 994, 1003, 990, 997, 996, 994, 1005

Motor- en encodertekens:
- LEFT_INVERTED = true
- RIGHT_INVERTED = false
- LEFT_ENCODER_SIGN = -1
- RIGHT_ENCODER_SIGN = 1

**Encoderresolutie:** Pololu specificeert 12 CPR bij x4-decodering (beide flanken van beide kanalen). De Nano-code gebruikt een interrupt op beide flanken van kanaal A en leest kanaal B voor de richting (x2). Daardoor is de effectieve telling 6 pulsen per motorasomwenteling. Met de 15,25:1-overbrenging is dat 91,5 pulsen per wielomwenteling; de eerdere metingen waren 91,3 links en 91,6 rechts.

## Seriële communicatie

Baudrate: 115200. De ESP32 stuurt START, STOP en het configuratiecommando:

`CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi,debug`

Na een geldige configuratieregel antwoordt de Nano met `ACK,CFG`. Voor EEPROM-opslag gebruikt de ESP32 `SAVE`; de Nano antwoordt `ACK,EEPROM`. Voor handmatige calibratie gebruikt de ESP32 `CAL,WHITE` en `CAL,BLACK`.

De telemetrieregel begint met `T,` en bevat run-status, lijn-detectiestatus, lijnpositie, acht ruwe sensorwaarden, acht genormaliseerde sensorwaarden, beide encodertellers, beide pulssnelheden en beide aangestuurde motorsnelheden.

## Belangrijke aandachtspunten

- De Nano bewaart de laatst bevestigde configuratie en de acht wit-/zwartcalibratiewaarden in de interne EEPROM. De ESP32 bewaart dashboardinstellingen aanvullend in NVS. Bij OPSLAAN stuurt de ESP32 na de configuratiebevestiging het commando SAVE; de Nano antwoordt met ACK,EEPROM. Bij het opstarten laadt de Nano de laatst geldige EEPROM-waarden, waarna de ESP32 zijn NVS-configuratie synchroniseert.
- De sensorcalibratie is handmatig via het dashboard beschikbaar: leg eerst wit en daarna zwart vast. De Nano neemt 32 monsters per kanaal, controleert of er voldoende contrast is en bewaart de nieuwe waarden in EEPROM.
- De PI-snelheidsregeling staat standaard uit. Als ze wordt ingeschakeld, volgt de feed-forwardterm ook de gewenste snelheid bij bochtvertraging.
- D13 wordt bij het opstarten HIGH gezet en blijft branden zolang de robot gevoed is; dit is de power-on-indicator.
- Verbreek zo nodig de UART-verbinding met de ESP32 tijdens het uploaden via USB.
- De acht sensoren zijn eerder fysiek uitgelezen op wit en zwart; gebruik de vastgelegde calibratiewaarden in TEST_RESULTS.md als projectreferentie.

## Teststatus

De Nano-sketch is succesvol gecompileerd in GitHub Actions-build #26. De gebruiker bevestigde op 22-11-2026 dat de vorige firmwareversie fysiek werkte. De nieuwe EEPROM-, debug-, calibratie- en power-on-led-aanpassingen moeten nog op de robot worden getest; zie POST_UPDATE_TEST_PLAN.md en TEST_RESULTS.md.
