# Testresultaten – LineFollower V2

Dit bestand bundelt eerder door de gebruiker gerapporteerde metingen en fysieke tests uit de projectgesprekken. Een test wordt niet opnieuw als openstaand gemarkeerd enkel omdat hij niet in de laatste code-upload opnieuw is uitgevoerd. Waar een test niet terug te vinden is, staat dat expliciet vermeld.

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

De grenswaarden zijn de eerder berekende middenwaarden tussen de wit- en zwartmetingen, afgerond op gehele ADC-counts. De gebruiker bevestigde dat alle acht sensoren bruikbaar reageren. De meetwaarden zijn ook de vaste wit-/zwartcalibratie in de finale Nano-firmware.

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

Beide encoders reageerden op de aangedreven motoren. De verschillen tussen de pulstelleresultaten tijdens deze test zijn geen bewijs van gelijke wielsnelheid: de meetduur, PWM, belasting en werkelijke snelheid kunnen verschillen. De handmatige 10-omwentelingenmeting blijft de kalibratiereferentie.

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

## ESP32-dashboard, UART en batterijmeting – historische status

In de teruggevonden projectgesprekken van 16-11-2026 meldde de gebruiker dat de lamp/statusindicator, batterijspanningsmeting en Wi-Fi-communicatie toen nog niet aangesloten waren. Ik heb geen latere, concreet gerapporteerde fysieke testuitslag teruggevonden voor:
- ESP32 accesspoint en browserdashboard;
- Nano–ESP32 UART-communicatie;
- dashboard START/STOP en CFG/ACK;
- instellingen bewaren in NVS en behouden na herstart;
- vergelijking van de batterijmeting met een multimeter;
- 5V-buckconverter en voedingsrails onder motorbelasting.

Dit betekent niet dat deze tests niet later zijn uitgevoerd; alleen dat er in de doorzochte gesprekken geen meetresultaat voor terug te vinden is. De firmware compileert via GitHub Actions, maar compileren is geen fysieke integratietest.

## Nieuw testrecord toevoegen

| Datum | Baan | Ronden | Rondeafstand | Tijd | Batterij vóór/na | Base PWM | Kp | Ki | Kd | Opmerking |
|---|---|---:|---:|---:|---|---:|---:|---:|---:|---|
| | | | | | | | | | | |
