# Sensoren proof of concept

Doel: aantonen dat de acht uitgangen van de HY-S301 afzonderlijk kunnen worden uitgelezen met de analoge ingangen van de Arduino Nano. De POC voert bewust geen calibratie, normalisatie of interpolatie uit.

**Broncode:** [Sensor_Readout_POC.ino](./Sensor_Readout_POC.ino)

## Aansluitingen volgens EPLAN

| HY-S301 | Arduino Nano |
|---|---:|
| D8 | A0 |
| D7 | A1 |
| D6 | A2 |
| D5 | A3 |
| D4 | A4 |
| D3 | A5 |
| D2 | A6 |
| D1 | A7 |
| VCC | 5 V volgens gebruikte module |
| GND | GND |
| IR / LED-enable | Volgens markering en schakeling van de gebruikte module |

De sensor-POC leest A7 tot A0 uit en print de waarden als D1 tot D8. Zo wordt de fysieke volgorde van links naar rechts aangehouden.

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

Dit zijn eerder genoteerde waarden, geen gegarandeerde actuele waarden. Vooral D8 reageerde in die meting weinig op het verschil tussen zwart en wit. Controleer sensorhoogte, uitlijning, IR-enable en bedrading als dat probleem terugkomt.

## Aandachtspunten

- Fysieke volgorde: D1 links en D8 rechts.
- EPLAN: D1→A7, D2→A6, ... D8→A0.
- De finale Nano-firmware en deze POC gebruiken dezelfde omgekeerde analoge pinvolgorde.
- A6 en A7 zijn op de klassieke Nano uitsluitend analoge ingangen; gebruik ze niet als digitale pinnen.
- De POC moet na een firmware- of bedradingwijziging opnieuw op de robot worden uitgevoerd.
