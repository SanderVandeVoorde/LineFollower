# Projectstatus – LineFollower V2 (Plan B)

Laatst bijgewerkt: 22-11-2026.

De BOM-totalen zijn op 22-11-2026 opnieuw nagerekend op basis van alle afzonderlijke regels: **€157,91** geraamde projectkost (€117,26 nieuw + €37,15 recup + €3,50 3D-print). De vorige samenvatting van €157,96 / €37,20 bevatte een optelfout; de BOM en README zijn gecorrigeerd. De recupwaarden blijven geraamde vervangingsprijzen, geen factuurbedragen.

**Gekozen uitvoeringsplan: Plan B.** De robot wordt opgebouwd met bestaande breakoutmodules, experimenteer-/soldeerplaat en bedrading. Een zelf ontworpen PCB, PCB-productiebestanden, SMD-componentplaatsing en een tweede volledig opgebouwde Plan-A-robot behoren niet tot de scope van deze indiening. Mechanische SolidWorks-tekeningen zijn voor deze Plan-B-afwerking niet als afzonderlijk verplicht opleverpunt behandeld; de bestaande CAD-/STL-bestanden blijven aanvullende projectbestanden.

Deze status is bijgewerkt op basis van de repository en de door de gebruiker bevestigde hardwarekeuzes. **Op 22-11-2026 bevestigde de gebruiker dat alle fysieke functies en integraties van de robot werken.** De oudere meldingen dat dashboard/UART, NVS, batterijmeting of voedingsrails nog niet fysiek gevalideerd waren, zijn daarmee achterhaald. Er zijn geen nieuwe numerieke meetwaarden opgegeven; historische meetresultaten blijven daarom als historische resultaten vermeld.

## Repository-inhoud

- [x] Arduino Nano-firmware: code/finaal/Arduino_Programma.ino.
- [x] ESP32-C3-dashboardfirmware: code/esp32/ESP32_Programma.ino.
- [x] Basisprogramma en vier POC-sketches.
- [x] Afzonderlijke SVG-deelschema's voor de H-brug- en sensor-POC.
- [x] README's en documentatie voor firmware, sensoren, PID, encoders, UART en dashboard.
- [x] BOM en kostprijsdocumentatie.
- [x] Gebruiksaanwijzing en instructable.
- [x] EPLAN-PDF en EPLAN-projectbackup.
- [x] Bestaande chassis-/STL-bestanden als aanvullende documentatie; geen extra SolidWorks-project of bemate mechanische Plan-A-tekeningen vereist voor Plan B.
- [x] Parcours-PDF's en SVG.
- [x] Testresultaten samengebracht in TEST_RESULTS.md.
- [x] HY-S301-leveranciersspecificaties en pinout online onderzocht en opgenomen in datasheets/readme.md.
- [x] Encoderconnector gecorrigeerd naar de door de gebruiker bevestigde 90°/side-entry JST SH-uitvoering; Pololu #4761 en de bijbehorende DRV5013-datasheet als fabrikantreferenties toegevoegd.
- [x] GitHub Actions-buildworkflow aanwezig.

## Bevestigde hardware en ontwerpkeuzes

- Volledig gemonteerde robot.
- Motordriver: DRV8833; gebruiker bevestigt dat EPLAN de juiste aansluitingen weergeeft.
- Sensorarray: HY-S301, D1 links tot D8 rechts.
- Sensorhoogte: 3 mm.
- Afstand sensorarray tot motoras: 70 mm.
- Totaalgewicht: 141 g.
- Schoolbaan: zwarte lijn op witte ondergrond, lijnbreedte 15 mm.
- Motoren: Pololu 15,25:1 Micro Metal Gearmotor HPCB 12 V, encoder-compatibele verlengde achteras (Pololu #4789 als fabrikantreferentie; exacte aankoop-SKU niet teruggevonden).
- Encoders: Pololu 12 CPR magnetische encoder, side-entry (90°) JST SH (Pololu #4761 als fabrikantreferentie).
- Wielen: Pololu Ø40 × 7 mm.
- Batterij: 2S LiPo, 7,4 V nominaal en 8,4 V volledig geladen.
- Startknop en status-led zijn fysiek getest en werken.

## Batterijspanningsdeler: EPLAN tegenover hardware

- EPLAN blijft bewust op 150 kΩ als nominale ontwerpwaarde staan; de gebruiker wil dit schema niet aanpassen.
- De werkelijke gemonteerde bovenste tak is 147 kΩ, opgebouwd uit 100 kΩ + 47 kΩ in serie.
- Onderste tak: 47 kΩ.
- Filtercondensator: 100 nF.
- ADC: ESP32-C3 GPIO0.
- De ESP32-firmware gebruikt de werkelijke hardwarefactor (147 + 47) / 47 = 194 / 47.
- Dit verschil is bewust gedocumenteerd en is geen openstaande EPLAN-fout.

Zie ook de afzonderlijke [Plan-B-indieningscontrole](./PLAN_B_CHECKLIST.md) voor de volledige koppeling tussen opdrachtvereisten, bestanden en resterend bewijs.

## Plan B – vereisten en afbakening

| Plan-B-opleverpunt | Repositorybestand | Status |
|---|---|---|
| Onderdelenlijst en kostprijs | [BOM](./bill%20of%20materials/readme.md) | Aanwezig; aankooplinks/bronvermelding per onderdeel nog verbeteren waar mogelijk |
| Elektrisch schema als PDF | [EPLAN-PDF](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.pdf) | Aanwezig |
| Oorspronkelijk elektrisch schema | [EPLAN-backup](./technische%20tekeningen/elektronisch/Linefollower_EPLAN_SVDV.zw1) | Aanwezig |
| H-brug-POC | [HBridge_POC.ino](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) · [schema](./code/proof%20of%20concepts/hbridge/HBridge_POC_Schema.svg) | Code, functioneel POC-deelschema en fysieke motorwerking aanwezig |
| Sensor-POC | [Sensor_Readout_POC.ino](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) · [schema](./code/proof%20of%20concepts/sensor/Sensor_POC_Schema.svg) | Code, functioneel POC-deelschema en achtkanaalsmetingen aanwezig; EPLAN-blad 3 nog corrigeren |
| Finale software | [Nano](./code/finaal/Arduino_Programma.ino) · [ESP32](./code/esp32/ESP32_Programma.ino) | Aanwezig; automatische compile geslaagd |
| Draadloze communicatie-POC | [ESP32_WiFi_UART_POC.ino](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) | Browserdashboard en Nano–ESP32-UART fysiek werkend volgens gebruiker |
| Start/stop interrupt-POC | [StartStop_Interrupt_POC.ino](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) | Start/stopfunctie fysiek werkend volgens gebruiker |
| Basisprogramma met communicatie, EEPROM en interrupt | [Basis_Programma.ino](./code/basis/Basis_Programma.ino) | Aanwezig en compileert |
| Instructable | [Instructable](./instructable/readme.md) | Aanwezig |
| Gebruiksaanwijzing | [Handleiding](./gebruiksaanwijzing/readme.md) | Aanwezig |
| Datasheets en pinouts | [Datasheets-index](./datasheets/readme.md) | Aanwezig, enkele chipdatasheets enkel als externe officiële link |

**Niet van toepassing op Plan B:** zelf ontworpen PCB, Plan-A-PCB-schema met footprints/packages, PCB-productiebestanden, SMD-assemblage-/soldeerbewijs, Plan-A-BOM en een tweede werkende Plan-A-robot. Ook een extra bemate SolidWorks-tekeningenset wordt niet als resterende Plan-B-taak beschouwd.

## Firmware en automatische compilatie

- [x] Nano- en ESP32-code staan in GitHub.
- [x] Nano-firmware en sensor-POC lezen de bevestigde fysieke mapping D1→A0 ... D8→A7 in volgorde A0→A7.
- [ ] EPLAN-blad 3 toont nog de omgekeerde mapping D8→A0 ... D1→A7; corrigeer de bron en exporteer een nieuwe PDF/backup.
- [x] Nano- en ESP32-UART-protocol inhoudelijk vergeleken: 115200 baud, START, STOP, CFG, ACK,CFG en telemetrie.
- [x] ESP32-batterijfactor aangepast aan de werkelijk gemonteerde 147 kΩ + 47 kΩ.
- [x] Nano speed-PI feed-forward aangepast zodat bochtvertraging ook met ingeschakelde PI-snelheidsregeling behouden blijft.
- [x] Dashboardverbindingsstatus verbeterd: Nano wordt pas als verbonden getoond na ontvangst van telemetrie; configuratiebevestiging wordt apart weergegeven.
- [x] Dashboard meldt expliciet of de Nano de ingestelde waarden met ACK,CFG bevestigd heeft.
- [x] ESP32 stuurt de opgeslagen instellingen opnieuw naar de Nano wanneer de Nano na een herstart opnieuw telemetrie begint te sturen.
- [x] GitHub Actions-build geslaagd: finale Nano-firmware, basisprogramma, drie Nano-POC's, ESP32-dashboard en ESP32-UART-POC compileerden succesvol. [Buildrun](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45074736076).

## Fysieke tests die al uitgevoerd zijn

De resultaten zijn teruggevonden in de projectgesprekken en samengebracht in [TEST_RESULTS.md](./TEST_RESULTS.md).

- [x] HY-S301: alle acht sensoren gemeten op wit en zwart; calibratiewaarden vastgelegd.
- [x] Motoren: beide motoren getest en fysieke draairichting vastgesteld.
- [x] Startknop getest.
- [x] Status-led getest.
- [x] Encoders: handmatige meting over exact tien wielomwentelingen.
- [x] Encoders: aangedreven motor-/encodertest.
- [x] Volledig parcours gereden.
- [x] Meerdere rijresultaten vastgelegd, inclusief een baseline van drie ronden in 26,08 s.

### Belangrijkste meetresultaten

- HY-S301 wit: 688, 618, 643, 568, 590, 560, 588, 651.
- HY-S301 zwart: 1009, 994, 1003, 990, 997, 996, 994, 1005.
- Encoders over tien wielomwentelingen: links 913, rechts 916 pulsen (91,3/91,6 per wielomwenteling; verwacht 91,5 met de huidige x2-softwaredecodering en 15,25:1-overbrenging).
- Aangedreven encoderproef: links L− = −1472, rechts R+ = +1110.
- Baseline: 3 × 4,144 m in 26,08 s = 0,477 m/s gemiddeld.
- 16-11-2026: volledig parcours gereden, stabiel maar traag.
- 18-11-2026: een ronde voltooid; robot viel bijna stil en had een duwtje nodig om te vertrekken.
- Gebruiker meldde daarnaast bijna eindeloos rondjes te kunnen rijden; exacte duur is niet genoteerd.

## HY-S301-documentatie

- [x] Online gezocht naar de HY-S301.
- [x] Leveranciersinformatie en pinout opgenomen in datasheets/readme.md.
- [x] Geen verifieerbare officiële fabrikantdatasheet gevonden; de openbare informatie is leveranciersdocumentatie.
- De bronnen noemen 3,3–5 V, acht IR-kanalen, circa 950 nm, GND/VCC/IR/D1–D8, twee montagegaten van 3 mm en ongeveer 67 × 17 mm.
- Leveranciers beschrijven de outputs vaak als digitaal. De projectrobot heeft de concrete D1–D8-uitgangen empirisch met de Nano-ADC gemeten; de gemeten calibratiewaarden zijn daarom leidend voor deze hardware.

## Fysieke integratie – bevestigd op 22-11-2026

De gebruiker bevestigt dat alle fysieke functies en integraties werken:

- [x] ESP32-accesspoint en browserdashboard.
- [x] Nano–ESP32-UART-communicatie en dashboard START/STOP/CFG-ACK.
- [x] PID-/snelheidsinstellingen toepassen via het dashboard.
- [x] Instellingen opslaan in ESP32-NVS en behouden na herstart.
- [x] Batterijspanningsmeting via de ESP32.
- [x] 5V-buckconverter en voedingsrails.
- [x] Fysieke werking van motoren, sensoren, encoders, start/stop en status-led.

De eerdere melding van 16-11-2026 dat Wi-Fi en batterijmeting toen nog niet aangesloten waren, is een historische tussenstand en wordt door deze latere bevestiging vervangen. Nieuwe numerieke meetwaarden (zoals de afwijking van de batterijmeting t.o.v. de multimeter) zijn niet opgegeven en worden daarom niet ingevuld.

## Snelheidscriterium – laatste geregistreerde meting

- De opdrachtbaseline is minimaal 0,5 m/s over de vereiste drie ronden.
- De geregistreerde test: 3 × 4,144 m = 12,432 m in 26,08 s, dus gemiddeld 0,477 m/s.
- Voor 0,5 m/s over dezelfde afstand mag de tijd maximaal 24,864 s bedragen. De vastgelegde baseline van 26,08 s ligt 1,216 s boven die grens en haalt het criterium niet.
- De snelste reproduceerbare topsnelheid is niet met een afzonderlijke herhaalde meetreeks vastgelegd.
- De gebruiker bevestigt dat de robot fysiek werkt; er is alleen geen nieuw tijd-/afstandsresultaat opgegeven waarmee kan worden vastgesteld of de 0,5 m/s-grens intussen gehaald is. Dit blijft dus een open meet-/bewijsitem, niet een hardwarestoring of ontbrekend Plan-A-ontwerpstuk.

## Publicatie

- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding en EPLAN Education-watermerk. Controleer toestemming voordat de PDF publiek wordt verspreid.
- Extra actuele foto's zijn alleen nodig als ze voor het eindrapport of de presentatie vereist zijn.
