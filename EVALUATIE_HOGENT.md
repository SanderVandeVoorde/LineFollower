# HOGENT-evaluatie en conformiteitsmatrix – LineFollower V2

Dit document vertaalt de officiële opdrachtfiche en de meegestuurde evaluatietabel naar concrete controlepunten voor deze repository. Het onderscheidt **aanwezige bestanden**, **aangetoonde werking** en **nog ontbrekend bewijs**. Een bestand in GitHub betekent niet automatisch dat een evaluatiecriterium inhoudelijk volledig bewezen is.

## 1. Gekozen traject en betekenis van het minimum

De huidige robot is ingediend als **Plan B**: een werkende robot met bestaande modules en een experimenteer-/soldeerplaat. De opdrachtfiche beschrijft Plan B expliciet als het basistraject waarmee het minimum kan worden behaald. Plan A met een eigen ontworpen printplaat is een afzonderlijk uitbreidingsaccent.

Daarom geldt:

- De Plan-B-opleverstukken hieronder zijn de prioriteit om het minimum van 8 punten te halen.
- De Plan-A-onderdelen zijn niet aanwezig en leveren in de huidige gekozen uitvoering geen Plan-A-punten op.
- De algemene technische specificaties (zoals circa €50, minimaal 0,5 m/s en de chronobrugafmetingen) blijven relevante ontwerpdoelen. Ze mogen niet worden voorgesteld alsof ze al behaald zijn wanneer er geen bewijs is.

## 2. Evaluatiesnapshot die werd meegestuurd

De meegestuurde HOGENT-evaluatie vermeldt:

- Totaal: **3/20**.
- Minimum: **3/8**.
- BOM: 0/1.
- Elektronisch schema: 0/1.
- Proof of concept H-brug: 0/1.
- Proof of concept sensor: 0/1.
- Finale code: 0/1.
- Robot: 1 toer 1/1 en 3 toeren 2/2.

Deze score is de geregistreerde evaluatie uit de opdrachtomgeving. De huidige repository bevat inmiddels bestanden voor de vijf documentatie-/codeonderdelen. Dit document maakt die bestanden expliciet vindbaar en vermeldt tegelijk wat inhoudelijk nog moet worden aangevuld. Het is geen garantie dat een herbeoordelaar automatisch punten zal toekennen.

**Belangrijk voor het minimum:** de evaluatietabel zet snelheid onder het onderdeel *Accenten*, niet in de tabel met de zeven minimumonderdelen die samen 8 punten vormen. De 0,5 m/s blijft wel een expliciete technische specificatie en bepaalt de snelheidspunten, maar is niet één van de vijf ontbrekende documentatiepunten in het minimum van 8.

## 3. Minimumtraject Plan B – 8 punten

| Criterium | Huidige repository | Huidige bewijsstatus | Nog nodig voor een sterke herbeoordeling |
|---|---|---|---|
| BOM (1 punt) | [bill of materials/readme.md](./bill%20of%20materials/readme.md) | Onderdelen, aantallen en kosten zijn opgelijst. Niet alle oorspronkelijke aankoopbronnen of exacte SKU's zijn bevestigd. | Ontbrekende aankooplinks/bestelbronnen aanvullen; bevestigen welke onderdelen effectief in de robot zitten; de ontbrekende caster controleren; kostprijsverschil met de richtprijs van circa €50 transparant verklaren. |
| Elektronisch schema (1 punt) | [EPLAN-PDF](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.pdf), [EPLAN-projectbackup](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.zw1) | Een volledig schema en het originele projectbestand zijn aanwezig. De PDF is gecontroleerd: blad 4 (DRV8833, motoren en encoders) komt overeen met de finale firmware. Blad 3 bevat een foutieve HY-S301-mapping: de tekening toont D8→A0 ... D1→A7, terwijl de bevestigde fysieke bedrading D1→A0 ... D8→A7 is. | Corrigeer blad 3 in het EPLAN-bronproject en exporteer een nieuwe PDF/backup. De motorsturing op blad 4 hoeft op basis van deze controle niet te worden aangepast. |
| H-brug-POC (1 punt) | [HBridge_POC.ino](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) en [uitleg](./code/proof%20of%20concepts/hbridge/readme.md) | Code, aansluitlijst en testprocedure zijn aanwezig. De gebruiker bevestigt dat de motorsturing fysiek werkt. | Een afzonderlijk getekend deelschema toevoegen dat exact overeenkomt met de gebruikte DRV8833-module en EPLAN. Voeg indien mogelijk een foto/video van de test toe. |
| Sensor-POC (1 punt) | [Sensor_Readout_POC.ino](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) en [uitleg](./code/proof%20of%20concepts/sensor/readme.md) | Code, aansluitlijst, testprocedure en individuele wit-/zwartmetingen van acht kanalen zijn aanwezig. De code moet de bevestigde fysieke volgorde D1→A0 ... D8→A7 lezen. | Een afzonderlijk getekend deelschema toevoegen met de fysieke mapping. Corrigeer ook blad 3 van EPLAN; voeg indien mogelijk een foto/video toe waarop de individuele uitlezing en D1-links/D8-rechts zichtbaar zijn. |
| Finale code (1 punt) | [Nano-firmware](./code/finaal/Arduino_Programma.ino), [ESP32-firmware](./code/esp32/ESP32_Programma.ino) | Beide programma's zijn aanwezig. GitHub Actions compileert de Nano-, ESP32- en POC-sketches. De gebruiker bevestigt de fysieke werking van de robot en integraties. | De finale versie, pinmapping, configuratieprotocol en opslagmethode blijven consequent documenteren. Leg een nieuwe geslaagde build vast na eventuele codewijzigingen. |
| Robot: 1 toer (1 punt) | Resultaat in [TEST_RESULTS.md](./TEST_RESULTS.md) | De meegestuurde evaluatie kent 1/1 toe. | Geen bijkomend bewijs nodig voor het reeds toegekende punt; bewaar de testgegevens. |
| Robot: 3 toeren (2 punten) | Resultaat in [TEST_RESULTS.md](./TEST_RESULTS.md) | De meegestuurde evaluatie kent 2/2 toe. | Geen bijkomend bewijs nodig voor de reeds toegekende toerpunten; registreer wel nieuwe snelheidsmetingen afzonderlijk. |

### Belangrijke POC-opmerking

De opdracht omschrijft elke POC als een minimale schakeling met een **elektronisch deelschema**, broncode en eventueel een video. De huidige H-brug- en sensor-POC's hebben code, uitleg en verbindingstabellen, maar in de repository is nog geen afzonderlijk getekend deelschema per POC terug te vinden. Het totaalschema in EPLAN is aanwezig, maar vervangt niet automatisch de twee afzonderlijke POC-deelschema's.

## 4. Documentatieaccenten

| Criterium | Huidige repository | Status / resterend bewijs |
|---|---|---|
| Draadloze communicatie-POC (1 punt) | [ESP32_WiFi_UART_POC.ino](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) en [uitleg](./code/proof%20of%20concepts/wireless%20communication/readme.md) | Code, architectuur, aansluitingen en testprocedure aanwezig. De gebruiker bevestigt dat browser ↔ ESP32 ↔ UART ↔ Nano fysiek werkt. Een afzonderlijk POC-deelschema en visueel testbewijs zouden dit sterker maken. |
| Start/stop-interrupt-POC (1 punt) | [StartStop_Interrupt_POC.ino](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) en [uitleg](./code/proof%20of%20concepts/interrupt/readme.md) | Code en D2/INT0-aansluiting zijn beschreven. De finale robotknop werkt fysiek, maar de afzonderlijke D2-POC moet als interruptdemonstratie herkenbaar getest/bewijsbaar zijn. |
| Basisprogramma: communicatie + EEPROM + interrupt (1 punt) | [Basis_Programma.ino](./code/basis/Basis_Programma.ino) en [uitleg](./code/basis/readme.md) | De code bevat seriële commando's, een D2-hardware-interrupt en EEPROM-opslag voor cyclustijd/debugstatus. Voeg een concreet testresultaat toe waarin SAVE, reset en STATUS aantonen dat de EEPROM-waarden behouden blijven. |
| Instructable (1 punt) | [instructable/readme.md](./instructable/readme.md) | Een stappenplan is aanwezig. Voor een volledige reproduceerbare instructable ontbreken nog echte foto's van de bouwstappen en volledige aankoopbronnen voor alle onderdelen. Voeg ook de exacte software-installatie en uploadstappen toe. |
| Handleiding (1 punt) | [gebruiksaanwijzing/readme.md](./gebruiksaanwijzing/readme.md) | Een tekstuele gebruiks- en veiligheidsinstructie is aanwezig. Controleer deze tegen de finale robot en voeg eventueel foto's van bediening, dashboard en aansluitingen toe. |
| Datasheets (1 punt) | [datasheets/readme.md](./datasheets/readme.md) en [datasheets-map](./datasheets/) | Gedeeltelijk aanwezig. De ESP32-C3-chipdatasheet, Nano-pinout, ESP32-pinout, encoder- en motorinformatie zijn opgenomen. De officiële ATmega328P- en DRV8833-chipdatasheets zijn extern gelinkt en niet lokaal opgeslagen. Voor de exacte DRV8833-module ontbreekt nog een geverifieerde modulepinout. Voor HY-S301 is geen verifieerbare officiële fabrikantdatasheet gevonden; leveranciersinformatie is als zodanig vermeld. |

## 5. Controle van de technische specificaties

| Specificatie uit de opdracht | Huidige status | Opmerking |
|---|---|---|
| Richtprijs circa €50 | **Niet gehaald volgens huidige BOM** | De geraamde som van de BOM is €157,91. Dit is transparant opgenomen; het is geen kostprijs van circa €50. Controleer of accessoires zoals de lader afzonderlijk moeten worden getoond, maar verberg geen noodzakelijke robotonderdelen. |
| Minstens 0,5 m/s | **Nog niet aangetoond** | De laatst in GitHub geregistreerde drie-rondentest is 12,432 m in 26,08 s = 0,477 m/s. De meegestuurde evaluatie vermeldt een eerdere snelheid van 0,33 m/s. Beide resultaten moeten als afzonderlijke metingen worden bewaard. |
| Zwarte lijn van 15 mm op witte ondergrond | **Hardware afgestemd op 15 mm** | De sensorarray en testbaan zijn voor de opgegeven 15 mm-lijn beschreven. |
| Minstens zes analoge sensoren | **Voldoet op basis van de gemeten hardware** | HY-S301 met acht individueel uitgelezen kanalen; D1 links en D8 rechts. |
| Sensorcalibratie, normalisatie en lijnpositie | **Grotendeels aanwezig** | De finale code gebruikt gemeten wit-/zwartcalibratiewaarden, normalisatie en een gewogen lijnpositie van -3500 tot +3500 in fysieke volgorde D1 links tot D8 rechts. De analoge pinvolgorde moet A0→A7 zijn. Automatische calibratie is niet aanwezig. |
| PID-regeling | **Aanwezig in finale code** | Kp, Ki en Kd zijn instelbaar. De geregistreerde baseline gebruikt Ki=0 en Kd=0; de aanwezigheid van de volledige PID-code is niet hetzelfde als bewijs van optimaal getunede PID-prestaties. |
| Kruispunten: altijd rechtdoor | **Nog niet afzonderlijk aangetoond** | De werking op een kruispunt moet met een gerichte test of video worden bevestigd. |
| Werking bij normale labverlichting, zonlicht, TL en camerair | **Nog niet afzonderlijk aangetoond** | Geen gecontroleerde lichttestreeks is in TEST_RESULTS.md opgenomen. |
| Chronobrug: maximaal 12 cm breed en 12 cm hoog | **Afmetingen robot nog te bevestigen** | De volledige gemonteerde robot moet binnen de vrije doorgang passen en de brug niet raken. De repo vermeldt nog geen gecontroleerde totale breedte en hoogte. |
| Hoofdschakelaar en monostabiele start/stop | **Aanwezig volgens documentatie en fysieke bevestiging** | De hoofdvoeding heeft een schakelaar; de start/stopknop op Nano D8 werkt. |
| Power-on-led | **Nog te verifiëren** | De finale code stuurt D13 als run/status-led: die brandt tijdens RUN en is uit tijdens STOP. Dat is niet hetzelfde als een led die continu aangeeft dat de voeding aan staat. |
| Geen LCD | **Voldoet** | Het project gebruikt een browserdashboard, geen LCD. |
| Draadloos instellen en visualiseren | **Gedeeltelijk** | Het dashboard toont telemetrie en laat PID-/snelheidsinstellingen aanpassen. In de huidige code zijn geen afzonderlijke debug-aan/uit- of sensorcalibratiebediening in het dashboard teruggevonden. |
| Alle instellingen bewaren in EEPROM | **Opslag werkt, maar de implementatie wijkt af van de letterlijke eis** | Het basisprogramma demonstreert Nano-EEPROM. De geïntegreerde robot bewaart dashboardinstellingen in ESP32-NVS, niet in de EEPROM van de Nano. NVS is niet-vluchtige opslag, maar mag niet als letterlijk Nano-EEPROM worden beschreven. |
| Eigen ontworpen PCB, SMD waar nuttig | **Niet uitgevoerd in Plan B** | Dit hoort bij Plan A. De huidige robot gebruikt breakoutmodules en een experimenteer-/soldeerplaat. |
| Geen breadboard/breakout/jumper wires/hotglue in afgewerkt product | **Niet voldaan aan Plan-A-eindtoestand** | Plan B laat deze opbouw expliciet toe voor het minimumtraject. De huidige uitvoering moet dus als Plan B worden gepresenteerd, niet als afgewerkt Plan A. |
| Volledig reproduceerbaar met courant verkrijgbare onderdelen | **Gedeeltelijk** | De BOM en instructable bestaan, maar ontbrekende aankoopbronnen, exacte modulevariant en ontbrekende foto's moeten worden aangevuld. |
| Spoiler(s) | **Te verduidelijken** | De opdracht vermeldt dit expliciet, maar de huidige repository beschrijft geen spoiler. Controleer of dit een letterlijke vormgevingsverwachting is of een grap/extra detail van de opdrachtfiche. |

## 6. Gevonden EPLAN-correctie – sensorpinmapping

De op 22-11-2026 geüploade EPLAN-PDF is vier bladen lang. Blad 3 bevat de voeding van de Nano/ESP32-C3, UART en HY-S301; blad 4 bevat de DRV8833, twee motoren en beide encoders. De motor- en encoderpinnen op blad 4 komen overeen met de finale Nano-firmware:

- Linkermotor: D11/D10.
- Rechtermotor: D6/D5.
- Linker encoder: D3/D4.
- Rechter encoder: D9/D7.

**De sensorverbindingen op blad 3 zijn omgekeerd ten opzichte van de bevestigde fysieke bedrading.** De juiste volgorde is D1 links→A0, D2→A1, ... D8 rechts→A7. De finale Nano-firmware en sensor-POC zijn aangepast om A0→A7 te lezen. Het EPLAN-bronproject zelf moet nog worden aangepast en opnieuw geëxporteerd; tot dan is de huidige PDF op het sensorstuk niet de definitieve waarheid.

## 7. Opslag: EEPROM tegenover ESP32-NVS

De huidige implementatie moet op alle pagina's op dezelfde manier worden beschreven:

- Het zelfstandige basisprogramma gebruikt de interne EEPROM van de Arduino Nano voor de cyclustijd en debugstatus.
- De geïntegreerde robot bewaart de dashboardinstellingen in de NVS-opslag van de ESP32-C3.
- De ESP32 stuurt de opgeslagen instellingen na opstart of herverbinding via UART opnieuw naar de Nano.
- De gebruiker bevestigt dat de NVS-instellingen een herstart overleven.

Dit bewijst persistente opslag in de geïntegreerde robot, maar niet dat de finale Nano-firmware alle instellingen in zijn interne EEPROM bewaart. Als de docent de letterlijke EEPROM-eis hanteert, moet dit verschil expliciet met de docent worden afgestemd of de firmware moet worden aangepast.

## 8. Plan A – niet opgenomen in de huidige scope

De huidige repository bevat geen eigen Plan-A-PCB, geen PCB-productiebestanden/footprints, geen SMD-assemblagebewijs en geen afzonderlijk werkende Plan-A-robot. De SolidWorks- en STL-bestanden zijn aanvullende mechanische bestanden, geen bewijs van een Plan-A-PCB.

De meegestuurde evaluatietabel kent Plan-A-punten toe voor BOM/schema met correcte packages, mechanische tekeningen, PCB, solderen en een werkende Plan A. Die punten kunnen niet worden geclaimd op basis van de huidige Plan-B-uitvoering.

## 9. Publicatie- en reproduceerbaarheidscontrole

- De repository is publiek.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en een EPLAN Education-watermerk. Controleer publicatietoestemming voordat dit document publiek wordt verspreid.
- De Wi-Fi-toegangsgegevens staan momenteel hard-coded in de firmware en worden ook in documentatie vermeld. Beoordeel of die standaardtoegangsgegevens publiek mogen blijven; wijzig ze niet zonder de firmware en handleiding tegelijk bij te werken.
- De officiële ATmega328P- en DRV8833-chipdatasheets zijn momenteel externe links. Een chipdatasheet vervangt niet de pinout van de concrete Nano- of DRV8833-module.
- Gebruik de actuele EPLAN-PDF als schema. De EasyEDA-file is een oudere variant met andere hardware en mag niet als actueel bouwschema worden gebruikt.

## 10. Nog te verzamelen om de repository inhoudelijk af te werken

1. Foto's van de volledige robot (bovenaanzicht, onderaanzicht, sensoren, elektronica, knoppen/leds en zijkant voor de hoogte).
2. Corrigeer de HY-S301-verbindingen op blad 3 van het EPLAN-bronproject (D1→A0 ... D8→A7) en exporteer de bijgewerkte PDF en projectbackup.
3. Gemeten totale breedte en hoogte van de volledig gemonteerde robot, zodat de chronobrugcontrole aantoonbaar is.
4. Bevestiging of de Pololu-ball-caster effectief op de finale robot gemonteerd is.
5. Aankoopbronnen/bestelbevestigingen voor onderdelen waarvoor de BOM nu alleen een raming of fabrikantreferentie bevat.
6. Bevestiging of de power-on-led continu brandt bij ingeschakelde voeding, los van RUN/STOP.
7. Nieuwe drie-rondentest met afstand, tijd en instellingen als de robot intussen sneller rijdt dan de geregistreerde 0,477 m/s.
8. Indien beschikbaar: korte video's van de H-brug-POC, sensor-POC, interrupt-POC, draadloze communicatie en drie volledige ronden.
9. Toestemming of richtlijn van HOGENT/docent voor publieke verspreiding van de EPLAN-documenten en de gekozen Wi-Fi-demo-instellingen.

**Doel van de volgende revisie:** elk criterium moet vanaf de hoofdpagina met één klik bereikbaar zijn, de POC's moeten elk een eigen deelschema hebben, en alle claims moeten terug te leiden zijn naar code, schema, foto of meetresultaat.
