# Datasheets en componentdocumentatie

Deze map bevat de technische documentatie van de belangrijkste onderdelen van de Linefollower.

> **Belangrijk onderscheid:** een chipdatasheet beschrijft de geïntegreerde schakeling. Een pinout van een ontwikkelbord of breakout-module beschrijft de aansluitingen op het volledige printplaatje. Die zijn niet automatisch hetzelfde.

## Microcontrollers

### Arduino Nano (ATmega328P)

| Document | Bestand / bron | Status |
|---|---|---|
| Pinout Arduino Nano | [Arduino Nano - Pinout.pdf](./Arduino%20Nano%20-%20Pinout.pdf) | Aanwezig in deze map |
| Datasheet ATmega328P | [Microchip ATmega48A/PA/88A/PA/168A/PA/328/P datasheet, DS40002061B](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf) | Officiële fabrikantbron |

De ATmega328P-datasheet beschrijft de microcontroller op de Nano. De Nano-pinout blijft nodig om de chip-pinnen te vertalen naar de D- en A-pinnen van het ontwikkelbord. De interne EEPROM is onderdeel van de ATmega328P; de finale firmware gebruikt deze voor instellingen en sensorcalibratie.

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

De TI-datasheet bevat de pinconfiguratie van de DRV8833-chip, de elektrische limieten en de werking van de twee H-bruggen. De functionele H-brug-POC-aansluitingen staan in [HBridge_POC_Schema.svg](../code/proof%20of%20concepts/hbridge/HBridge_POC_Schema.svg).

**Gebruikte module:** de gebruiker heeft bevestigd dat de gemonteerde motordriver de DRV8833-module is. De aansluitingen van de gebruikte module zijn in het projectschema (EPLAN, blad 4) vastgelegd. Gebruik voor deze robot de EPLAN-aansluitingen en niet de pinvolgorde van een willekeurige andere DRV8833-breakout. De TI-datasheet blijft de referentie voor de chip zelf.

## Lijnsensor

### HY-S301 8-kanaals IR-lijnsensor

| Document | Bestand / bron | Status |
|---|---|---|
| Productinformatie en pinout | [TinyTronics – 8x IR Lijn Tracking Module (HY-S301)](https://www.tinytronics.nl/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module) | Leveranciersinformatie |
| Aanvullende HY-S301-modulebeschrijving | [Einstronic – HY-S301 8-Channel Line Tracking Sensor](https://einstronic.com/product/hy-s301-8-channel-line-tracking-sensor-module/) | Leveranciersinformatie |
| Aanvullende modulebeschrijving | [Future Electro – HY-S301 8-channel IR sensor](https://futureelectro.in/products/8-channel-infrared-detection-line-tracking-sensor-module-hy-s301) | Leveranciersinformatie |

### Gevonden modulespecificaties

De geraadpleegde leveranciers beschrijven de HY-S301 als een reflectieve IR-array met acht kanalen:
- Voedingsspanning: 3,3–5 V DC.
- Aantal kanalen: 8 afzonderlijke IR-zender/ontvangerparen.
- IR-golflengte: circa 950 nm.
- Aansluitingen: GND, VCC, IR-enable en D1–D8.
- IR-enable: inschakelsignaal voor de IR-leds; leveranciers geven aan dat dit aan 3,3 V of 5 V kan worden gelegd.
- Afmetingen volgens TinyTronics: ongeveer 67 × 17 mm.
- Montage: twee gaten van 3 mm.
- De uitgang is volgens leveranciers hoog bij voldoende gereflecteerd IR-licht.

**Belangrijk onderscheid voor dit project:** leveranciers noemen de uitgangen vaak digitaal, maar de gemonteerde robot heeft de D1–D8-signalen met de Arduino-ADC uitgelezen en de gebruiker heeft per kanaal verschillende wit-/zwartwaarden gerapporteerd (zie [TEST_RESULTS.md](../TEST_RESULTS.md)). De projectfirmware gebruikt dus de empirisch gemeten ADC-waarden van deze concrete module. Die gemeten werking is leidend voor de robot; generaliseer de digitale uitgangsbeschrijving van een winkelpagina niet naar de gemonteerde print zonder meting.

**Datasheetstatus:** ik vond geen verifieerbare officiële fabrikantdatasheet of origineel schema voor exact deze HY-S301-print. De bovenstaande leverancierspagina's zijn daarom de best beschikbare openbare documentatie, geen officiële fabrikantdatasheet.

## Motoren en encoders

### Pololu 15:1 Micro Metal Gearmotor HPCB 12V

| Document | Bestand / bron | Status |
|---|---|---|
| Pololu Micro Metal Gearmotors datasheet | [Pololu N20 - Datasheet.pdf](./Pololu%20N20%20-%20Datasheet.pdf) | Aanwezig; familiegegevens |
| Exacte 15:1 HPCB 12V productgegevens (item 4788) | [Pololu productpagina](https://www.pololu.com/product/4788/specs) | Fabrikantproductinformatie |
| Pololu motorfamilie datasheet | [Pololu Micro Metal Gearmotors (PDF)](https://www.pololu.com/file/0J1487/pololu-micro-metal-gearmotors_rev-6-0.pdf) | Fabrikantbron |

De motor is een 15,25:1 HPCB 12V-uitvoering. De fysiek gemonteerde en geteste encoderkit vereist een verlengde achteras; de overeenkomstige Pololu-uitvoering is item 4789. Item 4788 is de standaardmotor zonder verlengde encoder-as. Het exacte bestelnummer is niet uit de aankoopgegevens terug te vinden, daarom wordt 4789 als compatibele referentie vermeld en niet als bewezen aankoop-SKU.

### Pololu Magnetic Encoder Pair Kit – 12 CPR, side-entry (90°) JST SH

| Document | Bestand / bron | Status |
|---|---|---|
| Encoder pinout | [Encoder - Pinout.pdf](./Encoder%20-%20Pinout.pdf) | Aanwezig in deze map; controleer pinrichting t.o.v. de connector |
| Encoderkit met side-entry connector, item 4761 | [Pololu productpagina](https://www.pololu.com/product/4761/specs) | Fabrikantbron; komt overeen met de door de gebruiker bevestigde 90°/side-entry connector |
| Encoderkit resources en schema | [Pololu product- en documentatiepagina](https://www.pololu.com/product/4761/resources) | Fabrikantbron |
| Encoderkit elektrisch schema | [Pololu 4760/4761 schema (PDF)](https://www.pololu.com/file/0J1718/pololu-4760-4761-schematic.pdf) | Fabrikantbron |
| Hall-sensor DRV5013 | [Texas Instruments DRV5013 datasheet](https://www.ti.com/lit/ds/symlink/drv5013.pdf) | Fabrikantbron |
| Compatibele motor met verlengde achteras | [Pololu 15:1 HPCB 12V, item 4789](https://www.pololu.com/product/4789/specs) | Fabrikantbron |

De gebruiker bevestigt dat de gemonteerde encoders de 90°/side-entry aansluiting hebben. Pololu beschrijft deze uitvoering als een 6-pins JST SH side-entry connector, item 4761. De encoder werkt op 2,7–18 V en heeft 12 CPR op de motoras bij x4-decodering (beide flanken van beide kanalen). De Nano-firmware telt alleen beide flanken van kanaal A en gebruikt kanaal B voor de richting (x2), dus de effectieve softwaretelling is 6 pulsen per motorasomwenteling. Met de 15,25:1-overbrenging geeft dat 91,5 pulsen per wielomwenteling; dit komt overeen met de eerder gemeten 91,3 en 91,6. De encoderkit vereist een Micro Metal Gearmotor met verlengde achteras. Voor de 15:1 HPCB 12V-motor is Pololu item 4789 de encoder-compatibele variant; item 4788 is de standaarduitvoering zonder verlengde achteras.

De 6-pins JST SH-signalen volgens de Pololu-familieschema's zijn:
- Pin 1: GND
- Pin 2: encoderkanaal B
- Pin 3: encoderkanaal A
- Pin 4: VCC (2,7–18 V)
- Pin 5: motoraansluiting M2
- Pin 6: motoraansluiting M1

Controleer de nummering aan de connectorzijde van de concrete kabel/print voordat er opnieuw wordt bedraad. De encoderboards zijn fysiek getest op de robot; de gemeten pulsen staan in [TEST_RESULTS.md](../TEST_RESULTS.md).

**Opmerking over de oudere TLE4946-2K-PDF:** dit bestand is behouden als component-/historische documentatie voor de oudere encoderkitvariant. De Pololu 4760/4761 side-entry/top-entry connectorfamilie verwijst in de huidige fabrikantdocumentatie naar de TI DRV5013 Hall-sensor. Gebruik voor de door de gebruiker bevestigde side-entry kit de DRV5013-datasheet als primaire componentreferentie.

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
| Pololu motor | Micro Metal Gearmotor-familie-PDF aanwezig | Product #4789 gelinkt als extended-shaft referentie voor encodercompatibiliteit |
| Pololu encoder | Encoderpinout PDF aanwezig; TLE4946 PDF behouden als oudere componentdocumentatie | Side-entry kit #4761 en de TI DRV5013-datasheet gelinkt als actuele referentie |

**Belangrijk:** de Microchip ATmega328P- en TI DRV8833-chipdatasheets zijn in deze repository als officiële externe PDF-links opgenomen, niet als lokale PDF-kopieën. Ik kon de binaire fabrikant-PDF's in deze omgeving niet betrouwbaar downloaden en daarom niet als bestanden in GitHub plaatsen. De lokale Nano-/ESP32-pinoutbestanden, encoderpinout, motorfamilie-PDF en laderhandleiding zijn wel aanwezig. Een chipdatasheet vervangt nooit de pinout van een specifieke breakout-module.

## Bronnen en versiebeheer

De fabrikantlinks verwijzen naar de oorspronkelijke documentatie van Microchip, Espressif, Texas Instruments en Pololu. Controleer bij wijzigingen aan de hardware altijd de revisie van de datasheet en de exacte componentvariant.
