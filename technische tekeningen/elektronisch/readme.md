# Elektrische technische tekeningen

## Bestanden

| Bestand | Beschrijving |
|---|---|
| Linefollower_EPLAN_SVDV.pdf | Elektrisch schema in PDF |
| Linefollower_EPLAN_SVDV.zw1 | EPLAN-projectbackup |
| easyeda_linefollower_planB.json | Oudere EasyEDA-variant; niet de actuele hardwareconfiguratie |

## Actuele Nano-aansluitingen

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| Startknop | D8 |
| Status-led | D13 |
| HY-S301 D1–D8 | A0–A7 |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

De fysieke sensorvolgorde is D1 links tot D8 rechts. In de momenteel opgeslagen EPLAN-tekening staat de sensorkoppeling omgekeerd weergegeven (D8 naar A0 tot D1 naar A7). De finale Nano-code verwacht D1 naar A0 tot D8 naar A7. Corrigeer de EPLAN-tekening of documenteer een bewuste fysieke kruising; gebruik de twee tegenstrijdige mappings niet door elkaar.

## ESP32-UART

- Nano D1/TX → 10 kΩ serieweerstand → ESP32 GPIO20/RX-knooppunt.
- ESP32 GPIO20/RX-knooppunt → 20 kΩ naar GND.
- ESP32 GPIO21/TX → Nano D0/RX.
- Gemeenschappelijke GND.

De 10 kΩ/20 kΩ-weerstandsdeler verlaagt het 5V-TX-signaal van de Nano voor de 3,3V-ingang van de ESP32. Controleer de werkelijk gemonteerde waarden.

## Voeding en ontkoppeling

De ontwerpdocumentatie vermeldt een 2S LiPo (7,4 V nominaal, 8,4 V volledig geladen), een 5V-buckconverter, een 470 µF-buffercondensator op de motorvoeding en 100 nF-ontstoring bij de motoren. Controleer de werkelijke componentwaarden en polariteit op de gemonteerde print.

De batterijspanningsdeler moet nog met de fysieke weerstandswaarden worden vergeleken. Gebruik geen ADC-schaalfactor voordat de werkelijk gemonteerde weerstanden zijn bevestigd.

## Belangrijke waarschuwing: EasyEDA Plan B

Het bestand easyeda_linefollower_planB.json bevat een oudere configuratie met onder andere Arduino Pro Micro, QTR-8A en HC-06. De actuele robot gebruikt Arduino Nano, ESP32-C3 Super Mini en HY-S301. Dit EasyEDA-bestand is dus geen betrouwbaar bouwschema voor de huidige robot. Het is bewust behouden als historisch bestand.

## Openstaande elektrische controles

- Exacte pinout en nSLEEP-aansluiting van de gebruikte DRV8833-breakout identificeren.
- Sensorvolgorde in EPLAN vergelijken met D1 links → A0 en D8 rechts → A7.
- Werkelijke batterijspanningsdeler opmeten en de spanningsverhouding berekenen.
- 5V-buckconverter controleren onder belasting.
- Alle GND-verbindingen en condensatorpolariteiten controleren.
- UART-spanningsdeler en TX/RX-kruising controleren.

## Publicatie

De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en een EPLAN Education-watermerk. Controleer de toestemming van HOGENT/docent voordat dit bestand publiek wordt verspreid. Het feit dat het bestand al in een publieke repository staat, betekent niet automatisch dat herpublicatie is toegestaan.
