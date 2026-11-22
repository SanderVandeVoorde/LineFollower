# LineFollower

Autonome tweewielige linefollower voor het HOGENT-syntheseproject Electromechanica – Automatisering.

<img width="1445" height="1088" alt="Gedetailleerde lijnvolgrobot met kleurrijke elektronica" src="https://github.com/user-attachments/assets/cbce14f9-4cfc-4b19-a69f-f2a981c93331" />

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

## Hardware en maatvoering

- Geregistreerd totaalgewicht: **141 g**.
- Sensorhoogte boven de baan: **3 mm**.
- Afstand tussen sensorarray en motoras: **70 mm**.

## Werking

1. De acht sensoren meten de reflectie van de ondergrond.
2. De Nano normaliseert de meetwaarden met wit- en zwartcalibratiewaarden die handmatig via het dashboard kunnen worden vastgelegd en in EEPROM bewaard.
3. Een gewogen gemiddelde bepaalt de lijnpositie: -3500 is uiterst links en +3500 uiterst rechts.
4. De PID-regelaar berekent de correctie voor de linker- en rechtermotor.
5. De encoders meten de motorpulsen en leveren snelheidsinformatie.
6. De ESP32 ontvangt telemetrie en stuurt instellingen, START/STOP, EEPROM-opslag en handmatige calibratie via UART.

## Resultaat van een geregistreerde testrit 16-11-2026

| Grootheid | Waarde |
|---|---:|
| Aantal ronden | 3 |
| Totale afstand | 12,432 m |
| Tijd | 26,08 s |
| Gemiddelde snelheid | 0,477 m/s |
| Gemiddelde snelheid | 1,72 km/h |

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
