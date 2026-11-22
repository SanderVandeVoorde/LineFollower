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
| H-brug-POC (1 punt) | [HBridge_POC.ino](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino), [POC-schema](./code/proof%20of%20concepts/hbridge/HBridge_POC_Schema.svg) en [uitleg](./code/proof%20of%20concepts/hbridge/readme.md) | Code, functioneel afzonderlijk SVG-deelschema, aansluitlijst en testprocedure aanwezig. De gebruiker bevestigt dat de motorsturing fysiek werkt. | Voeg indien mogelijk een foto/video van de test toe. Controleer de exacte breakoutconnectorposities aan de hand van EPLAN blad 4 en de modulemarkeringen. |
| Sensor-POC (1 punt) | [Sensor_Readout_POC.ino](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino), [POC-schema](./code/proof%20of%20concepts/sensor/Sensor_POC_Schema.svg) en [uitleg](./code/proof%20of%20concepts/sensor/readme.md) | Code, afzonderlijk SVG-deelschema met de bevestigde fysieke mapping D1→A0 ... D8→A7, aansluitlijst, testprocedure en individuele wit-/zwartmetingen aanwezig. | Corrigeer blad 3 van EPLAN zodat het totaalschema dezelfde mapping toont. Voeg indien mogelijk een foto/video toe waarop de individuele uitlezing en D1-links/D8-rechts zichtbaar zijn. |
| Finale code (1 punt) | [Nano-firmware](./code/finaal/Arduino_Programma.ino), [ESP32-firmware](./code/esp32/ESP32_Programma.ino) | Beide programma's zijn aanwezig. GitHub Actions compileert de Nano-, ESP32- en POC-sketches. De gebruiker bevestigt de fysieke werking van de robot en integraties. | De finale versie, pinmapping, configuratieprotocol en opslagmethode blijven consequent documenteren. Leg een nieuwe geslaagde build vast na eventuele codewijzigingen. |
| Robot: 1 toer (1 punt) | Resultaat in [TEST_RESULTS.md](./TEST_RESULTS.md) | De meegestuurde evaluatie kent 1/1 toe. | Geen bijkomend bewijs nodig voor het reeds toegekende punt; bewaar de testgegevens. |
| Robot: 3 toeren (2 punten) | Resultaat in [TEST_RESULTS.md](./TEST_RESULTS.md) | De meegestuurde evaluatie kent 2/2 toe. | Geen bijkomend bewijs nodig voor de reeds toegekende toerpunten; registreer wel nieuwe snelheidsmetingen afzonderlijk. |

### Belangrijke POC-opmerking

De opdracht omschrijft elke POC als een minimale schakeling met een **elektronisch deelschema**, broncode en eventueel een video. Er zijn nu afzonderlijke SVG-deelschema's toegevoegd voor de H-brug- en sensor-POC, naast de code en testuitleg. Het H-brugdiagram toont de functionele signaal- en motorverbindingen; voor de exacte breakoutconnectorposities verwijst het naar EPLAN blad 4. Het sensor-POC-schema toont de bevestigde fysieke mapping D1→A0 ... D8→A7. Het volledige EPLAN-blad 3 bevat nog de omgekeerde mapping en moet worden bijgewerkt.

## 4. Documentatieaccenten

| Criterium | Huidige repository | Status / resterend bewijs |
|---|---|---|
| Draadloze communicatie-POC (1 punt) | [ESP32_WiFi_UART_POC.ino](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino), [schema](./code/proof%20of%20concepts/wireless%20communication/Wireless_POC_Schema.svg) en [uitleg](./code/proof%20of%20concepts/wireless%20communication/readme.md) | Code, functioneel schema, architectuur, aansluitingen en testprocedure aanwezig. De eerdere fysieke browser ↔ ESP32 ↔ UART ↔ Nano-keten is door de gebruiker bevestigd; de nieuwe secrets-configuratie moet na upload opnieuw worden getest. |
| Start/stop-interrupt-POC (1 punt) | [StartStop_Interrupt_POC.ino](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino), [schema](./code/proof%20of%20concepts/interrupt/Interrupt_POC_Schema.svg) en [uitleg](./code/proof%20of%20concepts/interrupt/readme.md) | Code, afzonderlijk schema en D2/INT0-testprocedure aanwezig. De afzonderlijke D2-POC moet nog fysiek worden uitgevoerd en vastgelegd; de finale knop is een andere implementatie. |
| Basisprogramma: communicatie + EEPROM + interrupt (1 punt) | [Basis_Programma.ino](./code/basis/Basis_Programma.ino), [EEPROM-schema](./code/basis/EEPROM_POC_Schema.svg) en [uitleg](./code/basis/readme.md) | Code en logisch EEPROM-schema aanwezig. Een concreet SAVE → reset → STATUS-testresultaat moet nog fysiek worden geregistreerd. |
| Instructable (1 punt) | [instructable/readme.md](./instructable/readme.md) | Een stappenplan is aanwezig. Voor een volledige reproduceerbare instructable ontbreken nog echte foto's van de bouwstappen en volledige aankoopbronnen voor alle onderdelen. Voeg ook de exacte software-installatie en uploadstappen toe. |
| Handleiding (1 punt) | [gebruiksaanwijzing/readme.md](./gebruiksaanwijzing/readme.md) | Een tekstuele gebruiks- en veiligheidsinstructie is aanwezig. Controleer deze tegen de finale robot en voeg eventueel foto's van bediening, dashboard en aansluitingen toe. |
| Datasheets (1 punt) | [datasheets/readme.md](./datasheets/readme.md) en [datasheets-map](./datasheets/) | Gedeeltelijk aanwezig. De ESP32-C3-chipdatasheet, Nano-pinout, ESP32-pinout, encoder- en motorinformatie zijn opgenomen. De officiële ATmega328P- en DRV8833-chipdatasheets zijn extern gelinkt en niet lokaal opgeslagen. Voor de exacte DRV8833-module ontbreekt nog een geverifieerde modulepinout. Voor HY-S301 is geen verifieerbare officiële fabrikantdatasheet gevonden; leveranciersinformatie is als zodanig vermeld. |

## 5. Controle van de technische specificaties

| Specificatie uit de opdracht | Huidige status | Opmerking |
|---|---|---|
| Richtprijs circa €50 | **Niet gehaald volgens huidige BOM** | De geprijsde BOM is €157,91 inclusief lader (€137,92 exclusief lader), plus de nog onbekende aankoopprijs van de ball caster. Dit is transparant opgenomen; het is geen kostprijs van circa €50. Controleer of accessoires zoals de lader afzonderlijk moeten worden getoond, maar verberg geen noodzakelijke robotonderdelen. |
| Minstens 0,5 m/s | **Nog niet aangetoond** | De laatst in GitHub geregistreerde drie-rondentest is 12,432 m in 26,08 s = 0,477 m/s. De meegestuurde evaluatie vermeldt een eerdere snelheid van 0,33 m/s. Beide resultaten moeten als afzonderlijke metingen worden bewaard. |
| Zwarte lijn van 15 mm op witte ondergrond | **Hardware afgestemd op 15 mm** | De sensorarray en testbaan zijn voor de opgegeven 15 mm-lijn beschreven. |
| Minstens zes analoge sensoren | **Voldoet op basis van de gemeten hardware** | HY-S301 met acht individueel uitgelezen kanalen; D1 links en D8 rechts. |
| Sensorcalibratie, normalisatie en lijnpositie | **Handmatige calibratie in firmware toegevoegd** | Het dashboard kan witte en zwarte waarden laten vastleggen; de Nano neemt 32 monsters per kanaal, controleert contrast en bewaart de waarden in EEPROM. De fysieke calibratiefunctie moet nog worden getest. |
| PID-regeling | **Aanwezig in finale code** | Kp, Ki en Kd zijn instelbaar. De geregistreerde baseline gebruikt Ki=0 en Kd=0; de aanwezigheid van de volledige PID-code is niet hetzelfde als bewijs van optimaal getunede PID-prestaties. |
| Kruispunten: altijd rechtdoor | **Nog niet afzonderlijk aangetoond** | De werking op een kruispunt moet met een gerichte test of video worden bevestigd. |
| Werking bij normale labverlichting, zonlicht, TL en camerair | **Nog niet afzonderlijk aangetoond** | Geen gecontroleerde lichttestreeks is in TEST_RESULTS.md opgenomen. |
| Chronobrug: maximaal 12 cm breed en 12 cm hoog | **Afmetingen robot nog te bevestigen** | De volledige gemonteerde robot moet binnen de vrije doorgang passen en de brug niet raken. De repo vermeldt nog geen gecontroleerde totale breedte en hoogte. |
| Hoofdschakelaar en monostabiele start/stop | **Aanwezig volgens documentatie en fysieke bevestiging** | De hoofdvoeding heeft een schakelaar; de start/stopknop op Nano D8 werkt. |
| Power-on-led | **In firmware aangepast; fysieke controle nodig** | D13 wordt bij het opstarten HIGH gezet en blijft aan als power-on-indicator. Controleer dat de externe LED daadwerkelijk na de hoofdschakelaar gevoed wordt en bij uitschakelen dooft. |
| Geen LCD | **Voldoet** | Het project gebruikt een browserdashboard, geen LCD. |
| Draadloos instellen en visualiseren | **Code uitgebreid; fysieke hertest nodig** | Dashboardcode bevat PID-/snelheidsinstellingen, debugweergave en handmatige wit-/zwartcalibratie. Deze nieuwe bediening moet na upload fysiek worden gevalideerd. |
| Alle instellingen bewaren in EEPROM | **Code uitgebreid; fysieke hertest nodig** | De geïntegreerde Nano-firmware schrijft nu configuratie en sensorcalibratie naar de interne EEPROM na SAVE; de ESP32 bewaart aanvullend een kopie in NVS. De SAVE → reset → herladen-test moet nog worden uitgevoerd. |
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

De geïntegreerde firmware is uitgebreid zodat de Nano na SAVE de configuratie en sensorcalibratie in de interne EEPROM bewaart. De ESP32 bewaart daarnaast de dashboardinstellingen in NVS en synchroniseert die via UART. De nieuwe Nano-EEPROM-implementatie is code-aanwezig maar moet nog fysiek worden getest met SAVE → volledige reset → opnieuw uitlezen. Zie POST_UPDATE_TEST_PLAN.md.

## 8. Plan A – niet opgenomen in de huidige scope

De huidige repository bevat geen eigen Plan-A-PCB, geen PCB-productiebestanden/footprints, geen SMD-assemblagebewijs en geen afzonderlijk werkende Plan-A-robot. De SolidWorks- en STL-bestanden zijn aanvullende mechanische bestanden, geen bewijs van een Plan-A-PCB.

De meegestuurde evaluatietabel kent Plan-A-punten toe voor BOM/schema met correcte packages, mechanische tekeningen, PCB, solderen en een werkende Plan A. Die punten kunnen niet worden geclaimd op basis van de huidige Plan-B-uitvoering.

## 9. Publicatie- en reproduceerbaarheidscontrole

- De repository is publiek.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en een EPLAN Education-watermerk. Controleer publicatietoestemming voordat dit document publiek wordt verspreid.
- De firmware gebruikt lokale, door .gitignore uitgesloten secrets.h-bestanden. Een eerder gepubliceerde standaardwaarde staat nog in de Git-geschiedenis en moet als gecompromitteerd worden beschouwd; wijzig het wachtwoord op de robot. Zie SECURITY.md.
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

**Doel van de volgende revisie:** elk criterium moet vanaf de hoofdpagina met één klik bereikbaar zijn, de POC's moeten elk een eigen deelschema hebben, en alle claims moeten terug te leiden zijn naar code, schema, foto of meetresultaat. De nieuw toegevoegde EEPROM-, debug- en calibratiefuncties zijn code-aanpassingen en mogen pas als fysiek bewezen worden beschouwd nadat POST_UPDATE_TEST_PLAN.md is uitgevoerd.
