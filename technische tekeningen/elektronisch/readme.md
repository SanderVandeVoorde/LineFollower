# Elektrische technische tekeningen

## Bestanden

| Bestand | Beschrijving |
|---|---|
| Linefollower_EPLAN_SVDV.pdf | Elektrisch schema in PDF |
| Linefollower_EPLAN_SVDV.zw1 | EPLAN-projectbackup |
| easyeda_linefollower_planB.json | Oudere EasyEDA-variant; niet de actuele hardwareconfiguratie |

## Sensorbedrading en softwaremapping

De huidige EPLAN-tekening koppelt de HY-S301-uitgangen als volgt:

| HY-S301-uitgang | Arduino Nano |
|---|---:|
| D8 | A0 |
| D7 | A1 |
| D6 | A2 |
| D5 | A3 |
| D4 | A4 |
| D3 | A5 |
| D2 | A6 |
| D1 | A7 |

De fysieke sensorvolgorde die voor de robot wordt aangehouden is D1 links tot D8 rechts. De Nano-firmware leest daarom de analoge ingangen in omgekeerde volgorde (A7 tot A0), zodat de softwarekanalen D1 tot D8 links-naar-rechts blijven. De pinmapping in `code/finaal/Arduino_Programma.ino` is hierop aangepast. Bevestig dit na upload met de sensor-POC en door telkens één sensor boven een zwarte lijn te plaatsen.

## Actuele Nano-aansluitingen

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| Startknop | D8 |
| Status-led | D13 |
| HY-S301 D1–D8 | A7–A0 (in die volgorde) |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

## ESP32-UART

- Nano D1/TX → 10 kΩ serieweerstand → ESP32 GPIO20/RX-knooppunt.
- ESP32 GPIO20/RX-knooppunt → 20 kΩ naar GND.
- ESP32 GPIO21/TX → Nano D0/RX.
- Gemeenschappelijke GND.

De Nano werkt met 5V-logica en de ESP32-C3 met 3,3V-logica. Controleer de fysieke UART-schakelaars en spanningsdeler vóór gebruik.

## Batterijspanningsdeler

De werkelijk bevestigde weerstanden zijn:
- Bovenste tak: 147 kΩ, opgebouwd uit 100 kΩ + 47 kΩ in serie.
- Onderste tak: 47 kΩ.
- ESP32 ADC: GPIO0.
- Filtercondensator: 100 nF naar GND.

De softwarefactor is (147 + 47) / 47 = 194 / 47. De huidige EPLAN-PDF toont 150 kΩ voor de bovenste tak. De elektrische topologie is hetzelfde, maar de componentwaarde in de EPLAN-bron moet nog worden aangepast naar 100 kΩ + 47 kΩ in serie. Pas daarna de PDF opnieuw exporteren.

## Voeding en ontkoppeling

De ontwerpdocumentatie vermeldt een 2S LiPo (7,4 V nominaal, 8,4 V volledig geladen), een 5V-buckconverter, een 470 µF-buffercondensator op de motorvoeding en 100 nF-ontstoring bij de motoren. Controleer de werkelijke componentwaarden en polariteit op de gemonteerde print.

## Belangrijke waarschuwing: EasyEDA Plan B

Het bestand easyeda_linefollower_planB.json bevat een oudere configuratie met onder andere Arduino Pro Micro, QTR-8A en HC-06. De actuele robot gebruikt Arduino Nano, ESP32-C3 Super Mini en HY-S301. Dit EasyEDA-bestand is geen betrouwbaar bouwschema voor de huidige robot.

## Nog open

- Exacte DRV8833-breakout identificeren en de fysieke pinout vastleggen. De tot nu toe aangeleverde close-up lijkt visueel op een ESP32-C3 Super Mini en is onvoldoende om de motordriver te identificeren.
- EPLAN-weerstandswaarde aanpassen en PDF opnieuw exporteren.
- Na upload de sensorvolgorde D1 links tot D8 rechts praktisch valideren.
- Batterijspanningsmeting vergelijken met een multimeter en de ADC-schaalfactor zo nodig kalibreren.
- 5V-buckconverter onder motorbelasting meten.
- Alle GND-verbindingen en condensatorpolariteiten fysiek controleren.

## Publicatie

De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en een EPLAN Education-watermerk. Controleer de toestemming van HOGENT/docent voordat dit bestand publiek wordt verspreid.
