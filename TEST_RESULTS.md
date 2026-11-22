# Testresultaten – LineFollower V2

Dit bestand bundelt door de gebruiker gerapporteerde metingen en fysieke tests. Op 22-11-2026 bevestigde de gebruiker dat alle fysieke functies en integraties van de robot werken. Deze bevestiging actualiseert de oudere tussenstand waarin dashboard/UART, NVS, batterijmeting en voedingsrails nog niet als getest konden worden aangemerkt. Voor die recente bevestiging zijn geen nieuwe numerieke meetwaarden opgegeven.

## Mechanische gegevens

| Grootheid | Gemeten / bevestigd |
|---|---:|
| Totaalgewicht robot | 141 g |
| Sensorhoogte boven baan | 3 mm |
| Afstand sensorarray tot motoras | 70 mm |
| Lijnbreedte op de schoolbaan | 15 mm |
| Wielmaat | Ø40 × 7 mm |

## HY-S301 – gemeten sensorwaarden

Op 16-11-2026 werden de acht sensoren uitgelezen op wit en zwart. De waarden zijn door de gebruiker aangeleverd en staan in dezelfde fysieke volgorde D1 links tot D8 rechts.

| Sensor | Wit | Zwart | Middenwaarde / grens |
|---|---:|---:|---:|
| D1 | 688 | 1009 | 849 |
| D2 | 618 | 994 | 806 |
| D3 | 643 | 1003 | 823 |
| D4 | 568 | 990 | 779 |
| D5 | 590 | 997 | 794 |
| D6 | 560 | 996 | 778 |
| D7 | 588 | 994 | 791 |
| D8 | 651 | 1005 | 828 |

De grenswaarden zijn de eerder berekende middenwaarden tussen de wit- en zwartmetingen, afgerond op gehele ADC-counts. De gebruiker bevestigde dat alle acht sensoren bruikbaar reageren. De meetwaarden zijn ook de vaste wit-/zwartcalibratie in de finale Nano-firmware. De tabel staat in fysieke volgorde D1 links tot D8 rechts. De bevestigde pinmapping is D1→A0, D2→A1, ... D8→A7; de firmware leest de analoge kanalen dus A0→A7.

### Oudere meting

Een oudere sensor-POC-meting bevatte onderstaande waarden. Deze oudere meting wordt bewaard als historiek en is niet de calibratieset die in de finale Nano-firmware staat.

| Sensor | Zwart | Wit |
|---|---:|---:|
| D1 | 970 | 888 |
| D2 | 952 | 863 |
| D3 | 939 | 869 |
| D4 | 937 | 890 |
| D5 | 935 | 903 |
| D6 | 950 | 932 |
| D7 | 939 | 925 |
| D8 | 964 | 961 |

## Motoren en draairichting

Op 18-11-2026 werden de motoruitgangen en draairichtingen fysiek gecontroleerd:

| Motoruitgang | Fysieke draairichting |
|---|---|
| Linkermotor L+ | Achteruit |
| Linkermotor L− | Vooruit |
| Rechtermotor R+ | Vooruit |
| Rechtermotor R− | Achteruit |

De software-instellingen zijn daarom:
- Linkermotor geïnverteerd (LEFT_INVERTED = true).
- Rechtermotor niet geïnverteerd (RIGHT_INVERTED = false).

De gebruiker bevestigde dat beide motoren werken.

## Startknop en status-led

- Startknop: fysiek getest en door de gebruiker als werkend bevestigd.
- Status-led: fysiek getest en door de gebruiker als werkend bevestigd.
- De finale Nano-firmware gebruikt D8 met INPUT_PULLUP voor de knop en D13 voor de status-led.
- De robot start volgens de gewenste werking pas na bediening van de startknop.

## Encoders

### Handmatige kalibratie – 18-11-2026

De gebruiker draaide elk wiel exact tien volledige omwentelingen. De gemeten tellingen werden als betrouwbaar bevestigd.

| Encoder | Pulsen over 10 wielomwentelingen | Gemiddeld per wielomwenteling |
|---|---:|---:|
| Links | 913 | 91,3 |
| Rechts | 916 | 91,6 |

### Aangedreven encodertest – 18-11-2026

| Motor | Aangestuurde richting | Encoderverandering |
|---|---|---:|
| Links | L− (vooruit) | −1472 |
| Rechts | R+ (vooruit) | +1110 |

Beide encoders reageerden op de aangedreven motoren. De verschillen tussen de pulstelleresultaten tijdens deze test zijn geen bewijs van gelijke wielsnelheid: de meetduur, PWM, belasting en werkelijke snelheid kunnen verschillen. De handmatige 10-omwentelingenmeting blijft de kalibratiereferentie. De Pololu-specificatie van 12 CPR telt beide flanken van beide kanalen (x4). De Nano-firmware telt alleen de twee flanken van kanaal A en leest kanaal B voor de richting (x2), dus de verwachte telling is 6 × 15,25 = 91,5 pulsen per wielomwenteling. De metingen 91,3 en 91,6 komen daarmee overeen.

## Lijnvolging en rijtesten

| Datum / test | Resultaat |
|---|---|
| 16-11-2026 – volledig parcours | Robot reed het volledige parcours; gebruiker omschreef de werking als stabiel maar traag |
| Geregistreerde baseline | 3 ronden van 4,144 m in 26,08 s |
| Berekende baseline-snelheid | 0,477 m/s (1,72 km/h) over 12,432 m |
| 18-11-2026 – volledige ronde | Robot voltooide een ronde, maar viel bijna stil en had een duwtje nodig om te vertrekken |
| Langere duurtest | Gebruiker meldde dat de robot bijna eindeloos rondjes kon rijden; exacte duur is niet genoteerd |

De geregistreerde baselineberekening is:

v = (3 × 4,144 m) / 26,08 s = 0,4767 m/s

De snelste reproduceerbare topsnelheid is niet met een afzonderlijke meetreeks vastgelegd in de teruggevonden gesprekken. De bovenstaande waarden zijn bestaande resultaten, geen nieuwe testopdracht.

## Bekende softwarebasis van de baseline

- Basissnelheid: 70
- Kp: 30
- Ki: 0
- Kd: 0
- Maximale PWM: 160
- Sensorruisgrens: 150
- Minimale lijnsterkte: 300
- Lijnverlies-time-out: 80 ms
- PI-snelheidsregeling: uit

## ESP32-dashboard, UART en batterijmeting – fysiek bevestigd op 22-11-2026

De gebruiker bevestigt dat de volgende onderdelen fysiek werken:
- [x] ESP32 accesspoint en browserdashboard;
- [x] Nano–ESP32 UART-communicatie;
- [x] dashboard START/STOP en CFG/ACK;
- [x] instellingen bewaren in NVS en behouden na herstart;
- [x] batterijspanningsmeting via de ESP32;
- [x] 5V-buckconverter en voedingsrails onder motorbelasting.

De melding van 16-11-2026 dat Wi-Fi en batterijmeting toen nog niet aangesloten waren, was een eerdere ontwikkelstatus en is door de latere bevestiging achterhaald. Er zijn bij de bevestiging geen concrete multimeter-/ADC-afwijking, voedingsspanningen of belastingsstromen meegestuurd; die cijfers worden dus niet verzonnen.

## Software-update 22-11-2026 – nog fysiek te valideren

De repositorycode is uitgebreid met:
- Configuratieopslag in de interne Nano-EEPROM naast de ESP32-NVS-kopie.
- Handmatige wit-/zwartcalibratie via het dashboard (32 monsters per kanaal, contrastcontrole en EEPROM-opslag).
- Een optionele debugweergave met ruwe ADC-waarden en PID-/PI-diagnostiek.
- D13 als power-on-indicator in plaats van RUN-status-led.
- Lokale Wi-Fi-secrets via genegeerde secrets.h-bestanden.

Deze punten zijn softwarewijzigingen, geen fysieke testresultaten. Na upload moet je de stappen uit [POST_UPDATE_TEST_PLAN.md](./POST_UPDATE_TEST_PLAN.md) uitvoeren. Voeg hieronder pas waarden toe wanneer je ze werkelijk gemeten hebt.

## Nieuw testrecord toevoegen

| Datum | Baan | Ronden | Rondeafstand | Tijd | Batterij vóór/na | Base PWM | Kp | Ki | Kd | Opmerking |
|---|---|---:|---:|---:|---|---:|---:|---:|---:|---|
| | | | | | | | | | | |
