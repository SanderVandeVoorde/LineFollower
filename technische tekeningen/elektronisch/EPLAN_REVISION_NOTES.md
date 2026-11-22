# EPLAN- en hardwareweerstanden – LineFollower V2

De gebruiker heeft bevestigd dat het EPLAN-schema op 150 kΩ mag blijven staan. Dit is de nominale ontwerpwaarde voor de bovenste weerstand van de batterijspanningsdeler. De gemonteerde robot gebruikt de weerstanden die beschikbaar waren: 100 kΩ + 47 kΩ in serie, samen 147 kΩ. Dit verschil is bewust gedocumenteerd; het is geen openstaande EPLAN-fout.

## Batterijspanningsdeler (blad 3)

| Positie | EPLAN / nominale ontwerpwaarde | Werkelijke hardware |
|---|---:|---:|
| Bovenste tak | 150 kΩ | 100 kΩ + 47 kΩ in serie = 147 kΩ |
| Onderste tak | 47 kΩ | 47 kΩ |
| Filtercondensator | 100 nF | 100 nF |
| ESP32 ADC | GPIO0 | GPIO0 |

De ESP32-firmware moet rekenen met de werkelijke gemonteerde waarde van 147 kΩ:

`BATTERY_FACTOR = (147 + 47) / 47 = 194 / 47`

Bij 8,4 V batterijspanning is de theoretische ADC-spanning met de gemonteerde deler ongeveer 2,04 V. De nominale EPLAN-deler van 150 kΩ zou ongeveer 2,00 V geven. EPLAN blijft ongewijzigd op 150 kΩ, zoals de gebruiker vraagt.

## Bevestigde overige schema-informatie

- DRV8833 is de gebruikte motordriver; de gebruiker bevestigt dat blad 4 de juiste aansluitingen weergeeft.
- Sensorbedrading volgt blad 3: D8→A0, D7→A1, ..., D1→A7.
- De Nano-firmware leest A7→A0 zodat de softwarekanalen D1→D8 links-naar-rechts geordend zijn.
- Nano en ESP32-C3 communiceren via UART op 115200 baud.
- Nano-TX naar ESP32-RX gebruikt de 10 kΩ/20 kΩ spanningsdeler.
- De batterijmeting gebruikt de 147 kΩ/47 kΩ spanningsdeler en 100 nF-filtercondensator.

## Status

- [x] EPLAN 150 kΩ blijft behouden als nominale ontwerpwaarde.
- [x] Werkelijke hardwarewaarde van 147 kΩ is vastgelegd.
- [x] ESP32-firmwarefactor is aangepast aan 147 kΩ + 47 kΩ.
- [x] BOM en projectdocumentatie vermelden beide waarden.
- [x] Geen EPLAN-bron- of PDF-aanpassing nodig.
