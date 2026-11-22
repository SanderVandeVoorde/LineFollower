# Sensoren proof of concept

Doel: aantonen dat de acht uitgangen van de HY-S301 afzonderlijk kunnen worden uitgelezen met de analoge ingangen van de Arduino Nano. De POC voert bewust geen calibratie, normalisatie of interpolatie uit.

**Broncode:** [Sensor_Readout_POC.ino](./Sensor_Readout_POC.ino)

## Aansluitingen volgens de bevestigde fysieke bedrading

| HY-S301 | Arduino Nano |
|---|---:|
| D1 (links) | A0 |
| D2 | A1 |
| D3 | A2 |
| D4 | A3 |
| D5 | A4 |
| D6 | A5 |
| D7 | A6 |
| D8 (rechts) | A7 |
| VCC | 5 V volgens gebruikte module |
| GND | GND |
| IR / LED-enable | Volgens markering en schakeling van de gebruikte module |

De sensor-POC leest A0 tot A7 uit en print de waarden als D1 tot D8. Zo wordt de fysieke volgorde van links naar rechts aangehouden.

**Let op:** blad 3 van de huidige EPLAN-PDF toont nog de omgekeerde analoge koppeling (D8→A0 ... D1→A7). Dat is een fout in de tekening, niet de bevestigde fysieke mapping. Het EPLAN-bronproject moet op dit punt worden aangepast en opnieuw geëxporteerd.

## Testprocedure

1. Plaats de sensor boven de witte ondergrond.
2. Upload Sensor_Readout_POC.ino.
3. Open de seriële monitor op 115200 baud.
4. Noteer de acht waarden.
5. Plaats achtereenvolgens een zwart oppervlak onder elke sensor en controleer of alleen het overeenkomstige kanaal duidelijk verandert.
6. Controleer dat D1 links en D8 rechts wordt weergegeven.
7. Herhaal op de witte ondergrond en noteer de meetwaarden.

## Eerder genoteerde meetwaarden

| Kanaal | Zwart | Wit |
|---|---:|---:|
| D1 | 970 | 888 |
| D2 | 952 | 863 |
| D3 | 939 | 869 |
| D4 | 937 | 890 |
| D5 | 935 | 903 |
| D6 | 950 | 932 |
| D7 | 939 | 925 |
| D8 | 964 | 961 |

Dit is een oudere POC-meting. De latere en definitieve calibratieset staat in [TEST_RESULTS.md](../../../TEST_RESULTS.md) en wordt in de finale Nano-firmware gebruikt. De acht sensoren zijn later opnieuw fysiek op wit en zwart gemeten; alle acht werden als bruikbaar bevestigd. Vooral D8 had in deze oudere meting weinig verschil tussen zwart en wit.

## Aandachtspunten

- Fysieke volgorde: D1 links en D8 rechts.
- Bevestigde fysieke mapping: D1→A0, D2→A1, ... D8→A7.
- De finale Nano-firmware en deze POC lezen de analoge pinnen in oplopende volgorde A0→A7.
- Blad 3 van de huidige EPLAN-PDF is op dit punt verouderd/fout en moet worden gecorrigeerd.
- A6 en A7 zijn op de klassieke Nano uitsluitend analoge ingangen; gebruik ze niet als digitale pinnen.
- De eerder uitgevoerde fysieke metingen gelden als bewijs voor de huidige sensorarray en bedrading. Herhaal de POC alleen wanneer de sensorarray, bedrading of pinmapping verandert.
