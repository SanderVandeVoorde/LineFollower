# Sensoren proof of concept

Doel: aantonen dat de acht uitgangen van de HY-S301 afzonderlijk kunnen worden uitgelezen met de analoge ingangen van de Arduino Nano. De POC voert bewust geen calibratie, normalisatie of interpolatie uit.

**Broncode:** [Sensor_Readout_POC.ino](./Sensor_Readout_POC.ino)

## Aansluitingen

| HY-S301 | Arduino Nano |
|---|---:|
| D1 (fysiek links) | A0 |
| D2 | A1 |
| D3 | A2 |
| D4 | A3 |
| D5 | A4 |
| D6 | A5 |
| D7 | A6 |
| D8 (fysiek rechts) | A7 |
| VCC | 5 V volgens gebruikte module |
| GND | GND |
| IR / LED-enable | Volgens de markering en schakeling van de gebruikte module |

Controleer de voedingsspanning van de concrete sensorprint. De acht sensorkanalen moeten binnen het toegestane ADC-bereik van de Nano blijven.

## Testprocedure

1. Plaats de sensor boven de witte ondergrond.
2. Upload Sensor_Readout_POC.ino.
3. Open de seriële monitor op 115200 baud.
4. Noteer de acht waarden.
5. Plaats achtereenvolgens een zwart oppervlak onder elke sensor en controleer of alleen het overeenkomstige kanaal duidelijk verandert.
6. Herhaal op de witte ondergrond en noteer de meetwaarden.

## Bekende meetwaarden uit eerdere metingen

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

Dit zijn eerder genoteerde meetwaarden, geen gegarandeerde actuele waarden. Vooral D8 reageerde in die meting weinig op het verschil tussen zwart en wit. Controleer sensorhoogte, uitlijning, IR-enable en bedrading als dat probleem terugkomt.

## Aandachtspunten

- Fysieke volgorde: D1 links en D8 rechts.
- De finale software verwacht A0 = D1 links en A7 = D8 rechts.
- A6 en A7 zijn op de klassieke Nano uitsluitend analoge ingangen; gebruik ze niet als digitale I/O.
- Deze POC toont alleen ruwe ADC-waarden. De calibratie in de finale firmware staat apart gedocumenteerd.
