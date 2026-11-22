# Projectstatus – LineFollower V2

Laatst bijgewerkt: 22-11-2026.

Dit overzicht maakt onderscheid tussen bestanden die in GitHub aanwezig zijn, code die inhoudelijk is nagekeken en tests die nog op de fysieke robot moeten worden uitgevoerd.

## Aanwezig in GitHub

- [x] Arduino Nano-firmware: `code/finaal/Arduino_Programma.ino`.
- [x] ESP32-C3-dashboardfirmware: `code/esp32/ESP32_Programma.ino`.
- [x] Documentatie voor Nano-pinnen, sensorcalibratie, PID-instellingen, encoders en UART-protocol.
- [x] ESP32-dashboarddocumentatie met Wi-Fi, UART, NVS-instellingen en batterijmeting.
- [x] Vier POC-programma's: H-brug, sensoruitlezing, interrupt en draadloze UART.
- [x] Basisprogramma met EEPROM-instellingen en interrupt-start/stop.
- [x] BOM met laatst geregistreerde kostprijs van €157,86.
- [x] Bestaande datasheets, pinouts en officiële fabrikantlinks geïnventariseerd.
- [x] EPLAN-PDF en EPLAN-projectbackup.
- [x] SolidWorks-part en STL-bestanden.
- [x] Parcours-PDF's en SVG.
- [x] Gebruiksaanwijzing, instructable en README bijgewerkt.

## Door gebruiker bevestigde hardware- en meetgegevens

- Robot is volledig gemonteerd.
- Beide motoren, acht sensoren, beide encoders, startknop en status-led werken volgens de gebruiker.
- Robot kan de baan volgen en rijdt langdurig meerdere rondes.
- Sensorhoogte boven de baan: 3 mm.
- Afstand sensorarray tot motoras: 70 mm.
- Totaalgewicht: 141 g.
- Batterijspanningsdeler: bovenste tak 147 kΩ (100 kΩ + 47 kΩ in serie), onderste tak 47 kΩ.
- Eerder geregistreerde test: 3 ronden, 4,144 m per ronde, 26,08 s totaal, gemiddeld 0,477 m/s.
- Doel van de volgende praktijktests: maximale reproduceerbare snelheid verhogen.

## Softwarecontrole

- [x] ESP32-broncode toegevoegd aan GitHub.
- [x] ESP32- en Nano-UART-protocol inhoudelijk vergeleken: 115200 baud, START, STOP, CFG met twaalf parameters, ACK,CFG en T-telemetrie met 26 velden.
- [x] ESP32-batterijfactor gecontroleerd op de fysieke weerstanden: (147 kΩ + 47 kΩ) / 47 kΩ = 194 / 47.
- [x] Nano-sensorpinmapping aangepast aan de EPLAN-bedrading: D8→A0 ... D1→A7. De software leest A7→A0 om de logische volgorde D1 links tot D8 rechts te behouden.
- [ ] Nano-code compileren met de exacte Arduino IDE- en Nano-processorinstellingen.
- [ ] ESP32-code compileren met een geschikte ESP32-C3-boarddefinitie en Arduino-ESP32-core.
- [ ] Beide programma's samen op de robot uploaden en de UART-verbinding testen.
- [ ] Sensor-POC uitvoeren en elk kanaal fysiek afzonderlijk bevestigen.
- [ ] Batterijspanning op dashboard vergelijken met multimeter en meetfactor zo nodig kalibreren.
- [ ] Opslaan/herstellen van dashboardinstellingen na ESP32-herstart testen.
- [ ] Dashboard START/STOP en fysieke startknop testen.

## Elektrische documentatie en hardware

- [ ] EPLAN-componentwaarde aanpassen: bovenste spanningsdeler is 100 kΩ + 47 kΩ in serie (147 kΩ), niet 150 kΩ. Daarna PDF opnieuw exporteren.
- [x] Gebruiker heeft bevestigd dat de afgebeelde motordrivermodule de DRV8833 is.
- [ ] De fysieke pinlabels en oriëntatie van de DRV8833-module nog één keer vergelijken met EPLAN vóór een nieuwe bedradingstest.
- [ ] 5V-buckconverter onder motorbelasting meten.
- [ ] Gemeenschappelijke GND, condensatorpolariteiten en motorontstoring fysiek controleren.
- [ ] Controleer dat de UART-spanningsdeler en TX/RX-kruising overeenkomen met het schema.

## Mechanisch en projectdocumentatie

- [x] Gebruiker bevestigt sensorhoogte 3 mm.
- [x] Gebruiker bevestigt 70 mm tussen sensorarray en motoras.
- [x] Gebruiker bevestigt totaalgewicht 141 g.
- [ ] Bemate mechanische tekening en samenstellingstekening exporteren vanuit SolidWorks.
- [ ] Encoder/motorvariant en achterascompatibiliteit definitief documenteren.
- [ ] Actuele foto's van de volledige afgewerkte robot toevoegen.
- [ ] Publicatietoestemming voor documenten met HOGENT-auteursrechtvermelding controleren.

## Snelheidstesten

| Test | Batterijspanning | Kp | Ki | Kd | Gemiddelde snelheid | Ronden | Tijd | Opmerkingen |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| Eerder geregistreerd | Niet genoteerd | 30 | 0 | 0 | 0,477 m/s | 3 | 26,08 s | Rondeafstand 4,144 m |

Nieuwe metingen toevoegen zonder eerdere waarden te overschrijven. Noteer steeds baanvariant, rondeafstand, aantal rondes, tijd, batterijspanning en alle actieve regelinstellingen.

## Bekende beperkingen

- De HY-S301 heeft in deze repository leveranciersinformatie, maar geen geverifieerde officiële fabrikantdatasheet.
- De DRV8833-chipdatasheet is beschikbaar, maar de exacte breakoutmodulepinout is nog niet bevestigd.
- De ESP32-C3 Super Mini-kloon kan per printrevisie verschillen; controleer de bordopdruk.
- De EPLAN-PDF bevat nog de oude 150 kΩ-waarde en moet opnieuw worden geëxporteerd.
- De meest recente Nano-sensorpinmapping is een softwarecorrectie op basis van de EPLAN-verbindingen; fysieke kanaaltest na upload blijft noodzakelijk.
- Code die is opgeslagen in GitHub is niet automatisch gecompileerd of hardwarematig gevalideerd.
- De EPLAN-PDF bevat een HOGENT-auteursrechtvermelding; publicatietoestemming is niet bevestigd.
