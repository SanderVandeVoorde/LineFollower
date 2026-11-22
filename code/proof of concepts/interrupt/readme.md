# Start/stop interrupt proof of concept

Doel: aantonen dat een drukknop een hardware-interrupt kan activeren en daarmee een start/stopstatus kan omschakelen.

**Broncode:** [StartStop_Interrupt_POC.ino](./StartStop_Interrupt_POC.ino)

## Aansluiting

| Functie | Arduino Nano |
|---|---:|
| Drukknop contact 1 | D2 (INT0) |
| Drukknop contact 2 | GND |
| Status-led | D13 |

De ingang gebruikt INPUT_PULLUP. De knop is normaal open en verbindt D2 met GND wanneer hij wordt ingedrukt.

## Werking

- De dalende flank op D2 activeert de interrupt.
- De interrupt-service routine zet alleen een vlag.
- De hoofdloop verwerkt de vlag, past softwarematige debounce toe en schakelt de status om.
- D13 brandt wanneer de status actief is.

## Testprocedure

1. Upload StartStop_Interrupt_POC.ino.
2. Open de seriële monitor op 115200 baud.
3. Druk kort op de knop.
4. Controleer afwisselend STATE,START en STATE,STOP.
5. Controleer dat één druk niet meerdere omschakelingen veroorzaakt.

## Verschil met de finale robot

De finale Nano-firmware gebruikt de fysieke start/stopknop op D8 en leest die periodiek uit met debounce; die knop is fysiek getest. Deze POC gebruikt D2 om de hardware-interruptfunctie afzonderlijk te demonstreren. De repository bevat de sketch en de build compileert, maar er is geen afzonderlijk fysiek testresultaat voor de D2-interruptdemonstratie teruggevonden. De POC-aansluiting mag dus niet zonder wijziging naar de finale robot worden overgenomen.
