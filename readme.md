# LineFollower V2

Autonome tweewielige linefollower voor het HOGENT-syntheseproject Electromechanica – Automatisering.

<img width="1445" height="1088" alt="Gedetailleerde lijnvolgrobot met kleurrijke elektronica" src="https://github.com/user-attachments/assets/cbce14f9-4cfc-4b19-a69f-f2a981c93331" />

De robot volgt een zwarte lijn op een witte ondergrond met een achtkanaals IR-sensorarray en een PID-regelaar. Een Arduino Nano verzorgt de realtime motor- en sensorregeling. Een ESP32-C3 is voorzien voor draadloze communicatie en een dashboard.

> **Projectstatus:** de Arduino Nano-firmware in deze repository is de aangeleverde projectversie. De documentatie en afzonderlijke proof-of-conceptprogramma's zijn verder uitgewerkt, maar nieuwe code en elektrische wijzigingen zijn niet automatisch hardwarematig gevalideerd. Raadpleeg PROJECT_STATUS.md voor de volledige stand van zaken.

## Systeemspecificaties

| Onderdeel | Uitvoering |
|---|---|
| Hoofdcontroller | Arduino Nano, ATmega328P, 5 V |
| Draadloze controller | ESP32-C3 Super Mini, Wi-Fi 2,4 GHz |
| Motorsturing | DRV8833 dual H-bridge |
| Lijnsensor | HY-S301, 8-kanaals analoge IR-reflectiesensor |
| Motoren | 2× Pololu 15:1 Micro Metal Gearmotor HPCB, 12 V |
| Encoders | 2× magnetische encoderkit, 12 CPR |
| Batterij | Tattu 2S LiPo, 7,4 V nominaal, 550 mAh, 95C |
| Wielen | 2× Pololu Ø40 × 7 mm |
| Spoor | Zwarte lijn op witte ondergrond, lijnbreedte 15 mm |
| Chassis | Zelf ontworpen en 3D-geprint |

## Werking

1. De acht sensoren meten de reflectie van de ondergrond.
2. De Nano normaliseert de meetwaarden met vaste wit- en zwartcalibratiewaarden.
3. Een gewogen gemiddelde bepaalt de lijnpositie: -3500 is uiterst links en +3500 uiterst rechts.
4. De PID-regelaar berekent de correctie voor de linker- en rechtermotor.
5. De encoders meten de motorpulsen en leveren snelheidsinformatie.
6. De ESP32 kan via UART gegevens ontvangen en commando's van een browser doorgeven.

De fysieke sensorvolgorde is **D1 links tot D8 rechts**. In de Nano-code komen deze overeen met A0 tot A7.

## Resultaat van een geregistreerde testrit

Een eerder geregistreerde test bestond uit drie ronden op een parcours met een gemeten rondeafstand van 4,144 m.

| Grootheid | Waarde |
|---|---:|
| Aantal ronden | 3 |
| Totale afstand | 12,432 m |
| Tijd | 26,08 s |
| Gemiddelde snelheid | 0,477 m/s |
| Gemiddelde snelheid | 1,72 km/h |

Dit is één geregistreerde meting, geen gegarandeerde maximumsnelheid. Noteer bij een nieuwe test ook batterijspanning, ondergrond, PID-instellingen en eventuele lijnverliezen.

## Kostprijs en afmetingen

- Geregistreerde totale materiaalkost: **€157,86**.
- In de vorige README stond een gewicht van **141 g**. De meetconfiguratie (met/zonder batterij, wielen en bekabeling) is nog niet vastgelegd.
- In de oude specificaties staat **70 mm** als afstand tussen sensor en motoren. De exacte meetpunten moeten nog op de mechanische tekening worden aangeduid.

## Repositorystructuur

| Map | Inhoud |
|---|---|
| code/basis | Basisprogramma met seriële instellingen, EEPROM en interrupt-start/stop |
| code/finaal | Aangeleverde Arduino Nano-firmware en documentatie |
| code/proof of concepts | Afzonderlijke testen voor H-brug, sensoren, interrupt en draadloze communicatie |
| datasheets | Datasheets, pinouts en fabrikantlinks |
| bill of materials | Onderdelenlijst en kostprijs |
| technische tekeningen/elektronisch | EPLAN-documentatie en een oudere EasyEDA-variant |
| technische tekeningen/mechanisch | SolidWorks-model en STL-bestanden |
| parcours | Parcoursbestanden en testbaan |
| gebruiksaanwijzing | Gebruik, bediening en foutopsporing |
| instructable | Stappenplan om de robot na te bouwen |

## Snel aan de slag

1. Controleer eerst de elektrische aansluitingen aan de hand van de actuele bedrading en EPLAN-documentatie.
2. Test motoren, sensoren, start/stopknop en draadloze verbinding afzonderlijk met de proof-of-concepts.
3. Upload code/finaal/Arduino_Programma.ino naar de Arduino Nano.
4. Controleer sensorcalibratie en motordraairichting met de aangedreven wielen vrij van de grond.
5. Plaats de robot op het parcours en start met de fysieke knop op D8.
6. Gebruik de gebruiksaanwijzing voor seriële commando's en configuratie.

## Belangrijke aandachtspunten

- De DRV8833-breakout is nog niet met een exact bordtype of duidelijke foto geïdentificeerd. De chipdatasheet alleen bewijst de pinvolgorde van de gebruikte module niet.
- De encoderkit moet mechanisch compatibel zijn met de achteras van de motor. Controleer het exacte Pololu-bestelnummer.
- Het EasyEDA-bestand easyeda_linefollower_planB.json bevat onderdelen van een oudere configuratie en is **niet** het actuele aansluitschema van de Nano/ESP32-C3/HY-S301-versie.
- De actuele Nano-firmware gebruikt een startknop op D8 via polling. De aparte interrupt-POC gebruikt D2 om hardware-interrupts te demonstreren.
- De ESP32-code in de wireless proof-of-concept is een demonstratiebasis, geen bewezen definitieve dashboardfirmware.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding. Controleer de toestemming voor publieke verspreiding.

## Documentatie

- [Projectstatus en openstaande controles](./PROJECT_STATUS.md)
- [Definitieve Arduino Nano-code](./code/finaal/Arduino_Programma.ino)
- [Documentatie Arduino Nano-code](./code/finaal/readme.md)
- [Datasheets en componentdocumentatie](./datasheets/readme.md)
- [Elektrische tekeningen](./technische%20tekeningen/elektronisch/readme.md)
- [Mechanische tekeningen](./technische%20tekeningen/mechanisch/readme.md)
- [Gebruiksaanwijzing](./gebruiksaanwijzing/readme.md)
- [Instructable](./instructable/readme.md)
