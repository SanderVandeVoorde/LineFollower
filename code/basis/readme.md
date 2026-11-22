# Basisprogramma – Arduino Nano

Het basisprogramma is een zelfstandig oefenprogramma voor de Arduino Nano. Het toont de algemene softwarestructuur die vóór de finale linefollowercode kan worden getest.

**Broncode:** [Basis_Programma.ino](./Basis_Programma.ino)

**EEPROM-blokschema:** [EEPROM_POC_Schema.svg](./EEPROM_POC_Schema.svg)

## Aangetoonde functies

- Instelbare cyclustijd via de seriële poort.
- Debugmeldingen aan- en uitschakelen.
- Starten en stoppen via seriële commando's.
- Start/stop via een hardware-interrupt op D2 (INT0).
- Instellingen bewaren en teruglezen uit de interne EEPROM.
- Een status-led op D13 laten knipperen zolang het programma actief is.

## Aansluitingen

| Functie | Arduino Nano |
|---|---:|
| Status-led | D13 (onboard LED) |
| Start/stopknop | D2 naar GND |
| Seriële communicatie | USB / UART D0-D1 |

De knop gebruikt INPUT_PULLUP. De interrupt wordt geactiveerd op de dalende flank wanneer de knop wordt ingedrukt.

## Seriële instellingen

- Baudrate: 115200
- Lijnafsluiting: newline

| Commando | Functie |
|---|---|
| START | Start de cyclische werking |
| STOP | Stopt de cyclische werking |
| CYCLE,500 | Stel de cyclus in op 500 ms (50–5000 ms) |
| DEBUG,1 | Debugmeldingen inschakelen |
| DEBUG,0 | Debugmeldingen uitschakelen |
| SAVE | Bewaar instellingen in EEPROM |
| STATUS | Vraag status en instellingen op |

De standaardcyclustijd is 500 ms. De standaard debugstatus is ingeschakeld. Een wijziging aan CYCLE of DEBUG wordt pas blijvend na SAVE. De instellingen worden met een magicwaarde en bereikcontrole uit EEPROM geladen.

## Testprocedure

1. Upload Basis_Programma.ino naar de Nano.
2. Open de seriële monitor op 115200 baud en kies newline.
3. Verstuur STATUS en controleer het antwoord.
4. Verstuur CYCLE,250 en controleer de snellere LED-cyclus.
5. Verstuur DEBUG,0 en controleer dat de periodieke debugmelding stopt.
6. Verstuur SAVE, reset de Nano en controleer met STATUS of de instellingen bewaard zijn. Noteer de ontvangen waarden in TEST_RESULTS.md; deze test moet fysiek worden uitgevoerd.
7. Druk op de knop tussen D2 en GND en controleer dat de werking start of stopt.

**Let op:** dit programma gebruikt D2 voor de interruptknop. De finale linefollowerfirmware gebruikt de fysieke startknop op D8 en leest die knop via polling. Verwissel die aansluitingen niet.
