# Plan B – indieningscontrole

**Gekozen uitvoering:** Plan B – opgebouwde robot met bestaande modules, bedrading en experimenteer-/soldeerplaat.

**Fysieke status (22-11-2026):** de gebruiker bevestigt dat de volledige robot en alle fysieke functies/integraties werken. Dit omvat de motor- en sensorwerking, start/stop, encoders, draadloze browserbediening, Nano–ESP32-UART, dashboardconfiguratie en -bevestiging, NVS-opslag na herstart, batterijspanningsmeting en de voedingsrails. Eerdere opmerkingen dat deze integratie niet fysiek bewezen was, zijn hiermee achterhaald. Er zijn voor deze bevestiging geen nieuwe numerieke meetwaarden opgegeven; bestaande meetwaarden blijven daarom ongewijzigd.

Dit document koppelt de vereisten voor Plan B aan de bestanden in deze repository. Het is bewust geen Plan-A-ontwerpchecklist.

## Vereiste opleverstukken

| Vereiste | Bestand / locatie | Status |
|---|---|---|
| Onderdelenlijst (BOM) | [BOM](./bill%20of%20materials/readme.md) | Aanwezig; prijs- en aankoopbroncontrole blijft nodig; geraamde som €157,91 |
| Elektrisch schema als PDF | [EPLAN PDF](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.pdf) | Aanwezig |
| Origineel elektrisch schema | [EPLAN-backup](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.zw1) | Aanwezig |
| H-brug-POC | [Sketch](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) · [uitleg](./code/proof%20of%20concepts/hbridge/readme.md) | Aanwezig; fysieke motorsturing en richtingsregeling werken volgens gebruiker |
| Sensor-POC | [Sketch](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) · [uitleg](./code/proof%20of%20concepts/sensor/readme.md) | Aanwezig; alle acht sensoren fysiek gemeten en werkend |
| Finale code | [Nano](./code/finaal/Arduino_Programma.ino) · [ESP32](./code/esp32/ESP32_Programma.ino) | Aanwezig; GitHub Actions compileert |
| Draadloze communicatie-POC | [Sketch](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) · [uitleg](./code/proof%20of%20concepts/wireless%20communication/readme.md) | Aanwezig; browser ↔ ESP32 ↔ UART ↔ Nano werkt fysiek volgens gebruiker |
| Start/stop interrupt-POC | [Sketch](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) · [uitleg](./code/proof%20of%20concepts/interrupt/readme.md) | Aanwezig; start/stopfunctie werkt fysiek volgens gebruiker |
| Basisprogramma: seriële communicatie, EEPROM en interrupt | [Sketch](./code/basis/Basis_Programma.ino) · [uitleg](./code/basis/readme.md) | Aanwezig; alle drie functies zijn in de code opgenomen |
| Instructable | [Instructable](./instructable/readme.md) | Aanwezig |
| Gebruiksaanwijzing | [Handleiding](./gebruiksaanwijzing/readme.md) | Aanwezig |
| Datasheets en pinouts | [Datasheets-index](./datasheets/readme.md) | Index aanwezig; enkele officiële chip-PDF's enkel extern gelinkt |
| Resultaten van fysieke proeven | [TEST_RESULTS.md](./TEST_RESULTS.md) | Bestaande metingen en rijresultaten opgenomen |

## Functionele criteria van de robot

| Functionele eis | Huidige implementatie | Beoordeling |
|---|---|---|
| Minstens zes analoge sensoren | HY-S301 met acht kanalen; alle acht zijn fysiek gemeten | Voldoet |
| Lijnpositie bepalen | Gewogen sensorwaarde met positie van -3500 tot +3500 | In finale code aanwezig |
| PID-regeling | PID-parameters Kp, Ki en Kd in Nano-firmware | Fysieke lijnvolging werkt volgens gebruiker; snelheidscriterium apart beoordeeld op basis van meetwaarden |
| Instellingen draadloos wijzigen via pc/telefoon | ESP32-C3 accesspoint en browserdashboard met PID-/snelheidsinstellingen | Fysiek werkend volgens gebruiker |
| Instellingen bewaren | Basisprogramma gebruikt interne Nano-EEPROM; geïntegreerde dashboardinstellingen worden in ESP32-NVS bewaard | Opslag en behoud na herstart fysiek werkend volgens gebruiker; finale dashboardinstellingen staan in ESP32-NVS |
| Start/stop via interrupt aantonen | Afzonderlijke D2-interrupt-POC | Start/stopfunctie fysiek werkend volgens gebruiker; de POC-code blijft als afzonderlijk opleverbestand opgenomen |
| Drie ronden rijden | Eerdere drie-rondentest: 3 × 4,144 m | Voldoet aan het aantal ronden |
| Gemiddelde snelheid minimaal 0,5 m/s | Gemeten 0,477 m/s over drie ronden | Nog niet voldaan |

## Niet vereist voor de gekozen Plan B

De volgende Plan-A-opleverstukken zijn niet van toepassing op deze indiening:
- eigen ontworpen PCB en PCB-layout;
- footprints/packages en productiebestanden voor een Plan-A-PCB;
- SMD-assemblage en soldeerbewijs van een zelf ontworpen PCB;
- afzonderlijke Plan-A-BOM en Plan-A-schema;
- een tweede volledig werkende Plan-A-robot.

De bestaande SolidWorks- en STL-bestanden zijn aanvullende informatie. Een extra bemate mechanische tekeningenset is geen open Plan-B-opleverpunt volgens de door de gebruiker bevestigde projectscope.

## Nog te vervolledigen of te bewijzen

1. **BOM-bronnen:** voeg voor nieuw aangekochte onderdelen een bestelbon, winkelnaam of productlink toe waar die informatie nog beschikbaar is. Vul geen onbekende aankoopbron in alsof die bevestigd is.
2. **Datasheets:** de officiële ATmega328P- en DRV8833-chipdatasheets zijn momenteel als fabrikantlinks opgenomen; voeg lokale PDF-kopieën toe als die betrouwbaar kunnen worden opgehaald. Voor HY-S301 is geen verifieerbare officiële fabrikantdatasheet gevonden; leveranciersinformatie blijft de juiste bronvermelding.
3. **Snelheidsdoel:** de vastgelegde baseline is 0,477 m/s over drie ronden (12,432 m in 26,08 s). Dat ligt 0,023 m/s onder de opdrachtgrens van 0,5 m/s. Voor dezelfde afstand moet de tijd maximaal 24,864 s zijn. De fysieke werking is bevestigd, maar er is nog geen nieuw meetresultaat aangeleverd dat aantoont dat de 0,5 m/s-grens intussen gehaald is.

## Build

De repository bevat een GitHub Actions-workflow die de Nano-, ESP32- en POC-sketches compileert. De laatst gecontroleerde build was geslaagd: [GitHub Actions-run](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45036857106). Een geslaagde compile is geen bewijs van fysieke werking.
