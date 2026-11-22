# EPLAN-revisienotities – LineFollower V2

Deze notities leggen de nog uit te voeren administratieve correctie in het EPLAN-bronproject vast. De bestaande elektrische topologie en aansluitingen zijn door de gebruiker bevestigd als correct.

## Revisie 1 – batterijspanningsdeler (blad 3)

De gemonteerde hardware wijkt in componentwaarde af van de huidige tekst op het schema:

| Positie | Huidige PDF | Werkelijke hardware |
|---|---:|---:|
| Bovenste tak | 150 kΩ | 100 kΩ + 47 kΩ in serie = 147 kΩ |
| Onderste tak | 47 kΩ | 47 kΩ |
| Filtercondensator | 100 nF | 100 nF |
| ESP32 ADC | GPIO0 | GPIO0 |

### Aanpassing in EPLAN

1. Open de bestaande EPLAN-projectbackup `Linefollower_EPLAN_SVDV.zw1`.
2. Ga naar blad 3, **Besturing, sensoren & communicatie**.
3. Vervang de bovenste weerstand van de batterijspanningsdeler door twee afzonderlijke serieweerstanden: 100 kΩ en 47 kΩ.
4. Behoud de onderste weerstand van 47 kΩ en de 100 nF-condensator naar GND.
5. Behoud het meetpunt naar ESP32-C3 GPIO0.
6. Controleer de verbindingen en componentreferenties.
7. Exporteer het volledige schema opnieuw naar PDF en vervang het verouderde PDF-bestand in deze map.

De equivalente bovenste weerstand is 147 kΩ. De ESP32-firmware gebruikt daarom:

`BATTERY_FACTOR = (147 + 47) / 47 = 194 / 47`

Bij een batterijspanning van 8,4 V is de theoretische ADC-spanning ongeveer 2,04 V.

## Bevestigde overige schema-informatie

- DRV8833 is de gebruikte motordriver; de gebruiker bevestigt dat blad 4 de juiste aansluitingen weergeeft.
- Sensorbedrading volgt blad 3: D8→A0, D7→A1, ..., D1→A7.
- De Nano-firmware leest A7→A0 zodat de softwarekanalen D1→D8 links-naar-rechts geordend zijn.
- Nano en ESP32-C3 communiceren via UART op 115200 baud.
- Nano-TX naar ESP32-RX gebruikt de 10 kΩ/20 kΩ spanningsdeler.
- De batterijmeting gebruikt de 147 kΩ/47 kΩ spanningsdeler en 100 nF-filtercondensator.

## Revisiestatus

- [x] Werkelijke weerstandswaarden bevestigd door gebruiker.
- [x] ESP32-firmwarefactor aangepast op 147 kΩ + 47 kΩ.
- [x] BOM en projectdocumentatie bijgewerkt.
- [ ] EPLAN-bronproject aanpassen.
- [ ] Nieuwe PDF exporteren en uploaden.
- [ ] Nieuwe PDF visueel vergelijken met de bestaande vier bladen.
