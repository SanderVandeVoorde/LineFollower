# Definitieve Arduino Nano-software

Dit bestand bevat de aangeleverde Arduino Nano-software voor de autonome LineFollower V2.

**Programma:** [Arduino_Programma.ino](./Arduino_Programma.ino)

## Functies

- Acht analoge IR-sensoren uitlezen en normaliseren.
- De positie van de zwarte lijn berekenen met een gewogen gemiddelde.
- De lijn volgen met een PID-regelaar.
- Twee DC-motoren onafhankelijk aansturen via de DRV8833.
- Twee encoders uitlezen met interrupts/pin-change-interrupt.
- De pulssnelheid van beide motoren berekenen.
- De robot starten en stoppen met een fysieke drukknop.
- Starten, stoppen en parameters aanpassen via de seriële verbinding.
- Telemetrie uitsturen voor de ESP32.
- Optionele PI-snelheidsregeling op basis van de encoders.

## Aansluitingen Arduino Nano

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| Startknop | D8 |
| Status-led | D13 |
| Sensor D1 (links) | A0 |
| Sensor D2 | A1 |
| Sensor D3 | A2 |
| Sensor D4 | A3 |
| Sensor D5 | A4 |
| Sensor D6 | A5 |
| Sensor D7 | A6 |
| Sensor D8 (rechts) | A7 |
| Linker encoder A | D3 |
| Linker encoder B | D4 |
| Rechter encoder A | D9 |
| Rechter encoder B | D7 |

De fysieke sensorvolgorde is **D1 links tot D8 rechts**. De software koppelt die volgorde aan A0 tot A7. De berekende lijnpositie loopt van -3500 (links) tot +3500 (rechts).

De startknop gebruikt INPUT_PULLUP en moet bij indrukken D8 met GND verbinden. De finale firmware leest deze knop via polling en debounce; de knop gebruikt hier geen hardware-interrupt.

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

- Baudrate: 115200
- Telemetrie-interval: ongeveer 100 ms
- Commando's worden afgesloten met een newline.

| Commando | Werking |
|---|---|
| START | Start de robot |
| STOP | Stopt de robot |
| CFG,... | Wijzigt de regelparameters |

Configuratieformaat:

**CFG,base,max,kp,ki,kd,min,turn,timeout,speedPI,targetPPS,speedKp,speedKi**

De twaalf waarden na CFG staan in deze vaste volgorde: basissnelheid, maximale PWM, Kp, Ki, Kd, minimum PWM, bochtvertraging, lijnverlies-time-out, speedPI, targetPPS, speedKp en speedKi.

Voorbeeld met de standaardinstellingen:

**CFG,70,160,30,0,0,0,0,80,0,800,0.05,0.01**

Na een geldige configuratieregel antwoordt de Nano met ACK,CFG.

De telemetrieregel begint met T, en bevat achtereenvolgens run-status, lijn-detectiestatus, lijnpositie, acht ruwe sensorwaarden, acht genormaliseerde sensorwaarden, beide encodertellers, beide pulssnelheden en beide aangestuurde motorsnelheden.

## Belangrijke aandachtspunten

- De configuratie wordt tijdens runtime aangepast. Er is in deze versie geen EEPROM-opslag voorzien; na een herstart worden de standaardwaarden uit de code geladen.
- De sensorcalibratie gebeurt niet automatisch bij het opstarten. De vaste waarden moeten overeenkomen met de gebruikte sensorarray en ondergrond.
- De PI-snelheidsregeling staat standaard uit.
- De software stuurt de status-led aan met HIGH als de robot actief is. Controleer de polariteit van de fysieke LED-aansluiting.
- Verbreek de UART-verbinding met de ESP32 tijdens het uploaden via USB wanneer die verbinding de seriële upload verstoort.
- Controleer vóór een praktijktest voedingsspanning, gemeenschappelijke GND, motoruitgangen en draairichting.

## Teststatus

Dit is de door de gebruiker aangeleverde Nano-code. De code is in de repository geplaatst zonder de PID-instellingen of motorlogica bewust te wijzigen. Een nieuwe compileer- en praktijktest moet afzonderlijk worden uitgevoerd en geregistreerd. De definitieve ESP32-dashboardfirmware is nog niet aan deze map toegevoegd; zie de wireless POC.
