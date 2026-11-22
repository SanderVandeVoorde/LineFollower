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
| H-brug-POC | [Sketch](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) · [POC-schema](./code/proof%20of%20concepts/hbridge/HBridge_POC_Schema.svg) · [uitleg](./code/proof%20of%20concepts/hbridge/readme.md) | Code, functioneel afzonderlijk SVG-deelschema, aansluitlijst en testprocedure aanwezig; fysieke motorsturing werkt volgens gebruiker. Voor de exacte breakoutconnectorposities verwijst het POC-schema naar EPLAN blad 4. |
| Sensor-POC | [Sketch](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) · [POC-schema](./code/proof%20of%20concepts/sensor/Sensor_POC_Schema.svg) · [uitleg](./code/proof%20of%20concepts/sensor/readme.md) | Code, afzonderlijk SVG-deelschema met fysieke D1→A0 ... D8→A7-mapping, aansluitlijst, testprocedure en achtkanaalsmetingen aanwezig. De EPLAN-pagina moet nog dezelfde mapping tonen. |
| Finale code | [Nano](./code/finaal/Arduino_Programma.ino) · [ESP32](./code/esp32/ESP32_Programma.ino) | Aanwezig; GitHub Actions compileert |
| Draadloze communicatie-POC | [Sketch](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) · [uitleg](./code/proof%20of%20concepts/wireless%20communication/readme.md) | Code, architectuur en aansluitlijst aanwezig; browser ↔ ESP32 ↔ UART ↔ Nano werkt fysiek volgens gebruiker. Een apart getekend POC-schema en visueel bewijs ontbreken nog. |
| Start/stop interrupt-POC | [Sketch](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) · [uitleg](./code/proof%20of%20concepts/interrupt/readme.md) | Code en D2/INT0-aansluitlijst aanwezig. De finale D8-start/stop werkt fysiek; een afzonderlijk testresultaat van de D2-interrupt-POC en een getekend deelschema ontbreken nog. |
| Basisprogramma: seriële communicatie, EEPROM en interrupt | [Sketch](./code/basis/Basis_Programma.ino) · [uitleg](./code/basis/readme.md) | Code bevat seriële commando's, D2-hardware-interrupt en Nano-EEPROM voor cyclustijd/debugstatus. Een testlog met SAVE → reset → STATUS ontbreekt nog. |
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
| Gemiddelde snelheid minimaal 0,5 m/s | Laatste geregistreerde meting: 0,477 m/s over drie ronden | Laatste vastgelegde meting haalt de grens niet; een nieuwere meting is nog niet opgegeven |

## Belangrijke interpretatie van de officiële evaluatie

De meegestuurde HOGENT-evaluatie vermeldt 3/20 en 3/8 voor het minimum. De drie toerpunten zijn toegekend; BOM, totaalschema, H-brug-POC, sensor-POC en finale code kregen in die evaluatiesnapshot 0 punten. De repository bevat nu afzonderlijke SVG-deelschema's voor H-brug en sensor, naast de code en testuitleg. Het EPLAN-blad voor de sensorbedrading moet nog worden gecorrigeerd en de BOM-bronnen zijn onvolledig. Zie [EVALUATIE_HOGENT.md](./EVALUATIE_HOGENT.md) voor de volledige rubricmatrix.

De officiële opdracht stelt een richtprijs van circa €50 en een snelheid van minstens 0,5 m/s. De huidige geraamde BOM is €157,91 en de laatst geregistreerde drie-rondentest is 0,477 m/s. De meegestuurde evaluatie vermeldt een snelheid van 0,33 m/s; behandel dat als een afzonderlijke evaluatiemeting, niet als vervanging van de meetgegevens in TEST_RESULTS.md. **Snelheid staat in de evaluatietabel onder Accenten en is geen afzonderlijk onderdeel van het minimum van 8 punten**, maar blijft wel een technische eis en bepaalt de snelheidspunten.

De finale robot bewaart dashboardinstellingen in ESP32-NVS. Het zelfstandige basisprogramma demonstreert Nano-EEPROM, maar de finale Nano-firmware schrijft de dashboardinstellingen niet naar zijn eigen EEPROM. Dit onderscheid staat uitgelegd in EVALUATIE_HOGENT.md.

## Niet vereist voor de gekozen Plan B

De volgende Plan-A-opleverstukken zijn niet van toepassing op deze indiening:
- eigen ontworpen PCB en PCB-layout;
- footprints/packages en productiebestanden voor een Plan-A-PCB;
- SMD-assemblage en soldeerbewijs van een zelf ontworpen PCB;
- afzonderlijke Plan-A-BOM en Plan-A-schema;
- een tweede volledig werkende Plan-A-robot.

De bestaande SolidWorks- en STL-bestanden zijn aanvullende informatie. Een extra bemate mechanische tekeningenset is geen open Plan-B-opleverpunt volgens de door de gebruiker bevestigde projectscope.

## Nog te vervolledigen of te bewijzen

1. **EPLAN-sensorblad:** corrigeer blad 3 naar D1→A0 ... D8→A7 en exporteer de bijgewerkte PDF en projectbackup. De twee afzonderlijke POC-SVG-schema's zijn inmiddels toegevoegd.
2. **BOM-bronnen:** voeg voor nieuw aangekochte onderdelen een bestelbon, winkelnaam of productlink toe waar die informatie nog beschikbaar is. Vul geen onbekende aankoopbron in alsof die bevestigd is.
3. **Datasheets:** de officiële ATmega328P- en DRV8833-chipdatasheets zijn momenteel als fabrikantlinks opgenomen; voeg lokale PDF-kopieën toe als die betrouwbaar kunnen worden opgehaald. Voor HY-S301 is geen verifieerbare officiële fabrikantdatasheet gevonden; leveranciersinformatie blijft de juiste bronvermelding.
4. **Snelheidsdoel:** de laatst vastgelegde meting is 0,477 m/s over drie ronden (12,432 m in 26,08 s), 0,023 m/s onder de opdrachtgrens van 0,5 m/s. Voor dezelfde afstand moet de tijd maximaal 24,864 s zijn. De fysieke werking is bevestigd, maar zonder een nieuw tijd-/afstandsresultaat kan ik niet vaststellen of de grens intussen gehaald is.

## Build

De repository bevat een GitHub Actions-workflow die de Nano-, ESP32- en POC-sketches compileert. De laatst gecontroleerde build was geslaagd: [GitHub Actions-run](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45074736076). Een geslaagde compile is geen bewijs van fysieke werking.
