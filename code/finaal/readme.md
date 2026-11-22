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
| Status-led | D13 |
| HY-S301 D1 (links) | A7 |
| HY-S301 D2 | A6 |
| HY-S301 D3 | A5 |
| HY-S301 D4 | A4 |
| HY-S301 D5 | A3 |
| HY-S301 D6 | A2 |
| HY-S301 D7 | A1 |
| HY-S301 D8 (rechts) | A0 |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

**Sensorvolgorde:** de EPLAN-bedrading koppelt D8 aan A0, D7 aan A1, ... en D1 aan A7. De software leest daarom de analoge ingangen in omgekeerde volgorde: A7, A6, ... A0. Zo blijven de softwarekanalen D1–D8 geordend van links naar rechts, zoals de calibratie- en positiewaarden verwachten.

De berekende lijnpositie loopt van -3500 (links) tot +3500 (rechts). De code gebruikt de pinvolgorde A7 tot A0 om de in EPLAN getekende bedrading te volgen. Na een firmware-upload moet de fysieke kanaalvolgorde nog sensor-voor-sensor worden bevestigd.

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

## Seriële communicatie

Baudrate: 115200. De ESP32 stuurt START, STOP en het configuratiecommando:

`CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi`

Na een geldige configuratieregel antwoordt de Nano met `ACK,CFG`.

De telemetrieregel begint met `T,` en bevat run-status, lijn-detectiestatus, lijnpositie, acht ruwe sensorwaarden, acht genormaliseerde sensorwaarden, beide encodertellers, beide pulssnelheden en beide aangestuurde motorsnelheden.

## Belangrijke aandachtspunten

- De instellingen in deze Nano-firmware worden niet in EEPROM opgeslagen. De ESP32 bewaart dashboardinstellingen in NVS en stuurt ze bij het opstarten opnieuw naar de Nano.
- De sensorcalibratie gebeurt niet automatisch. De vaste waarden moeten overeenkomen met de gebruikte sensorarray en ondergrond.
- De PI-snelheidsregeling staat standaard uit. Als ze wordt ingeschakeld, volgt de feed-forwardterm ook de gewenste snelheid bij bochtvertraging.
- De status-led wordt HIGH aangestuurd wanneer de robot actief is.
- Verbreek zo nodig de UART-verbinding met de ESP32 tijdens het uploaden via USB.
- Test na de wijziging van de sensorpinvolgorde elk kanaal afzonderlijk voordat je de robot op snelheid laat rijden.

## Teststatus

De broncode is door de gebruiker aangeleverd en in GitHub opgenomen. De sensorpinvolgorde is aangepast om overeen te komen met de D8→A0 ... D1→A7-bedrading die in EPLAN is getekend. De aangepaste firmware is nog niet op de robot geüpload of opnieuw getest. Compileer- en praktijktest moeten daarom nog worden geregistreerd.
