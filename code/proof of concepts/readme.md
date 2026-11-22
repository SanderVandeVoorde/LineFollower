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

## Testresultaten en bewijsstatus

De eerdere fysieke tests van de robot zijn samengebracht in [TEST_RESULTS.md](../../TEST_RESULTS.md). Daarin staan onder meer de acht HY-S301-wit-/zwartmetingen, de twee motoren en hun draairichting, de fysieke startknop en status-led, de encoderproeven en de drie-ronde-baseline. Deze resultaten mogen als bestaande hardwarevalidatie worden gebruikt.

Maak wel onderscheid tussen een functie die op de robot fysiek getest is en het afzonderlijk uitvoeren van exact de POC-sketch uit deze map. De repository-build bewijst alleen dat de POC-code compileert. De wireless POC en de D2-interrupt-POC hebben nog geen teruggevonden afzonderlijk fysiek testresultaat. De finale robotknop op D8 is wel fysiek getest; dat bewijst niet automatisch de aparte D2-interruptdemonstratie.

De POC-aansluitingen zijn niet altijd identiek aan de finale robot. De interrupt-POC gebruikt bijvoorbeeld D2, terwijl de finale startknop op D8 is aangesloten.
