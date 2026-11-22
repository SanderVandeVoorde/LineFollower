# LineFollower V2 – Plan B

Autonome tweewielige linefollower voor het HOGENT-syntheseproject Electromechanica – Automatisering.

**Gekozen uitvoering: Plan B.**

**Officiële opdrachtcontrole:** zie [EVALUATIE_HOGENT.md](./EVALUATIE_HOGENT.md) voor de criterium-per-criterium-matrix, de evaluatiesnapshot, de ontbrekende POC-deelschema's en de technische aandachtspunten. Deze robot gebruikt bestaande breakoutmodules, een experimenteer-/soldeerplaat en bedrading. Een zelf ontworpen PCB, PCB-footprints/productiebestanden, SMD-assemblage en een tweede Plan-A-robot vallen buiten de gekozen scope. De Plan-B-opleverpunten en resterende bewijsstatus staan in [PLAN_B_CHECKLIST.md](./PLAN_B_CHECKLIST.md).

<img width="1445" height="1088" alt="Gedetailleerde lijnvolgrobot met kleurrijke elektronica" src="https://github.com/user-attachments/assets/cbce14f9-4cfc-4b19-a69f-f2a981c93331" />

De robot volgt een zwarte lijn op een witte ondergrond met een achtkanaals IR-sensorarray en PID-regeling. De Arduino Nano verzorgt de realtime motor- en sensorregeling. De ESP32-C3 verzorgt het Wi-Fi-dashboard en de verbinding met de Nano via UART.

> **Projectstatus (22-11-2026):** de gebruiker bevestigde dat de toenmalige robotfuncties en integraties werkten. De nieuw toegevoegde EEPROM-, debug-, calibratie-, secrets- en power-on-led-aanpassingen zijn nog niet fysiek gevalideerd. De bekende meetwaarden en de Plan-B-controle staan in [TEST_RESULTS.md](./TEST_RESULTS.md) en [PLAN_B_CHECKLIST.md](./PLAN_B_CHECKLIST.md).

## Automatische firmwarecontrole

De Nano-firmware, het basisprogramma, de Nano-POC's, de ESP32-C3-dashboardfirmware en de draadloze ESP32-POC zijn succesvol gecompileerd met GitHub Actions. [Bekijk de meest recente geslaagde build #28](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45076866650) of open de [workflow](./.github/workflows/firmware-build.yml). Deze build bevestigt compilatie, niet de nieuwe fysieke EEPROM-, calibratie- of debugfuncties.

## Systeemspecificaties

| Onderdeel | Uitvoering |
|---|---|
| Hoofdcontroller | Arduino Nano, ATmega328P, 5 V |
| Dashboardcontroller | ESP32-C3 Super Mini, Wi-Fi 2,4 GHz |
| Motorsturing | DRV8833 dual H-bridge |
| Lijnsensor | HY-S301, 8-kanaals IR-reflectiesensor met empirisch uitgelezen ADC-waarden |
| Motoren | 2× Pololu 15,25:1 Micro Metal Gearmotor HPCB 12 V, encoder-compatibele achteras |
| Encoders | 2× Pololu magnetische encoder, 12 CPR, side-entry (90°) JST SH |
| Batterij | Tattu 2S LiPo, 7,4 V nominaal, 550 mAh, 95C |
| Wielen | 2× Pololu Ø40 × 7 mm |
| Spoor | Zwarte lijn op witte ondergrond, lijnbreedte 15 mm |
| Chassis | Zelf ontworpen en 3D-geprint |

## Hardware en maatvoering

- Geregistreerd totaalgewicht: **141 g**.
- Sensorhoogte boven de baan: **3 mm**.
- Afstand tussen sensorarray en motoras: **70 mm**.
- Fysieke sensorvolgorde: D1 links tot D8 rechts.
- Bevestigde fysieke mapping: D1→A0, D2→A1, ... D8→A7. De Nano-software leest A0→A7, zodat de logische sensorkanalen D1→D8 van links naar rechts lopen.
- **EPLAN-correctie open:** blad 3 van de huidige PDF toont de omgekeerde mapping (D8→A0 ... D1→A7). De motorsturing op blad 4 komt wel overeen met de finale code.
- Batterijspanningsdeler: EPLAN-ontwerpwaarde boven 150 kΩ; werkelijke hardware 147 kΩ (100 kΩ + 47 kΩ in serie), onderste tak 47 kΩ; ADC op ESP32-C3 GPIO0. De ESP32-firmware rekent met de werkelijke 147 kΩ.

## Werking

1. De acht sensoren meten de reflectie van de ondergrond.
2. De Nano normaliseert de meetwaarden met wit- en zwartcalibratiewaarden die handmatig via het dashboard kunnen worden vastgelegd en in EEPROM bewaard.
3. Een gewogen gemiddelde bepaalt de lijnpositie: -3500 is uiterst links en +3500 uiterst rechts.
4. De PID-regelaar berekent de correctie voor de linker- en rechtermotor.
5. De encoders meten de motorpulsen en leveren snelheidsinformatie.
6. De ESP32 ontvangt telemetrie en stuurt instellingen, START/STOP, EEPROM-opslag en handmatige calibratie via UART.

## ESP32-dashboard gebruiken

1. Schakel de robot in.
2. Verbind laptop of smartphone met het Wi-Fi-netwerk dat in je lokale `code/esp32/secrets.h` is ingesteld (standaard SSID: **Linefollower-V2**).
3. Gebruik het zelfgekozen wachtwoord uit `secrets.h`; er staat bewust geen werkend wachtwoord in deze publieke repository.
4. Open **http://192.168.4.1**.
5. Bekijk sensoren, lijnpositie, batterijspanning, encoderpulsen en motor-PWM.
6. Pas PID-, snelheids- en debuginstellingen aan met **TOEPASSEN**. Gebruik **OPSLAAN** om ze in ESP32-NVS én Nano-EEPROM te bewaren. De knoppen WIT VASTLEGGEN en ZWART VASTLEGGEN voeren een handmatige sensorcalibratie uit.

Het dashboard is bedoeld voor een lokaal netwerk tussen de robot en het toestel; internet is niet nodig. De fysieke startknop op Nano D8 blijft beschikbaar. Bij **TOEPASSEN** en **OPSLAAN** wacht het dashboard op de `ACK,CFG`-bevestiging van de Nano en meldt het wanneer die ontbreekt. Als de Nano opnieuw opstart, stuurt de ESP32 de opgeslagen instellingen opnieuw zodra de Nano-telemetrie terugkeert.

## Resultaat van een geregistreerde testrit

Een eerder geregistreerde test bestond uit drie ronden op een parcours met een gemeten rondeafstand van 4,144 m.

| Grootheid | Waarde |
|---|---:|
| Aantal ronden | 3 |
| Totale afstand | 12,432 m |
| Tijd | 26,08 s |
| Gemiddelde snelheid | 0,477 m/s |
| Gemiddelde snelheid | 1,72 km/h |

Dit is één geregistreerde meting, geen gegarandeerde maximumsnelheid. Eerdere aanvullende ritten: op 16-11-2026 reed de robot het volledige parcours stabiel maar traag; op 18-11-2026 voltooide hij een ronde maar viel bijna stil en had een duwtje nodig om te vertrekken. Zie TEST_RESULTS.md.

## Encoderresultaten

De eerder uitgevoerde encodercontrole registreerde 913 pulsen links en 916 pulsen rechts over tien wielomwentelingen. Dat komt overeen met respectievelijk 91,3 en 91,6 gemeten pulsen per wielomwenteling. Zie [TEST_RESULTS.md](./TEST_RESULTS.md) voor de meetgegevens en resterende verificaties.

## Kostprijs

De bekende geprijsde BOM bedraagt **€157,91** inclusief de LiPo-lader (€117,26 nieuw, €37,15 recup en €3,50 3D-print). De bekende robotkost exclusief de lader is €137,92. De ball caster is toegevoegd maar de aankoopprijs ontbreekt, dus beide totalen moeten nog met die prijs worden aangevuld. Recupwaarden zijn vervangingsramingen, geen factuurbedragen.

## Plan B – opleverstukken

| Opleverstuk | Bestand |
|---|---|
| BOM en kostprijs | [bill of materials](./bill%20of%20materials/readme.md) |
| Elektrisch schema PDF + origineel | [EPLAN-map](./technische%20tekeningen/elektronisch/) |
| H-brug-POC | [Code](./code/proof%20of%20concepts/hbridge/HBridge_POC.ino) · [schema](./code/proof%20of%20concepts/hbridge/HBridge_POC_Schema.svg) |
| Sensor-POC | [Code](./code/proof%20of%20concepts/sensor/Sensor_Readout_POC.ino) · [schema](./code/proof%20of%20concepts/sensor/Sensor_POC_Schema.svg) |
| Finale Nano- en ESP32-firmware | [Nano](./code/finaal/Arduino_Programma.ino) · [ESP32](./code/esp32/ESP32_Programma.ino) |
| Draadloze communicatie-POC | [Wireless POC](./code/proof%20of%20concepts/wireless%20communication/ESP32_WiFi_UART_POC.ino) · [schema](./code/proof%20of%20concepts/wireless%20communication/Wireless_POC_Schema.svg) |
| Start/stop interrupt-POC | [Interrupt POC](./code/proof%20of%20concepts/interrupt/StartStop_Interrupt_POC.ino) · [schema](./code/proof%20of%20concepts/interrupt/Interrupt_POC_Schema.svg) |
| Basisprogramma: communicatie, EEPROM en interrupt | [Basisprogramma](./code/basis/Basis_Programma.ino) · [EEPROM-schema](./code/basis/EEPROM_POC_Schema.svg) |
| Instructable en handleiding | [Instructable](./instructable/readme.md) · [Handleiding](./gebruiksaanwijzing/readme.md) |
| Datasheets en pinouts | [Datasheets-index](./datasheets/readme.md) |
| Meetresultaten | [TEST_RESULTS.md](./TEST_RESULTS.md) |

**Plan-A-onderdelen zijn bewust niet opgenomen:** geen eigen PCB, PCB-footprints, SMD-assemblage, Plan-A-schema/BOM of tweede Plan-A-robot. De aanwezige SolidWorks- en STL-bestanden zijn aanvullende documentatie en geen open Plan-B-verplichting.

## Repositorystructuur

| Map | Inhoud |
|---|---|
| code/basis | Basisprogramma met seriële instellingen, EEPROM en interrupt-start/stop |
| code/finaal | Definitieve Arduino Nano-broncode en documentatie |
| code/esp32 | ESP32-C3-dashboardfirmware en documentatie |
| .github/workflows | Automatische firmware-builds voor Nano en ESP32-C3 |
| PLAN_B_CHECKLIST.md | Controle van Plan-B-opleverstukken, scope en resterend bewijs |
| code/proof of concepts | Afzonderlijke testen voor H-brug, sensoren, interrupt en draadloze communicatie |
| datasheets | Datasheets, pinouts en fabrikantlinks |
| bill of materials | Onderdelenlijst en kostprijs |
| technische tekeningen/elektronisch | EPLAN-documentatie en een oudere EasyEDA-variant |
| technische tekeningen/mechanisch | SolidWorks-model en STL-bestanden |
| parcours | Parcoursbestanden en testbaan |
| gebruiksaanwijzing | Gebruik, bediening en foutopsporing |
| instructable | Stappenplan om de robot na te bouwen |

## Belangrijke aandachtspunten

- De gebruiker heeft bevestigd dat de motordriver de DRV8833 is. De motorsturing en encoderbedrading op blad 4 van EPLAN komen overeen met de finale code; de sensorbedrading op blad 3 moet nog worden omgewisseld naar D1→A0 ... D8→A7.
- De encoders met 90°/side-entry JST SH-aansluiting zijn op de gemonteerde robot getest en leveren pulsen; de geregistreerde meting staat in [TEST_RESULTS.md](./TEST_RESULTS.md). De Pololu-kit vereist een motor met verlengde achteras.
- Het EasyEDA-bestand `easyeda_linefollower_planB.json` is een oude ontwerpvariant met een andere controller/sensorconfiguratie. Ondanks de historische bestandsnaam is dit niet het actuele Plan-B-aansluitschema en geen vereist Plan-B-opleverstuk.
- EPLAN blijft bewust op de nominale ontwerpwaarde 150 kΩ staan; de gemonteerde hardware gebruikt 147 kΩ (100 kΩ + 47 kΩ in serie). De ESP32-code gebruikt de werkelijke delerfactor.
- De HY-S301 heeft geen verifieerbare officiële fabrikantdatasheet gevonden; leveranciersspecificaties en pinout staan in datasheets/readme.md. De eerder gemeten wit-/zwartwaarden staan in TEST_RESULTS.md.
- De Nano- en ESP32-sketches en alle POC-sketches zijn succesvol gecompileerd via GitHub Actions. De gebruiker bevestigt daarnaast dat alle fysieke functies en integraties werken. Zie [PLAN_B_CHECKLIST.md](./PLAN_B_CHECKLIST.md) en [TEST_RESULTS.md](./TEST_RESULTS.md) voor de actuele bewijsstatus.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding. Controleer publicatietoestemming.

## Beveiliging en lokale Wi-Fi-configuratie

Kopieer `code/esp32/secrets.example.h` naar `code/esp32/secrets.h` en vul een uniek wachtwoord in. Doe hetzelfde voor de draadloze POC in die map. `secrets.h` wordt door `.gitignore` uitgesloten. Een eerder gepubliceerde standaardwaarde moet als gecompromitteerd worden beschouwd en moet op de robot worden gewijzigd. Zie [SECURITY.md](./SECURITY.md).

## Snel aan de slag

1. Controleer de elektrische aansluitingen en voedingsrails.
2. Upload `code/finaal/Arduino_Programma.ino` naar de Arduino Nano.
3. Upload `code/esp32/ESP32_Programma.ino` naar de ESP32-C3.
4. De eerdere sensor-, motor-, knop/LED- en encoderresultaten staan in TEST_RESULTS.md; gebruik deze als bestaande testbasis.
5. Verbind met het ESP32-Wi-Fi-netwerk en open het dashboard.
6. Start op de baan met lage snelheid en verhoog stapsgewijs.
7. Registreer tijd, afstand, batterijspanning en PID-instellingen.
