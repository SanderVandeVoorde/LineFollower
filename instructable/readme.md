# Instructable – LineFollower V2 nabouwen

Dit stappenplan beschrijft de opbouw en software van de LineFollower V2. Gebruik steeds de actuele bestanden in deze repository; de oudere EasyEDA Plan-B is geen actueel aansluitschema.

## Stap 1 – Onderdelen verzamelen

- Verzamel de onderdelen uit de Bill of Materials.
- Controleer de exacte motor- en encoderuitvoering.
- Controleer de pinout van de gebruikte Nano, ESP32-C3 en DRV8833-breakout.
- De werkelijke batterijspanningsdeler gebruikt 100 kΩ + 47 kΩ in serie (147 kΩ) als bovenste tak en 47 kΩ als onderste tak.

## Stap 2 – Mechanische onderdelen printen

- Open `ChassisV4_Linefollower_SVDV.SLDPRT` in SolidWorks.
- Print `ChassisV4_Linefollower_SVDV.STL`.
- Print de motorhouder en afstandhouder.
- Controleer passing en bevestigingsgaten vóór de elektronica wordt gemonteerd.

## Stap 3 – Motoren en wielen monteren

- Monteer de twee motoren in de motorhouders.
- Controleer dat encoderprintjes en magnetische schijven vrij kunnen draaien.
- Monteer de wielen.
- Controleer de draairichting en mechanische speling.
- Monteer geen encoderkit op een motor zonder de vereiste achteras.

## Stap 4 – Sensorarray monteren

- Monteer de HY-S301 aan de voorzijde.
- Houd D1 aan de linkerzijde en D8 aan de rechterzijde.
- Richt de sensorarray parallel met de baan.
- De door de gebruiker opgegeven sensorhoogte is 3 mm.
- De afstand tussen sensorarray en motoras is 70 mm.

## Stap 5 – Elektronica voorbereiden

- Monteer de Arduino Nano, ESP32-C3, DRV8833 en voedingsmodule.
- Soldeer ontkoppel- en buffercondensatoren met correcte polariteit.
- Gebruik de actuele EPLAN-bedrading en niet de oudere EasyEDA Plan-B.
- Controleer de fysieke DRV8833-modulepinout aan de hand van de eigen breakout.

## Stap 6 – Voeding en spanningsmeting

- Sluit de 2S LiPo via de hoofdschakelaar aan.
- Sluit de motorvoeding aan op de daarvoor voorziene DRV8833-ingang.
- Voed de logica via de 5V-buckconverter.
- Verbind alle GND-punten.
- De batterijspanningsdeler is 147 kΩ boven (100 kΩ + 47 kΩ in serie) en 47 kΩ onder.
- Meet de voedingsrails vóór de controllers worden aangesloten.

## Stap 7 – Nano-bedrading

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1/IN2 | D11/D10 |
| Rechtermotor IN1/IN2 | D6/D5 |
| Start/stopknop | D8 naar GND |
| Status-led | D13 |
| HY-S301 D8/D7/D6/D5/D4/D3/D2/D1 | A0/A1/A2/A3/A4/A5/A6/A7 |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

De firmware leest A7 tot A0 om de logische sensorvolgorde D1 links tot D8 rechts te behouden.

## Stap 8 – ESP32-UART

- Nano TX (D1) gaat via 10 kΩ serie en 20 kΩ naar GND naar ESP32 GPIO20 (RX).
- ESP32 GPIO21 (TX) gaat naar Nano RX (D0).
- Verbind de GND's.
- Controleer de spanningsdeler en logicaniveaus vóór inschakelen.

## Stap 9 – Elektrische controle

- Meet of batterijplus en GND niet kortgesloten zijn.
- Controleer alle voedingsspanningen zonder motoren te laten draaien.
- Controleer de polariteit van de elektrolytische condensatoren.
- Controleer dat de DRV8833 niet warm wordt zonder motorcommando.
- Sluit de batterij pas aan na de controle.

## Stap 10 – Afzonderlijke POC-tests

1. Sensor-POC: lees alle acht kanalen afzonderlijk uit en bevestig D1–D8.
2. H-brug-POC: test motoren kort en met lage PWM, wielen vrij van de grond.
3. Interrupt-POC: demonstreer start/stop via D2; dit is niet de finale D8-startknop.
4. Wireless-POC: test browsercommando via ESP32 en UART naar Nano.

Noteer resultaten in `PROJECT_STATUS.md`.

## Stap 11 – Finale software uploaden

- Upload `code/finaal/Arduino_Programma.ino` naar de Nano.
- Upload `code/esp32/ESP32_Programma.ino` naar de ESP32-C3.
- Koppel zo nodig UART tijdelijk los tijdens Nano-USB-upload.
- Controleer sensorvolgorde, motorinversie, encoderwaarden en UART-telemetrie.
- Verbind met Linefollower-V2 en open http://192.168.4.1.

## Stap 12 – Eindtest en snelheid optimaliseren

- Zet de robot op de testbaan met de aangedreven wielen vrij voor de eerste motorproef.
- Start op lage snelheid.
- Test de fysieke stopknop en draadloze STOP.
- Verhoog de basissnelheid stapsgewijs en verander één PID-parameter tegelijk.
- Registreer tijd, afstand, batterijspanning en PID-instellingen.
- Herhaal tests meerdere keren; noteer de snelste reproduceerbare tijd, niet alleen één toevallig snelle ronde.
