# Datasheets en componentdocumentatie

Deze map bevat de technische documentatie van de belangrijkste onderdelen van de Linefollower V2.

> **Belangrijk onderscheid:** een chipdatasheet beschrijft de geïntegreerde schakeling. Een pinout van een ontwikkelbord of breakout-module beschrijft de aansluitingen op het volledige printplaatje. Die zijn niet automatisch hetzelfde.

## Microcontrollers

### Arduino Nano (ATmega328P)

| Document | Bestand / bron | Status |
|---|---|---|
| Pinout Arduino Nano | [Arduino Nano - Pinout.pdf](./Arduino%20Nano%20-%20Pinout.pdf) | Aanwezig in deze map |
| Datasheet ATmega328P | [Microchip ATmega48A/PA/88A/PA/168A/PA/328/P datasheet, DS40002061B](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf) | Officiële fabrikantbron |

De ATmega328P-datasheet beschrijft de microcontroller op de Nano. De Nano-pinout blijft nodig om de chip-pinnen te vertalen naar de D- en A-pinnen van het ontwikkelbord.

### ESP32-C3 Super Mini

| Document | Bestand / bron | Status |
|---|---|---|
| ESP32-C3 chipdatasheet | [ESP32-C3 - Datasheet.pdf](./ESP32-C3%20-%20Datasheet.pdf) | Aanwezig in deze map |
| Actuele ESP32-C3 chipdatasheet | [Espressif officiële datasheet (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf) | Officiële fabrikantbron |
| ESP32-C3 Super Mini pinout | [ESP32-C3 Super Mini - Pinout.png](./ESP32-C3%20Super%20Mini%20-%20Pinout.png) | Aanwezig in deze map |

De Espressif-datasheet is voor de ESP32-C3-chipfamilie, niet voor de specifieke Super Mini-printplaat. De pinout-afbeelding beschrijft het ontwikkelbord. Controleer bij een kloon steeds de silkscreen en de werkelijke printplaatrevisie.

## Motorsturing

### DRV8833

| Document | Bestand / bron | Status |
|---|---|---|
| DRV8833 chipdatasheet, Rev. E | [Texas Instruments DRV8833 datasheet (PDF)](https://www.ti.com/lit/ds/symlink/drv8833.pdf) | Officiële fabrikantbron |

De TI-datasheet bevat de pinconfiguratie van de DRV8833-chip, de elektrische limieten en de werking van de twee H-bruggen.

**Gebruikte module:** de gebruiker heeft bevestigd dat de gemonteerde motordriver de DRV8833-module is. De aansluitingen van de gebruikte module zijn in het projectschema (EPLAN, blad 4) vastgelegd. Gebruik voor deze robot de EPLAN-aansluitingen en niet de pinvolgorde van een willekeurige andere DRV8833-breakout. De TI-datasheet blijft de referentie voor de chip zelf.

## Lijnsensor

### HY-S301 8-kanaals IR-lijnsensor

| Document | Bestand / bron | Status |
|---|---|---|
| Productinformatie en pinout | [TinyTronics – 8x IR Lijn Tracking Module (HY-S301)](https://www.tinytronics.nl/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module) | Leveranciersinformatie; geen fabrikantdatasheet gevonden |

De leverancierspagina vermeldt een 8-kanaals reflectiesensor, een voedingsspanning van 3,3–5 V en aansluitingen GND, VCC, IR en D1–D8.

**Opmerking:** de leverancierspagina is geen officiële fabrikantdatasheet. De precieze elektrische uitgangskarakteristiek en de werking van de IR-enable-aansluiting moeten aan de hand van de gebruikte module worden bevestigd. In dit project worden de acht sensoruitgangen door de Arduino-software als analoge ingangen A0–A7 uitgelezen.

## Motoren en encoders

### Pololu 15:1 Micro Metal Gearmotor HPCB 12V

| Document | Bestand / bron | Status |
|---|---|---|
| Pololu Micro Metal Gearmotors datasheet | [Pololu N20 - Datasheet.pdf](./Pololu%20N20%20-%20Datasheet.pdf) | Aanwezig; familiegegevens |
| Exacte 15:1 HPCB 12V productgegevens (item 4788) | [Pololu productpagina](https://www.pololu.com/product/4788/specs) | Fabrikantproductinformatie |
| Pololu motorfamilie datasheet | [Pololu Micro Metal Gearmotors (PDF)](https://www.pololu.com/file/0J1487/pololu-micro-metal-gearmotors_rev-6-0.pdf) | Fabrikantbron |

De motor in de BOM is de 15,25:1 HPCB 12V-uitvoering zonder geïntegreerde encoder. Controleer het exacte bestelnummer. **Let op:** encoderkit 3081 vereist een motor met verlengde achteras. Bij de Pololu-varianten is dat de extended-shaft-uitvoering (product 4789); de standaarduitvoering 4788 heeft geen verlengde encoder-as. Controleer dit vóór je de montage als correct documenteert.

### Pololu Magnetic Encoder Pair Kit – 12 CPR

| Document | Bestand / bron | Status |
|---|---|---|
| Encoder pinout | [Encoder - Pinout.pdf](./Encoder%20-%20Pinout.pdf) | Aanwezig in deze map |
| TLE4946-2K Hall-sensor datasheet | [Encoder TLE4946-2K Hall-sensor - Datasheet.pdf](./Encoder%20TLE4946-2K%20Hall-sensor%20-%20Datasheet.pdf) | Aanwezig in deze map |
| Pololu encoderkit item 3081 | [Pololu product- en documentatiepagina](https://www.pololu.com/product/3081/resources) | Fabrikantbron |
| Encoderkit schema | [Pololu encoderkit schematische tekening (PDF)](https://www.pololu.com/file/0J814/magnetic-encoder-kit-for-micro-metal-gearmotors-schematic.pdf) | Fabrikantbron |

De encoderkit gebruikt twee Hall-sensorprintjes en magnetische schijven. De opgegeven resolutie is 12 counts per omwenteling van de motoras bij het tellen van beide flanken van beide kanalen. Voor de uitgaande gearbox-as moet de overbrengingsverhouding worden meegerekend.

## Reeds aanwezige aanvullende documentatie

- [LiPo-charger BC-4S15D - Manual.pdf](./LiPo-charger%20BC-4S15D%20-%20Manual.pdf)
- [Encoder - Pinout.pdf](./Encoder%20-%20Pinout.pdf)
- [Encoder TLE4946-2K Hall-sensor - Datasheet.pdf](./Encoder%20TLE4946-2K%20Hall-sensor%20-%20Datasheet.pdf)

## Nog te bevestigen / aan te vullen

- **DRV8833-breakout:** exacte modulepinout toevoegen zodra de gebruikte module aan de hand van een foto of bestelnummer is geïdentificeerd.
- **HY-S301:** officiële fabrikantdatasheet lijkt niet beschikbaar; leveranciersinformatie is daarom als zodanig aangeduid.
- **Arduino Nano-kloon:** de bestaande pinout moet overeenkomen met de concrete Nano-printplaat die in het project gebruikt wordt.
- **ESP32-C3 Super Mini-kloon:** de bestaande pinout moet overeenkomen met de concrete bordrevisie.

## Bronnen en versiebeheer

De fabrikantlinks verwijzen naar de oorspronkelijke documentatie van Microchip, Espressif, Texas Instruments en Pololu. Controleer bij wijzigingen aan de hardware altijd de revisie van de datasheet en de exacte componentvariant.
