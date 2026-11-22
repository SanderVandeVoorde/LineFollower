# Testresultaten – LineFollower V2

Dit bestand verzamelt alleen metingen en observaties die eerder door de gebruiker zijn doorgegeven. Nieuwe tests worden als afzonderlijke regels toegevoegd; eerdere resultaten worden niet overschreven.

## Mechanische gegevens

| Grootheid | Gemeten / bevestigd |
|---|---:|
| Totaalgewicht robot | 141 g |
| Sensorhoogte boven baan | 3 mm |
| Afstand sensorarray tot motoras | 70 mm |
| Lijnbreedte op de schoolbaan | 15 mm |
| Wielmaat | Ø40 × 7 mm |

## Elektrische en functionele controle

| Onderdeel | Gerapporteerde toestand | Opmerking |
|---|---|---|
| Linkermotor | Werkt | Softwarematig geïnverteerd |
| Rechtermotor | Werkt | Normale softwarepolariteit |
| DRV8833 | Gemonteerd en bevestigd | Gebruiker bevestigt dat de afgebeelde module de DRV8833 is |
| HY-S301 | Werkt | Acht kanalen aanwezig; de individuele sensor-voor-sensor mapping moet na de laatste firmwaremapping opnieuw worden bevestigd |
| Start/stopknop | Werkt | Finale firmware gebruikt D8 met INPUT_PULLUP |
| Status-led | Werkt | Finale firmware gebruikt D13 |
| Encoders | Werken | Onderstaande pulsmeting |
| ESP32-dashboard | Firmware aanwezig | De laatste gecombineerde UART-/dashboardtest moet na de laatste softwarewijzigingen worden herhaald |

## Encodercontrole

Eerder gemeten over tien omwentelingen van elk wiel:

| Encoder | Pulsen over 10 wielomwentelingen | Gemiddeld per wielomwenteling |
|---|---:|---:|
| Links | 913 | 91,3 |
| Rechts | 916 | 91,6 |

Deze gemeten waarden zijn de pulsen die de huidige encoderuitlezing registreerde. Gebruik ze als empirische referentie voor het gemonteerde systeem; leid hieruit niet zonder aanvullende definitie van CPR, flanktelling en overbrengingsverhouding een andere encoderresolutie af.

## Lijnvolging

| Test | Ronden | Rondeafstand | Totale afstand | Tijd | Gemiddelde snelheid |
|---|---:|---:|---:|---:|---:|
| Geregistreerde baseline | 3 | 4,144 m | 12,432 m | 26,08 s | 0,477 m/s (1,72 km/h) |

Berekening:

`v = (3 × 4,144 m) / 26,08 s = 0,4767 m/s`

De gebruiker meldde daarnaast dat de robot bijna eindeloos rondes kan blijven rijden. Voor die observatie is geen exacte duur geregistreerd. De snelste reproduceerbare tijd moet nog met meerdere herhalingen worden bepaald.

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

Gebruik de waarden hierboven alleen als de baseline-instellingen; controleer de actuele ESP32-opgeslagen configuratie vóór elke nieuwe test.

## Nog uit te voeren verificaties

- [ ] Na upload van de huidige Nano-firmware alle acht sensoren afzonderlijk testen en de volgorde D1 links tot D8 rechts bevestigen.
- [ ] H-brug-POC uitvoeren met lage PWM en de wielen vrij van de grond.
- [ ] De gecombineerde Nano–ESP32-UART-verbinding testen en bevestigen dat de Nano `ACK,CFG` terugstuurt.
- [ ] Dashboard START en STOP testen; ook de fysieke D8-knop testen.
- [ ] Dashboard-batterijspanning vergelijken met een multimeter bij minstens twee batterijspanningen.
- [ ] Instellingen opslaan, ESP32 herstarten en controleren of de instellingen behouden blijven.
- [ ] De 5V-rail meten tijdens starten, rijden en bochten.
- [ ] Minstens vijf volledige snelheidsmetingen uitvoeren met dezelfde baan en dezelfde meetmethode.
- [ ] Mechanische trillingen/rammelen in bochten inspecteren en registreren.

## Nieuw testrecord toevoegen

| Datum | Baan | Ronden | Rondeafstand | Tijd | Batterij vóór/na | Base PWM | Kp | Ki | Kd | Opmerking |
|---|---|---:|---:|---:|---|---:|---:|---:|---:|---|
| | | | | | | | | | | |
