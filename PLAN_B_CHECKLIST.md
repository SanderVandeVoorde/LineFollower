# Plan B – indieningscontrole

**Gekozen uitvoering:** Plan B – opgebouwde robot met bestaande modules, bedrading en experimenteer-/soldeerplaat.

Dit document koppelt de vereisten voor Plan B aan de bestanden in deze repository. Het is bewust geen Plan-A-ontwerpchecklist.

## Vereiste opleverstukken

| Vereiste | Bestand / locatie | Status |
|---|---|---|
| Onderdelenlijst (BOM) | [BOM](./bill%20of%20materials/readme.md) | Aanwezig; prijs- en aankoopbroncontrole blijft nodig |
| Elektrisch schema als PDF | [EPLAN PDF](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.pdf) | Aanwezig |
| Origineel elektrisch schema | [EPLAN-backup](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.zw1) | Aanwezig |
| H-brug-POC | [Sketch](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) · [uitleg](./code/proof%20of%20concepts/hbridge/readme.md) | Aanwezig; motoren fysiek getest, exact gebruik van deze aparte POC-sketch niet aangetoond |
| Sensor-POC | [Sketch](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) · [uitleg](./code/proof%20of%20concepts/sensor/readme.md) | Aanwezig; alle acht sensoren fysiek gemeten |
| Finale code | [Nano](./code/finaal/Arduino_Programma.ino) · [ESP32](./code/esp32/ESP32_Programma.ino) | Aanwezig; GitHub Actions compileert |
| Draadloze communicatie-POC | [Sketch](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) · [uitleg](./code/proof%20of%20concepts/wireless%20communication/readme.md) | Aanwezig; fysieke browser/UART-integratie niet bewezen in de teruggevonden testresultaten |
| Start/stop interrupt-POC | [Sketch](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) · [uitleg](./code/proof%20of%20concepts/interrupt/readme.md) | Aanwezig; finale D8-knop fysiek getest, afzonderlijke D2-interrupt-POC niet bewezen |
| Basisprogramma: seriële communicatie, EEPROM en interrupt | [Sketch](./code/basis/Basis_Programma.ino) · [uitleg](./code/basis/readme.md) | Aanwezig; alle drie functies zijn in de code opgenomen |
| Instructable | [Instructable](./instructable/readme.md) | Aanwezig |
| Gebruiksaanwijzing | [Handleiding](./gebruiksaanwijzing/readme.md) | Aanwezig |
| Datasheets en pinouts | [Datasheets-index](./datasheets/readme.md) | Index aanwezig; enkele officiële chip-PDF's enkel extern gelinkt |
| Resultaten van fysieke proeven | [TEST_RESULTS.md](./TEST_RESULTS.md) | Bestaande metingen en rijresultaten opgenomen |

## Niet vereist voor de gekozen Plan B

De volgende Plan-A-opleverstukken zijn niet van toepassing op deze indiening:
- eigen ontworpen PCB en PCB-layout;
- footprints/packages en productiebestanden voor een Plan-A-PCB;
- SMD-assemblage en soldeerbewijs van een zelf ontworpen PCB;
- afzonderlijke Plan-A-BOM en Plan-A-schema;
- een tweede volledig werkende Plan-A-robot.

De bestaande SolidWorks- en STL-bestanden zijn aanvullende informatie. Een extra bemate mechanische tekeningenset is geen open Plan-B-opleverpunt volgens de door de gebruiker bevestigde projectscope.

## Nog te vervolledigen of te bewijzen

1. **BOM-bronnen:** voeg voor alle nieuw aangekochte onderdelen een bestelbon, winkelnaam of productlink toe waar die informatie nog beschikbaar is. Vul geen onbekende aankoopbron in alsof die bevestigd is.
2. **Datasheets:** sla de ontbrekende officiële ATmega328P- en DRV8833-PDF's lokaal op wanneer de bestanden betrouwbaar beschikbaar zijn. Voor HY-S301 is tot nu toe geen verifieerbare officiële fabrikantdatasheet gevonden; vermeld de leveranciersbron als leveranciersinformatie.
3. **POC-bewijs:** de sensorproef en motorproef zijn in de robot uitgevoerd en de meetgegevens staan in TEST_RESULTS.md. Voor de aparte D2-interrupt-POC en browser↔ESP32↔Nano-wireless-POC is nog geen afzonderlijk fysiek testbewijs teruggevonden.
4. **Finale integratie:** fysieke werking van dashboard/UART, NVS-herstart, batterijmeting tegenover multimeter en 5V-voedingsrail onder motorbelasting is niet bewezen in de teruggevonden meetresultaten.
5. **Snelheidsdoel:** de vastgelegde drie-ronden-baseline is 0,477 m/s. Als de opdracht 0,5 m/s eist, is dit resultaat nog 0,023 m/s te laag. Noteer een nieuwe meting alleen nadat ze effectief is uitgevoerd.

## Build

De repository bevat een GitHub Actions-workflow die de Nano-, ESP32- en POC-sketches compileert. De laatst gecontroleerde build was geslaagd: [GitHub Actions-run](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45036857106). Een geslaagde compile is geen bewijs van fysieke werking.
