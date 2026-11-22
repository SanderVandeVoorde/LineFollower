# Proof of Concepts

Een proof of concept (POC) is een minimale combinatie van hardware, software en een testprocedure waarmee één functie afzonderlijk wordt aangetoond. De POC's kunnen ook worden gebruikt om storingen te isoleren zonder de volledige robotsoftware te moeten debuggen.

## Overzicht

| POC | Doel | Broncode |
|---|---|---|
| H-brug | Twee motoren onafhankelijk aansturen, richting omkeren en PWM regelen | [HBridge_POC.ino](./hbridge/HBridge_POC.ino) |
| Sensoren | Acht analoge HY-S301-kanalen afzonderlijk uitlezen | [Sensor_Readout_POC.ino](./sensor/Sensor_Readout_POC.ino) |
| Interrupt | Start/stopknop via hardware-interrupt demonstreren | [Code](./interrupt/StartStop_Interrupt_POC.ino) · [schema](./interrupt/Interrupt_POC_Schema.svg) |
| Draadloze communicatie | Browser ↔ ESP32-C3 ↔ UART ↔ Nano | [Code](./wireless%20communication/ESP32_WiFi_UART_POC.ino) · [schema](./wireless%20communication/Wireless_POC_Schema.svg) |
| EEPROM | Nano-instellingen bewaren en na reset teruglezen | [Basisprogramma](../basis/Basis_Programma.ino) · [schema](../basis/EEPROM_POC_Schema.svg) |

## Wat hoort bij een POC?

- Een elektrisch aansluitschema of duidelijke verbindingstabel.
- Minimale broncode die één functie aantoont.
- Een korte testprocedure.
- Een resultaat dat na uitvoering wordt ingevuld.

## Testresultaten en bewijsstatus

De fysieke testresultaten staan in [TEST_RESULTS.md](../../TEST_RESULTS.md). De gebruiker bevestigde op 22-11-2026 dat de toenmalige geïntegreerde robotfuncties werkten, waaronder motorsturing, draadloze browserbediening, Nano–ESP32-UART en de finale start/stop. Dat betekent niet automatisch dat elke afzonderlijke POC-sketch fysiek is uitgevoerd. De nieuwe onafhankelijke PWM-commando's van de H-brug-POC, de D2-interrupt-POC, de EEPROM SAVE/reset-test en de nieuwe secrets-configuratie moeten afzonderlijk worden getest en geregistreerd.

De POC-sketches blijven afzonderlijke demonstratieprogramma's en kunnen andere pinnen gebruiken dan de finale robot. De interrupt-POC gebruikt bijvoorbeeld D2, terwijl de finale startknop op D8 is aangesloten. Die pinverschillen veranderen niets aan de bevestigde fysieke werking van de finale robot.
