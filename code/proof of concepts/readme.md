# Proof of Concepts

Een proof of concept (POC) is een minimale combinatie van hardware, software en een testprocedure waarmee één functie afzonderlijk wordt aangetoond. De POC's kunnen ook worden gebruikt om storingen te isoleren zonder de volledige robotsoftware te moeten debuggen.

## Overzicht

| POC | Doel | Broncode |
|---|---|---|
| H-brug | Twee motoren onafhankelijk aansturen, richting omkeren en PWM regelen | [HBridge_POC.ino](./hbridge/HBridge_POC.ino) |
| Sensoren | Acht analoge HY-S301-kanalen afzonderlijk uitlezen | [Sensor_Readout_POC.ino](./sensor/Sensor_Readout_POC.ino) |
| Interrupt | Start/stopknop via hardware-interrupt demonstreren | [StartStop_Interrupt_POC.ino](./interrupt/StartStop_Interrupt_POC.ino) |
| Draadloze communicatie | Browser ↔ ESP32-C3 ↔ UART ↔ Nano | [ESP32_WiFi_UART_POC.ino](./wireless%20communication/ESP32_WiFi_UART_POC.ino) |

## Wat hoort bij een POC?

- Een elektrisch aansluitschema of duidelijke verbindingstabel.
- Minimale broncode die één functie aantoont.
- Een korte testprocedure.
- Een resultaat dat na uitvoering wordt ingevuld.

## Testresultaten

De broncode en testprocedures zijn opgenomen. De hardwaretests moeten nog met de concrete robot worden uitgevoerd en afgevinkt in PROJECT_STATUS.md. Voeg geen resultaat toe voordat de test effectief is uitgevoerd.

De POC-aansluitingen zijn niet altijd identiek aan de finale robot. De interrupt-POC gebruikt bijvoorbeeld D2, terwijl de finale startknop op D8 is aangesloten.
