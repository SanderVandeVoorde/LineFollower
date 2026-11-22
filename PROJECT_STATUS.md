# Projectstatus – LineFollower V2

Dit overzicht maakt onderscheid tussen wat in de repository aanwezig is, wat inhoudelijk is gedocumenteerd en wat nog fysiek of met de gebruikte hardware moet worden gecontroleerd.

## Aanwezig in de repository

- [x] Arduino Nano-programma toegevoegd als code/finaal/Arduino_Programma.ino.
- [x] Documentatie van Nano-pinnen, sensoren, PID-instellingen, encoders en seriële commando's.
- [x] BOM met geregistreerde totaalprijs van €157,86.
- [x] Bestaande datasheets en pinoutbestanden geïnventariseerd.
- [x] Fabrikantlinks toegevoegd voor ATmega328P, ESP32-C3, DRV8833, Pololu-motoren en encoderkit.
- [x] EPLAN-PDF en projectbackup aanwezig.
- [x] SolidWorks-part en STL-bestanden aanwezig.
- [x] Parcours-PDF's en SVG aanwezig.
- [x] Broncode en testinstructies toegevoegd voor vier proof-of-concepts.
- [x] Basisprogramma met EEPROM-instellingen en interrupt-start/stop toegevoegd.
- [x] Gebruiksaanwijzing, instructable en README uitgebreid.

## Nog te controleren met de echte robot

- [ ] Arduino Nano-code opnieuw compileren met de exacte Arduino IDE/core-versie.
- [ ] Definitieve firmware opnieuw testen op de robot en testresultaten registreren.
- [ ] ESP32-C3-dashboardfirmware die daadwerkelijk op de robot gebruikt wordt toevoegen. De huidige ESP32-code is alleen een proof-of-concept.
- [ ] Exacte DRV8833-breakout identificeren en fysieke pinout met foto of bestelnummer bevestigen.
- [ ] Encoderkit en motoras mechanisch controleren. De encoderkit vereist een motoruitvoering met geschikte verlengde achteras.
- [ ] Werkelijke sensorvolgorde controleren: D1 links, D8 rechts.
- [ ] EPLAN-sensorbedrading vergelijken met de fysieke sensorvolgorde en Nano-code.
- [ ] Werkelijke weerstandswaarden en aansluitingen van de batterijspanningsdeler opmeten.
- [ ] 5V-voeding onder motorbelasting controleren.
- [ ] Alle GND-verbindingen en polariteit van condensatoren controleren.
- [ ] Gewicht opnieuw meten en vermelden wat inbegrepen is.
- [ ] De 70mm-maat op de CAD-tekening definiëren met exacte meetpunten.
- [ ] Bemate mechanische tekening en samenstellingstekening exporteren.
- [ ] Actuele foto's van de afgewerkte robot toevoegen.
- [ ] Vier proof-of-concepts effectief uitvoeren en resultaten invullen.
- [ ] Toestemming controleren voor publieke verspreiding van documenten met HOGENT-auteursrechtvermelding.

## Bekende documentatiebeperkingen

- Voor de HY-S301 is geen officiële fabrikantdatasheet teruggevonden; de repository verwijst naar leveranciersinformatie.
- De chipdatasheet van de DRV8833 is beschikbaar, maar niet de exacte pinout van de gebruikte breakout.
- De pinout van een ESP32-C3 Super Mini-kloon kan per bordrevisie verschillen.
- easyeda_linefollower_planB.json beschrijft een oudere hardwareconfiguratie en mag niet als actuele bedrading worden gebruikt.
- Niet alle fabrikantdocumenten staan lokaal in de repository; voor sommige onderdelen zijn officiële externe links opgenomen.
- De ESP32-dashboardcode en volledige praktijktest zijn nog niet als definitieve, gevalideerde onderdelen beschikbaar.

## Testlog

| Datum | Batterijspanning | Kp | Ki | Kd | Gemiddelde snelheid | Ronden | Tijd | Opmerkingen |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| Eerder geregistreerd | Niet genoteerd | 30 | 0 | 0 | 0,477 m/s | 3 | 26,08 s | Rondeafstand 4,144 m |

Voeg nieuwe metingen toe zonder eerdere waarden te overschrijven.
