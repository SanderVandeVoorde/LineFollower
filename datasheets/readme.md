# Datasheets en componentdocumentatie

Deze map bevat de technische documentatie van de belangrijkste onderdelen van de Linefollower.

> **Belangrijk onderscheid:** een chipdatasheet beschrijft de geïntegreerde schakeling. Een pinout van een ontwikkelbord of breakout-module beschrijft de aansluitingen op het volledige printplaatje. Die zijn niet automatisch hetzelfde.

## Microcontrollers

### Arduino Nano (ATmega328P)

| Document | Bestand / bron | Status |
|---|---|---|
| Pinout Arduino Nano | [Arduino Nano - Pinout.pdf](./Arduino%20Nano%20-%20Pinout.pdf) | Aanwezig in deze map |
| Datasheet ATmega328P | [Microchip ATmega48A/PA/88A/PA/168A/PA/328/P datasheet, DS40002061B](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf) | Officiële fabrikantbron |

### ESP32-C3 Super Mini

| Document | Bestand / bron | Status |
|---|---|---|
| ESP32-C3 chipdatasheet | [ESP32-C3 - Datasheet.pdf](./ESP32-C3%20-%20Datasheet.pdf) | Aanwezig in deze map |
| Actuele ESP32-C3 chipdatasheet | [Espressif officiële datasheet (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf) | Officiële fabrikantbron |
| ESP32-C3 Super Mini pinout | [ESP32-C3 Super Mini - Pinout.png](./ESP32-C3%20Super%20Mini%20-%20Pinout.png) | Aanwezig in deze map |

## Motorsturing

### DRV8833

| Document | Bestand / bron | Status |
|---|---|---|
| DRV8833 chipdatasheet, Rev. E | [Texas Instruments DRV8833 datasheet (PDF)](https://www.ti.com/lit/ds/symlink/drv8833.pdf) | Officiële fabrikantbron |

## Lijnsensor

### HY-S301 8-kanaals IR-lijnsensor

| Document | Bestand / bron | Status |
|---|---|---|
| Productinformatie en pinout | [TinyTronics – 8x IR Lijn Tracking Module (HY-S301)](https://www.tinytronics.nl/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module) | Leveranciersinformatie |
| Aanvullende HY-S301-modulebeschrijving | [Einstronic – HY-S301 8-Channel Line Tracking Sensor](https://einstronic.com/product/hy-s301-8-channel-line-tracking-sensor-module/) | Leveranciersinformatie |
| Aanvullende modulebeschrijving | [Future Electro – HY-S301 8-channel IR sensor](https://futureelectro.in/products/8-channel-infrared-detection-line-tracking-sensor-module-hy-s301) | Leveranciersinformatie |

### Gevonden modulespecificaties

Specificaties:
- Voedingsspanning: 3,3–5 V DC.
- Aantal kanalen: 8 afzonderlijke IR-zender/ontvangerparen.
- IR-golflengte: circa 950 nm.
- Aansluitingen: GND, VCC, IR-enable en D1–D8.
- IR-enable: inschakelsignaal voor de IR-leds; leveranciers geven aan dat dit aan 3,3 V of 5 V kan worden gelegd.
- Afmetingen: ongeveer 67 × 17 mm.
- Montage: twee gaten van 3 mm.

**Datasheetstatus:** Er is geen tot weinig officiële fabrikantdatasheet of origineel schema voor exact deze HY-S301-print. De bovenstaande leverancierspagina's zijn daarom de best beschikbare openbare documentatie, geen officiële fabrikantdatasheet.

## Motoren en encoders

### Pololu 15:1 Micro Metal Gearmotor HPCB 12V

| Document | Bestand / bron | Status |
|---|---|---|
| Pololu Micro Metal Gearmotors datasheet | [Pololu N20 - Datasheet.pdf](./Pololu%20N20%20-%20Datasheet.pdf) | Aanwezig; familiegegevens |
| Exacte 15:1 HPCB 12V productgegevens (item 4788) | [Pololu productpagina](https://www.pololu.com/product/4788/specs) | Fabrikantproductinformatie |
| Pololu motorfamilie datasheet | [Pololu Micro Metal Gearmotors (PDF)](https://www.pololu.com/file/0J1487/pololu-micro-metal-gearmotors_rev-6-0.pdf) | Fabrikantbron |


### Pololu Magnetic Encoder Pair Kit – 12 CPR, side-entry (90°) JST SH

| Document | Bestand / bron | Status |
|---|---|---|
| Encoder pinout | [Encoder - Pinout.pdf](./Encoder%20-%20Pinout.pdf) | Aanwezig in deze map; controleer pinrichting t.o.v. de connector |
| Encoderkit met side-entry connector, item 4761 | [Pololu productpagina](https://www.pololu.com/product/4761/specs) | Fabrikantbron; komt overeen met de door de gebruiker bevestigde 90°/side-entry connector |
| Encoderkit resources en schema | [Pololu product- en documentatiepagina](https://www.pololu.com/product/4761/resources) | Fabrikantbron |
| Encoderkit elektrisch schema | [Pololu 4760/4761 schema (PDF)](https://www.pololu.com/file/0J1718/pololu-4760-4761-schematic.pdf) | Fabrikantbron |
| Hall-sensor DRV5013 | [Texas Instruments DRV5013 datasheet](https://www.ti.com/lit/ds/symlink/drv5013.pdf) | Fabrikantbron |
| Compatibele motor met verlengde achteras | [Pololu 15:1 HPCB 12V, item 4789](https://www.pololu.com/product/4789/specs) | Fabrikantbron |

De 6-pins JST SH-signalen volgens de Pololu-familieschema's zijn:
- Pin 1: GND
- Pin 2: encoderkanaal B
- Pin 3: encoderkanaal A
- Pin 4: VCC (2,7–18 V)
- Pin 5: motoraansluiting M2
- Pin 6: motoraansluiting M1

## Reeds aanwezige aanvullende documentatie

- [LiPo-charger BC-4S15D - Manual.pdf](./LiPo-charger%20BC-4S15D%20-%20Manual.pdf)
- [Encoder - Pinout.pdf](./Encoder%20-%20Pinout.pdf)
- [Encoder TLE4946-2K Hall-sensor - Datasheet.pdf](./Encoder%20TLE4946-2K%20Hall-sensor%20-%20Datasheet.pdf)

## Beschikbaarheid en documentstatus

| Component | In GitHub als lokaal bestand | Officiële externe bron / status |
|---|---|---|
| Arduino Nano | Nano-pinout PDF aanwezig | ATmega328P-chipdatasheet gelinkt bij Microchip; PDF niet als lokaal bestand gekopieerd |
| ESP32-C3 Super Mini | ESP32-C3-chipdatasheet PDF en Super Mini-pinout PNG aanwezig | Espressif fabrikantdocumentatie |
| DRV8833 | Geen afzonderlijke module-PDF | TI-chipdatasheet gelinkt; moduleaansluitingen volgen het bevestigde EPLAN-blad 4 |
| HY-S301 | Geen fabrikant-PDF gevonden | Leveranciersinformatie en pinout gelinkt; geen verifieerbare officiële fabrikantdatasheet gevonden |
| Pololu motor | Micro Metal Gearmotor-familie-PDF aanwezig | Product met extended-shaft voor encodercompatibiliteit |
| Pololu encoder | Encoderpinout PDF aanwezig; TLE4946 PDF behouden als oudere componentdocumentatie | TI DRV5013-datasheet gelinkt als actuele referentie |
