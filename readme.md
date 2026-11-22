# LineFollower V2

Autonome tweewielige linefollower voor het HOGENT-syntheseproject Electromechanica – Automatisering.

<img width="1445" height="1088" alt="Gedetailleerde lijnvolgrobot met kleurrijke elektronica" src="https://github.com/user-attachments/assets/cbce14f9-4cfc-4b19-a69f-f2a981c93331" />

De robot volgt een zwarte lijn op een witte ondergrond met een achtkanaals IR-sensorarray en PID-regeling. De Arduino Nano verzorgt de realtime motor- en sensorregeling. De ESP32-C3 verzorgt het Wi-Fi-dashboard en de verbinding met de Nano via UART.

> **Projectstatus:** de Nano- en ESP32-broncode zijn opgenomen in GitHub. De ESP32-code en Nano-code zijn inhoudelijk op hun UART-protocol afgestemd. De meest recente sensorpinmapping is aangepast aan de EPLAN-bedrading, maar moet na upload nog sensor-voor-sensor worden gevalideerd. Zie [PROJECT_STATUS.md](./PROJECT_STATUS.md) en [TEST_RESULTS.md](./TEST_RESULTS.md).

## Systeemspecificaties

| Onderdeel | Uitvoering |
|---|---|
| Hoofdcontroller | Arduino Nano, ATmega328P, 5 V |
| Dashboardcontroller | ESP32-C3 Super Mini, Wi-Fi 2,4 GHz |
| Motorsturing | DRV8833 dual H-bridge |
| Lijnsensor | HY-S301, 8-kanaals analoge IR-reflectiesensor |
| Motoren | 2× Pololu 15:1 Micro Metal Gearmotor HPCB, 12 V |
| Encoders | 2× magnetische encoderkit, 12 CPR |
| Batterij | Tattu 2S LiPo, 7,4 V nominaal, 550 mAh, 95C |
| Wielen | 2× Pololu Ø40 × 7 mm |
| Spoor | Zwarte lijn op witte ondergrond, lijnbreedte 15 mm |
| Chassis | Zelf ontworpen en 3D-geprint |

## Hardware en maatvoering

- Geregistreerd totaalgewicht: **141 g**.
- Sensorhoogte boven de baan: **3 mm**.
- Afstand tussen sensorarray en motoras: **70 mm**.
- Fysieke sensorvolgorde: D1 links tot D8 rechts.
- EPLAN-koppeling: D8→A0, D7→A1, ... D1→A7. De Nano-software leest daarom A7→A0 zodat de logische sensorkanalen D1→D8 van links naar rechts lopen.
- Batterijspanningsdeler: bovenste tak 147 kΩ (100 kΩ + 47 kΩ in serie), onderste tak 47 kΩ; ADC op ESP32-C3 GPIO0.

## Werking

1. De acht sensoren meten de reflectie van de ondergrond.
2. De Nano normaliseert de meetwaarden met vaste wit- en zwartcalibratiewaarden.
3. Een gewogen gemiddelde bepaalt de lijnpositie: -3500 is uiterst links en +3500 uiterst rechts.
4. De PID-regelaar berekent de correctie voor de linker- en rechtermotor.
5. De encoders meten de motorpulsen en leveren snelheidsinformatie.
6. De ESP32 ontvangt telemetrie en stuurt instellingen en START/STOP via UART.

## ESP32-dashboard gebruiken

1. Schakel de robot in.
2. Verbind laptop of smartphone met Wi-Fi-netwerk **Linefollower-V2**.
3. Wachtwoord: **linefollow**.
4. Open **http://192.168.4.1**.
5. Bekijk sensoren, lijnpositie, batterijspanning, encoderpulsen en motor-PWM.
6. Pas PID- en snelheidsinstellingen aan met **TOEPASSEN**. Gebruik **OPSLAAN** om ze in de ESP32 te bewaren.

Het dashboard is bedoeld voor een lokaal netwerk tussen de robot en het toestel; internet is niet nodig. De fysieke startknop op Nano D8 blijft beschikbaar.

## Resultaat van een geregistreerde testrit

Een eerder geregistreerde test bestond uit drie ronden op een parcours met een gemeten rondeafstand van 4,144 m.

| Grootheid | Waarde |
|---|---:|
| Aantal ronden | 3 |
| Totale afstand | 12,432 m |
| Tijd | 26,08 s |
| Gemiddelde snelheid | 0,477 m/s |
| Gemiddelde snelheid | 1,72 km/h |

Dit is één geregistreerde meting, geen gegarandeerde maximumsnelheid. De gebruiker meldt dat de robot inmiddels langdurig rondes kan blijven rijden; de snelste reproduceerbare tijd moet nog systematisch worden gemeten.

## Encoderresultaten

De eerder uitgevoerde encodercontrole registreerde 913 pulsen links en 916 pulsen rechts over tien wielomwentelingen. Dat komt overeen met respectievelijk 91,3 en 91,6 gemeten pulsen per wielomwenteling. Zie [TEST_RESULTS.md](./TEST_RESULTS.md) voor de meetgegevens en resterende verificaties.

## Kostprijs

De laatst geregistreerde materiaalkost bedraagt **€157,86**. De bovenste weerstand van de batterijspanningsdeler is in werkelijkheid 147 kΩ (100 kΩ + 47 kΩ in serie), niet één weerstand van 150 kΩ. De kostprijs moet opnieuw worden gecontroleerd als de recupwaarde van de extra 100 kΩ-weerstand wordt meegerekend.

## Repositorystructuur

| Map | Inhoud |
|---|---|
| code/basis | Basisprogramma met seriële instellingen, EEPROM en interrupt-start/stop |
| code/finaal | Definitieve Arduino Nano-broncode en documentatie |
| code/esp32 | ESP32-C3-dashboardfirmware en documentatie |
| .github/workflows | Automatische firmware-builds voor Nano en ESP32-C3 |
| code/proof of concepts | Afzonderlijke testen voor H-brug, sensoren, interrupt en draadloze communicatie |
| datasheets | Datasheets, pinouts en fabrikantlinks |
| bill of materials | Onderdelenlijst en kostprijs |
| technische tekeningen/elektronisch | EPLAN-documentatie en een oudere EasyEDA-variant |
| technische tekeningen/mechanisch | SolidWorks-model en STL-bestanden |
| parcours | Parcoursbestanden en testbaan |
| gebruiksaanwijzing | Gebruik, bediening en foutopsporing |
| instructable | Stappenplan om de robot na te bouwen |

## Belangrijke aandachtspunten

- De gebruiker heeft bevestigd dat de motordriver de DRV8833 is en dat EPLAN de juiste aansluitingen weergeeft.
- De encoders zijn op de gemonteerde robot getest en leveren pulsen; de geregistreerde meting staat in [TEST_RESULTS.md](./TEST_RESULTS.md).
- Het EasyEDA-bestand `easyeda_linefollower_planB.json` bevat een oudere configuratie en is niet het actuele aansluitschema.
- De EPLAN-PDF toont 150 kΩ in de bovenste batterijspanningsdeler; de gemonteerde hardware gebruikt 100 kΩ + 47 kΩ in serie. Werk de EPLAN-bron bij en exporteer de PDF opnieuw.
- De sensorpinmapping in de Nano-code is aangepast aan de EPLAN-verbindingen. Test na upload alle acht kanalen afzonderlijk voordat de snelheid wordt verhoogd.
- Broncode in GitHub is niet automatisch bewijs van een geslaagde compileer- of praktijktest.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding. Controleer publicatietoestemming.

## Snel aan de slag

1. Controleer de elektrische aansluitingen en voedingsrails.
2. Upload `code/finaal/Arduino_Programma.ino` naar de Arduino Nano.
3. Upload `code/esp32/ESP32_Programma.ino` naar de ESP32-C3.
4. Controleer eerst de sensorvolgorde en motordraairichting met de aangedreven wielen vrij van de grond.
5. Verbind met het ESP32-Wi-Fi-netwerk en open het dashboard.
6. Start op de baan met lage snelheid en verhoog stapsgewijs.
7. Registreer tijd, afstand, batterijspanning en PID-instellingen.
