# Projectstatus – LineFollower V2

Laatst bijgewerkt: 22-11-2026.

Dit bestand scheidt de repositorystatus, eerder door de gebruiker bevestigde resultaten en de nog noodzakelijke compileer- en hardwaretests.

## Aanwezig in GitHub

- [x] Arduino Nano-firmware: `code/finaal/Arduino_Programma.ino`.
- [x] ESP32-C3-dashboardfirmware: `code/esp32/ESP32_Programma.ino`.
- [x] Basisprogramma en vier afzonderlijke POC-sketches.
- [x] Documentatie voor de pinnen, sensorcalibratie, PID, encoders en UART.
- [x] Dashboarddocumentatie met Wi-Fi, NVS-instellingen en batterijmeting.
- [x] BOM, gebruiksaanwijzing, instructable, hoofd-README en mechanische/elektrische documentatie.
- [x] Testresultaten verzameld in [TEST_RESULTS.md](./TEST_RESULTS.md).
- [x] Bestaande datasheets, pinouts en officiële fabrikantlinks geïnventariseerd.
- [x] EPLAN-PDF en EPLAN-projectbackup.
- [x] SolidWorks-part en STL-bestanden.
- [x] Parcours-PDF's en SVG.
- [x] GitHub Actions-buildworkflow toegevoegd: `.github/workflows/firmware-build.yml`.

## Door gebruiker bevestigde hardware

- Robot is volledig gemonteerd.
- DRV8833 is de gebruikte motordriver; de gebruiker bevestigt dat EPLAN de juiste aansluitingen weergeeft.
- Beide motoren, sensoren, encoders, startknop en status-led zijn volgens de gebruiker functioneel.
- Sensorhoogte: 3 mm.
- Afstand sensorarray tot motoras: 70 mm.
- Totaalgewicht: 141 g.
- Lijnbreedte van de schoolbaan: 15 mm.
- Batterijspanningsdeler: bovenste tak 147 kΩ (100 kΩ + 47 kΩ in serie), onderste tak 47 kΩ.
- Encoders: eerder 913 pulsen links en 916 pulsen rechts gemeten over tien wielomwentelingen.
- Robot rijdt meerdere rondes; de gebruiker rapporteert bijna continue rondes.

## Geregistreerde rijtest

- 3 ronden.
- 4,144 m per ronde.
- 12,432 m totale afstand.
- 26,08 s totale tijd.
- Gemiddeld 0,477 m/s (1,72 km/h).

De snelste reproduceerbare snelheid is nog niet systematisch vastgesteld. De details staan in [TEST_RESULTS.md](./TEST_RESULTS.md).

## Softwarewijzigingen en controle

- [x] Nano-sensorpinmapping afgestemd op de EPLAN-bedrading: D8→A0 ... D1→A7; softwarevolgorde A7→A0.
- [x] ESP32- en Nano-UART-protocol inhoudelijk vergeleken: 115200 baud, START, STOP, CFG met twaalf parameters, ACK,CFG en T-telemetrie met 26 velden.
- [x] ESP32-batterijfactor afgestemd op de fysieke weerstanden: (147 kΩ + 47 kΩ) / 47 kΩ = 194 / 47.
- [x] Nano speed-PI feed-forward aangepast zodat ingestelde bochtvertraging ook bij ingeschakelde PI-snelheidsregeling behouden blijft.
- [x] ESP32-dashboard verbetert de verbindingsstatus: toont pas Nano-verbonden na ontvangst van telemetrie en geeft configuratiebevestiging apart weer.
- [x] GitHub Actions-workflow toegevoegd om Nano- en ESP32-C3-sketches te compileren.
- [x] GitHub Actions-build geslaagd: Nano-firmware, basisprogramma, drie Nano-POC's, ESP32-dashboard en ESP32-UART-POC zijn succesvol gecompileerd ([run 45034747024](https://github.com/SanderVandeVoorde/LineFollower/actions/runs/45034747024), commit c11c9fa).
- [x] Eerdere fysieke sensortests, motor- en draairichtingstests, knop/LED-tests en encoderkalibratie zijn vastgelegd in TEST_RESULTS.md.
- [ ] De laatste repositorywijzigingen zijn succesvol gecompileerd; een nieuwe fysieke uploadtest is alleen nodig als de gewijzigde firmware daadwerkelijk op de robot wordt gebruikt.
- [ ] In de teruggevonden gesprekken is nog geen afgerond fysiek resultaat vastgelegd voor ESP32-dashboard/UART/START-STOP/NVS of batterijmeting; status niet als bewezen markeren zonder meetresultaat.

## Elektrische documentatie

- [x] DRV8833-module-identiteit bevestigd door de gebruiker; EPLAN is de referentie voor de aansluitingen.
- [x] Werkelijke batterijspanningsdeler gedocumenteerd als 147 kΩ boven (100 kΩ + 47 kΩ in serie) en 47 kΩ onder.
- [x] EPLAN blijft op 150 kΩ staan als nominale ontwerpwaarde; gebruiker wil het schema niet wijzigen.
- [x] Werkelijke gemonteerde bovenste tak is 147 kΩ (100 kΩ + 47 kΩ in serie); de ESP32-firmware gebruikt de werkelijke delerfactor 194/47.
- [ ] Alleen indien de meetnauwkeurigheid opnieuw wordt gekalibreerd: vergelijk de dashboardwaarde met een multimeter. Dit is geen reden om EPLAN te wijzigen.
- [ ] 5V-buckconverter onder motorbelasting meten.
- [ ] Voedingsrails, gemeenschappelijke GND en condensatorpolariteiten nogmaals fysiek controleren.

## Mechanische documentatie

- [x] Chassis-SLDPRT en STL-bestanden in GitHub.
- [x] Gebruiker bevestigt sensorhoogte 3 mm, sensorarray-tot-motoras 70 mm en totaalgewicht 141 g.
- [x] Geen SolidWorks-project of extra chassisafmetingen nodig voor de huidige afwerking; de relevante maten zijn al bevestigd: 3 mm sensorhoogte, 70 mm sensorarray-tot-motoras en 141 g totaalgewicht.
- [ ] Alleen indien het eindrapport foto's vereist: actuele foto's van de afgewerkte robot toevoegen.

## Datasheets

- [x] Bestaande lokale PDF's en pinoutbestanden opgenomen in `datasheets/`.
- [x] Officiële fabrikantlinks voor ATmega328P, ESP32-C3, DRV8833 en Pololu motor/encoder toegevoegd aan de datasheetindex.
- [x] HY-S301 online onderzocht: geen verifieerbare officiële fabrikantdatasheet gevonden. Leveranciersspecificaties en pinout zijn gedocumenteerd met bronlinks in datasheets/readme.md.
- [ ] Controleer of de lokale Nano- en ESP32-C3-pinoutafbeeldingen overeenkomen met de exacte gebruikte printplaatrevisies.

## Publicatie en rapport

- [ ] Controleer publicatietoestemming voor de EPLAN-PDF met HOGENT-auteursrechtvermelding en EPLAN Education-watermerk.
- [ ] Definitieve foto's, nieuwe reproduceerbare snelheidsmetingen en de laatste hardwaretestresultaten toevoegen.

## Bekende beperkingen

- GitHub Actions is toegevoegd, maar een geslaagde build is nog niet bevestigd.
- De sensorpinvolgorde in de code volgt de EPLAN-verbindingen; fysieke validatie na de laatste upload blijft nodig.
- De EPLAN-PDF toont nog 150 kΩ en is dus nog niet bijgewerkt naar de werkelijk gemonteerde 147 kΩ.
- De EPLAN-bron en het SolidWorks-model kunnen niet vanuit deze tekstbestanden worden aangepast; daarvoor is de oorspronkelijke EPLAN-/SolidWorks-applicatie nodig.
- Een code-upload of documentwijziging is geen vervanging voor een test op de fysieke robot.
