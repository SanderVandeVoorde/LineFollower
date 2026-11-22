# Elektrische technische tekeningen

## Bestanden

| Bestand | Beschrijving |
|---|---|
| Linefollower_EPLAN_SVDV.pdf | Elektrisch schema in PDF |
| Linefollower_EPLAN_SVDV.zw1 | EPLAN-projectbackup |
| easyeda_linefollower_planB.json | Oudere EasyEDA-variant; niet de actuele hardwareconfiguratie |
| [EPLAN_REVISION_NOTES.md](./EPLAN_REVISION_NOTES.md) | Documentatie van de nominale 150 kΩ-ontwerpwaarde tegenover de gemonteerde 147 kΩ |

## Sensorbedrading en softwaremapping

De bevestigde fysieke sensorvolgorde is D1 links tot D8 rechts. De correcte analoge mapping is:

| HY-S301-uitgang | Arduino Nano |
|---|---:|
| D1 (links) | A0 |
| D2 | A1 |
| D3 | A2 |
| D4 | A3 |
| D5 | A4 |
| D6 | A5 |
| D7 | A6 |
| D8 (rechts) | A7 |

**Correctie nodig in het EPLAN-bronproject:** blad 3 van de op 22-11-2026 geüploade PDF toont nog de omgekeerde mapping (D8→A0 ... D1→A7). De fysieke bedrading en de finale Nano-firmware zijn leidend: beide gebruiken D1→A0 ... D8→A7 en de code leest A0→A7. Pas de verbindingen op blad 3 in EPLAN aan en exporteer daarna een nieuwe PDF en projectbackup. De motorsturing en encoderbedrading op blad 4 komen wel overeen met de finale firmware. De acht sensoren zijn fysiek op wit en zwart getest; de meetwaarden staan in [TEST_RESULTS.md](../../TEST_RESULTS.md).

## Actuele Nano-aansluitingen

| Functie | Nano-pin |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| Startknop | D8 |
| Status-led | D13 |
| HY-S301 D1–D8 | A0–A7 (in die volgorde) |
| Linker encoder A/B | D3/D4 |
| Rechter encoder A/B | D9/D7 |

## ESP32-UART

- Nano D1/TX → 10 kΩ serieweerstand → ESP32 GPIO20/RX-knooppunt.
- ESP32 GPIO20/RX-knooppunt → 20 kΩ naar GND.
- ESP32 GPIO21/TX → Nano D0/RX.
- Gemeenschappelijke GND.

De Nano werkt met 5V-logica en de ESP32-C3 met 3,3V-logica. Controleer de fysieke UART-schakelaars en spanningsdeler vóór gebruik.

## Batterijspanningsdeler

De nominale ontwerpwaarde in EPLAN blijft 150 kΩ, zoals door de gebruiker bevestigd. De gemonteerde hardware gebruikt 147 kΩ (100 kΩ + 47 kΩ in serie), met 47 kΩ naar GND, ADC op GPIO0 en 100 nF naar GND. De ESP32-firmware gebruikt de werkelijke hardwarefactor (147 + 47) / 47 = 194 / 47. Er is geen EPLAN-aanpassing nodig.

## Voeding en ontkoppeling

De ontwerpdocumentatie vermeldt een 2S LiPo (7,4 V nominaal, 8,4 V volledig geladen), een 5V-buckconverter, een 470 µF-buffercondensator op de motorvoeding en 100 nF-ontstoring bij de motoren. Controleer de werkelijke componentwaarden en polariteit op de gemonteerde print.

## Belangrijke waarschuwing: EasyEDA Plan B

Het bestand easyeda_linefollower_planB.json bevat een oudere configuratie met onder andere Arduino Pro Micro, QTR-8A en HC-06. De actuele robot gebruikt Arduino Nano, ESP32-C3 Super Mini en HY-S301. Dit EasyEDA-bestand is geen betrouwbaar bouwschema voor de huidige robot.

## Bevestigde ontwerpstatus

- De gebruiker heeft bevestigd dat de motordrivermodule de DRV8833 is. De motorsturing op blad 4 komt overeen met de finale firmware (D11/D10 links, D6/D5 rechts; encoders D3/D4 en D9/D7).
- De sensorbedrading op blad 3 is een bekende uitzondering: de PDF toont D8→A0 ... D1→A7, maar de bevestigde fysieke mapping is D1→A0 ... D8→A7. Corrigeer het EPLAN-bronproject en exporteer een nieuwe PDF voordat de schema's als definitief worden ingediend.
- EPLAN blijft op 150 kΩ; de werkelijke gemonteerde waarde is 147 kΩ en wordt door de ESP32-firmware gebruikt.
- Eerdere sensor-, motor-, knop/LED- en encoderresultaten staan in [TEST_RESULTS.md](../../TEST_RESULTS.md). Er is geen EPLAN-wijziging nodig.

## Publicatie

De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en een EPLAN Education-watermerk. Controleer de toestemming van HOGENT/docent voordat dit bestand publiek wordt verspreid.
