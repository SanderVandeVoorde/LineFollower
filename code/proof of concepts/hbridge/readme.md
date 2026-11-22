# H-brug proof of concept

Doel: aantonen dat twee DC-motoren onafhankelijk kunnen draaien, van draairichting kunnen veranderen en met PWM in snelheid kunnen worden geregeld.

**Broncode:** [HBridge_POC.ino](./HBridge_POC.ino)

## Aansluitingen

| Functie | Arduino Nano |
|---|---:|
| Linkermotor IN1 | D11 |
| Linkermotor IN2 | D10 |
| Rechtermotor IN1 | D6 |
| Rechtermotor IN2 | D5 |
| DRV8833 VM/VMM | Motorvoeding |
| DRV8833 GND | Gemeenschappelijke GND |

De gebruikte module is de DRV8833. De moduleaansluitingen en de verbindingen naar de motoren zijn vastgelegd op blad 4 van het EPLAN-schema. Gebruik voor deze robot dat schema als referentie.

## Testprocedure

1. Zet de robot op een steun zodat beide aangedreven wielen vrij kunnen draaien.
2. Controleer met een multimeter op kortsluiting tussen voedingsplus en GND.
3. Controleer de polariteit van de batterij en motorvoeding.
4. Upload HBridge_POC.ino en open de seriële monitor op 115200 baud.
5. Begin met de lage standaard-PWM van 80.
6. Verstuur F, B, L en R afzonderlijk. Elke beweging stopt automatisch na één seconde.
7. Verstuur + of - om de PWM-stapwaarde aan te passen.
8. Verstuur S om onmiddellijk te stoppen.

## Commando's

| Teken | Actie |
|---|---|
| F | Beide motoren vooruit |
| B | Beide motoren achteruit |
| L | Links draaien |
| R | Rechts draaien |
| S | Stop |
| + | PWM met 10 verhogen |
| - | PWM met 10 verlagen |

De linkermotor wordt softwarematig geïnverteerd, overeenkomstig de huidige finale Nano-code.

## Aandachtspunten

- De slaap-/enable-aansluitingen van de gebruikte DRV8833-module volgen de EPLAN-tekening. Neem geen pinvolgorde van een andere DRV8833-breakout over.
- Verbind de Nano-GND, DRV8833-GND en batterij-GND.
- Gebruik de batterijspanning die voor de robot is voorzien; sluit geen 12V-bron aan op basis van alleen de motorvermelding.
- De code is een testprogramma en geen motorregeling voor autonoom rijden.
- De motoren, hun draairichtingen en de H-brugwerking zijn fysiek getest; de gebruiker bevestigt op 22-11-2026 dat de motorsturing werkt. Zie [TEST_RESULTS.md](../../../TEST_RESULTS.md). De POC-sketch is afzonderlijk opgenomen als reproduceerbaar testprogramma en compileert succesvol. De finale robot gebruikt daarnaast de geïntegreerde Nano-firmware.
