# H-brug proof of concept

Doel: aantonen dat twee DC-motoren onafhankelijk kunnen draaien, van draairichting kunnen veranderen en met afzonderlijke PWM-waarden kunnen worden geregeld.

**Broncode:** [HBridge_POC.ino](./HBridge_POC.ino)

**Afzonderlijk POC-deelschema:** [HBridge_POC_Schema.svg](./HBridge_POC_Schema.svg)

Het SVG-schema toont de functionele signaal-, voedings- en massaverbindingen tussen Nano, DRV8833 en beide motoren. Het is geen connectorlayout van een specifieke breakoutmodule; controleer SLEEP/nSLEEP en de fysieke connectorposities met de modulemarkeringen en het actuele EPLAN-blad.

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
7. Test beide motoren onafhankelijk met M,80,0 en daarna M,0,80. Test ook een negatieve waarde, bijvoorbeeld M,-80,0.
8. Verstuur + of - om de standaard test-PWM aan te passen.
9. Verstuur S om onmiddellijk te stoppen.

## Commando's

| Teken | Actie |
|---|---|
| F | Beide motoren vooruit |
| B | Beide motoren achteruit |
| L | Links draaien |
| R | Rechts draaien |
| S | Stop |
| + | PWM met 10 verhogen |
| - | Standaard test-PWM met 10 verlagen |
| M,<links>,<rechts> | Onafhankelijke PWM instellen, bereik -160 tot +160; voorbeeld M,80,0 |

De linkermotor wordt softwarematig geïnverteerd, overeenkomstig de huidige finale Nano-code.

## Aandachtspunten

- De slaap-/enable-aansluitingen van de gebruikte DRV8833-module volgen de EPLAN-tekening. Neem geen pinvolgorde van een andere DRV8833-breakout over.
- Verbind de Nano-GND, DRV8833-GND en batterij-GND.
- Gebruik de batterijspanning die voor de robot is voorzien; sluit geen 12V-bron aan op basis van alleen de motorvermelding.
- De code is een testprogramma en geen motorregeling voor autonoom rijden.
- De motoren, hun draairichtingen en de H-brugwerking zijn fysiek getest; de gebruiker bevestigt op 22-11-2026 dat de motorsturing werkt. Zie [TEST_RESULTS.md](../../../TEST_RESULTS.md). De POC-sketch is afzonderlijk opgenomen als reproduceerbaar testprogramma en compileert succesvol. De finale robot gebruikt daarnaast de geïntegreerde Nano-firmware.
