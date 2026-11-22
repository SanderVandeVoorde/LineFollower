# Instructable – LineFollower V2 nabouwen

Dit stappenplan beschrijft de volgorde om de robot op te bouwen met de onderdelenlijst en de beschikbare technische bestanden.

## Stap 1 – Onderdelen verzamelen

- Verzamel de onderdelen uit de Bill of Materials.
- Controleer de exacte motor- en encoderuitvoering.
- Controleer de pinout van de gebruikte Nano, ESP32-C3 en DRV8833-breakout.

## Stap 2 – Mechanische onderdelen printen

- Open ChassisV4_Linefollower_SVDV.SLDPRT in SolidWorks.
- Print ChassisV4_Linefollower_SVDV.STL.
- Print N20-Holder_Linefollower_SVDV.stl.
- Print Spacer_Linefollower_SVDV.stl.
- Controleer passing en bevestigingsgaten vóór de elektronica wordt gemonteerd.

## Stap 3 – Motoren en wielen monteren

- Monteer de twee N20-motoren in de motorhouders.
- Controleer dat encoderprintjes en magnetische schijven vrij kunnen draaien.
- Monteer de wielen.
- Controleer de draairichting en mechanische speling.
- Monteer geen encoderkit op een motor zonder de vereiste achteras.

## Stap 4 – Sensorarray monteren

- Monteer de HY-S301 aan de voorzijde.
- Richt D1 naar de linkerzijde en D8 naar de rechterzijde.
- Zorg dat de sensorarray parallel met de baan staat.
- Meet de sensorhoogte boven de ondergrond en noteer die.

## Stap 5 – Elektronica voorbereiden

- Monteer de Arduino Nano, ESP32-C3, DRV8833 en voedingsmodule.
- Soldeer de ontkoppel- en buffercondensatoren met correcte polariteit.
- Gebruik de actuele verbindingstabel en niet het oudere EasyEDA Plan-B-schema.
- Controleer de DRV8833-modulepinout aan de hand van de concrete breakout.

## Stap 6 – Voedingsbedrading aansluiten

- Sluit de 2S LiPo via de hoofdschakelaar aan.
- Sluit de motorvoeding aan op de daarvoor voorziene DRV8833-ingang.
- Voed de logica via de 5V-buckconverter.
- Verbind alle GND-punten.
- Controleer de polariteit en meet de voedingsrails vóór de controllers worden aangesloten.

## Stap 7 – Nano-bedrading aansluiten

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1/IN2 | D11/D10 |
| Rechtermotor IN1/IN2 | D6/D5 |
| Start/stopknop | D8 naar GND |
| Status-led | D13 |
| Sensor D1–D8 | A0–A7 |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

## Stap 8 – ESP32-UART aansluiten

- Nano TX (D1) gaat via de voorziene spanningsdeler naar ESP32 GPIO20 (RX).
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

1. Sensor-POC: alle acht kanalen afzonderlijk uitlezen.
2. H-brug-POC: motoren kort en met lage PWM testen.
3. Interrupt-POC: start/stop via D2 demonstreren.
4. Wireless-POC: browsercommando via ESP32 en UART naar Nano sturen.

Noteer de resultaten in PROJECT_STATUS.md.

## Stap 11 – Finale software uploaden

- Upload code/finaal/Arduino_Programma.ino naar de Nano.
- Koppel de UART tijdelijk los als de USB-upload wordt verstoord.
- Controleer sensorvolgorde, motorinversie en encoderwaarden.
- De definitieve ESP32-dashboardfirmware moet afzonderlijk worden toegevoegd; de wireless-POC is geen vervanging daarvan.

## Stap 12 – Eindtest

- Zet de robot op de testbaan.
- Controleer eerst bij lage snelheid.
- Test lijnverlies en de fysieke stopknop.
- Verhoog de snelheid stapsgewijs.
- Registreer tijd, afstand, batterijspanning en PID-instellingen.
