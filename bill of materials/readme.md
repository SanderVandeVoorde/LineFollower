## Bill of Materials (BOM) – LineFollower V2

Deze lijst beschrijft de onderdelen en de geregistreerde kostprijs van de huidige robotconfiguratie. Bedragen zijn de in het project genoteerde aankoop- of vervangingswaarden.

### 1) Elektrische onderdelen

| Volgnummer | Naam | Omschrijving | Nieuw/recup | Kostprijs/stuk | Aantal | Subtotaal |
|---:|---|---|---|---:|---:|---:|
| 1 | Arduino Nano | ATmega328P, 5 V | Recup | €3,33 | 1 | €3,33 |
| 2 | ESP32-C3 Super Mini | Draadloze communicatie via Wi-Fi | Recup | €6,33 | 1 | €6,33 |
| 3 | HY-S301 | 8-kanaals analoge IR-sensorarray | Nieuw | €3,99 | 1 | €3,99 |
| 4 | LED | Witte LED als power-on-indicator | Recup | €0,05 | 1 | €0,05 |
| 5 | Weerstand | 330 Ω, stroombegrenzing status-LED | Recup | €0,05 | 1 | €0,05 |
| 6 | Drukknop | Momentane drukknop, normaal open | Recup | €0,10 | 1 | €0,10 |
| 7 | Schakelaar | Hoofdschakelaar batterijvoeding | Recup | €0,05 | 1 | €0,05 |
| 8 | Schakelaar | UART-onderbreking voor programmeren | Recup | €0,05 | 2 | €0,10 |
| 9 | Buckconverter | S09 V8.0, vaste 5 V-uitgang | Nieuw | €4,09 | 1 | €4,09 |
| 10 | LiPo-batterij | Tattu 2S, 7,4 V, 550 mAh, 95C | Nieuw | €16,00 | 1 | €16,00 |
| 11 | Elektrolytische condensator | 100 µF, 16 V, buffering 5V-voeding | Recup | €0,05 | 1 | €0,05 |
| 12 | Weerstanden | 100 kΩ + 47 kΩ in serie: bovenste tak 147 kΩ van de batterijspanningsdeler | Recup | €0,05 (geschatte vervangingswaarde) | 2 | €0,10 |
| 13 | Weerstand | 47 kΩ, onderste tak batterijspanningsdeler | Recup | €0,05 | 1 | €0,05 |
| 14 | Keramische condensator | 100 nF, batterijspanningsmeting en motorontstoring | Recup | €0,05 | 3 | €0,15 |
| 15 | Weerstand | 10 kΩ, UART-spanningsdeler | Recup | €0,05 | 1 | €0,05 |
| 16 | Weerstand | 20 kΩ, UART-spanningsdeler | Recup | €0,05 | 1 | €0,05 |
| 17 | H-brug | DRV8833, dubbele DC-motorcontroller | Nieuw | €1,18 | 1 | €1,18 |
| 18 | Elektrolytische condensator | 470 µF, minimaal 16 V, buffering motorvoeding | Recup | €0,30 | 1 | €0,30 |
| 19 | Encoder | Pololu magnetische encoder, 12 CPR, side-entry (90°) JST SH, referentie item 4761 | Nieuw | €3,25 | 2 | €6,50 |
| 20 | Motor | Pololu 15,25:1 Micro Metal Gearmotor HPCB 12 V, encoder-compatibele verlengde achteras (referentie item 4789; exact aankoop-SKU niet bevestigd) | Nieuw | €38,15 | 2 | €76,30 |
| 21 | XT30-connector | Aansluiting voor batterij | Recup | €0,90 | 1 | €0,90 |
| 22 | LiPo-lader | BC-4S15D balanslader | Recup | €19,99 | 1 | €19,99 |
| 23 | Experimenteerplaat | Groene soldeerplaat 50 × 70 mm | Recup | €1,00 | 1 | €1,00 |

### 2) Mechanische onderdelen en montage

| Volgnummer | Naam | Omschrijving | Nieuw/recup | Kostprijs/stuk | Aantal | Subtotaal |
|---:|---|---|---|---:|---:|---:|
| 24 | Wiel | Pololu, Ø40 × 7 mm | Nieuw | €4,60 | 2 | €9,20 |
| 25 | Bevestigingsmateriaal | Schroeven en moeren | Recup | / | Diverse | €2,00 |
| 26 | Bekabeling | Voedings- en signaaldraden | Recup | / | Diverse | €1,00 |
| 27 | Connectoren | JST- en overige aansluitconnectoren | Recup | / | Diverse | €1,50 |
| 28 | Chassis | Zelf ontworpen en 3D-geprint PLA-chassis | / | / | 1 | €2,50 |
| 29 | Motorbevestiging | Zelf ontworpen en 3D-geprinte bevestiging voor N20-motoren | / | / | 2 | €1,00 |
| 30 | Ball caster | Pololu 3/4-inch plastic ball caster; besteld via OpenCircuit, montage op finale robot nog te bevestigen | Nieuw | Aankoopprijs niet teruggevonden | 1 | Niet opgenomen in totaal |

### 3) Kostenoverzicht

De kostprijs is opnieuw berekend op basis van alle regels in deze BOM. De twee weerstanden van de werkelijke bovenste batterijtak (100 kΩ + 47 kΩ in serie) zijn geraamd op €0,05 per stuk. De som van de afzonderlijke regels is €157,91: €117,26 nieuw + €37,15 recup + €3,50 3D-print. De twee weerstanden van de bovenste 147 kΩ-tak zijn beide meegeteld aan €0,05 per stuk. De recupweerstanden zijn gewaardeerd aan dezelfde vervangingsprijs als de andere losse weerstanden; dit is geen oorspronkelijke aankoopfactuur.

| Categorie | Laatst geregistreerd bedrag |
|---|---:|
| Totaal nieuw | €117,26 |
| Totaal recup | €37,15 |
| Totaal 3D-print | €3,50 |
| **Bekende projectkost inclusief lader** | **€157,91 + prijs ball caster** |
| **Bekende robotkost exclusief lader** | **€137,92 + prijs ball caster** |

### 4) Herkomst en aankoopbronnen

De BOM bevat de geregistreerde aankoop-/vervangingswaarden, maar niet voor elk onderdeel is de oorspronkelijke winkel of bestelbon nog beschikbaar. De Pololu 3/4-inch ball caster is besteld via OpenCircuit; de officiële productreferentie is [Pololu #954](https://www.pololu.com/product/954), maar de concrete aankoopprijs en bevestiging van montage ontbreken. Om geen aankoopgegevens te verzinnen, geldt onderstaande herkomststatus:

| Onderdeelgroep | Herkomst / bronstatus |
|---|---|
| Arduino Nano, ESP32-C3 Super Mini, LED, weerstanden, knop, schakelaars, condensatoren, connectoren en bekabeling met label recup | Gerecupereerd uit bestaande voorraad; oorspronkelijke aankoopbron niet geregistreerd |
| HY-S301 | [TinyTronics productinformatie](https://www.tinytronics.nl/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module); geen officiële fabrikantdatasheet gevonden |
| DRV8833 | [Texas Instruments-chipdatasheet](https://www.ti.com/lit/ds/symlink/drv8833.pdf); exacte breakoutwinkel/-SKU niet teruggevonden |
| Pololu 15,25:1 HPCB 12 V motor | [Pololu #4789 productreferentie](https://www.pololu.com/product/4789/specs) voor encoder-compatibele verlengde achteras; exacte aankoop-SKU niet bevestigd |
| Pololu side-entry encoder | [Pololu #4761 productreferentie](https://www.pololu.com/product/4761/specs); overeenkomstig de door de gebruiker bevestigde 90°-connector |
| Tattu 2S LiPo, S09 V8.0 buckconverter, BC-4S15D-lader, wielen, soldeerplaat en printmateriaal | Product-/aankoopbron niet met zekerheid uit de bewaarde aankoopgegevens teruggevonden; lokale handleidingen/specs waar aanwezig staan in `datasheets/` |
| Pololu 3/4-inch ball caster | Besteld via OpenCircuit; [Pololu #954 fabrikantreferentie](https://www.pololu.com/product/954); aankoopprijs en montage nog te bevestigen |

Vul de ontbrekende leveranciersinformatie aan met de oorspronkelijke bestelbevestiging of factuur wanneer die nog beschikbaar is. De hierboven vermelde fabrikant-/leverancierslinks zijn technische productreferenties en bewijzen niet noodzakelijk waar de concrete exemplaren gekocht zijn.

### 5) Belangrijke compatibiliteitscontroles

- De gemonteerde encoder heeft de door de gebruiker bevestigde 90°/side-entry JST SH-aansluiting; de overeenkomstige Pololu-referentie is encoderkit #4761.
- De encoderkit vereist een motor met verlengde achteras. Voor de 15:1 HPCB 12V-uitvoering is Pololu #4789 de encoder-compatibele referentie; het exacte bestelnummer van de gemonteerde motor is niet uit de aankoopgegevens bevestigd. De fysieke encoderwerking is wel eerder getest.
- De robot wordt gevoed met een 2S LiPo (7,4 V nominaal, 8,4 V maximaal); de 12V-motorspecificaties zijn dus niet rechtstreeks de werkelijke bedrijfsspanning.
- Controleer in de handleiding van de BC-4S15D dat de gekozen laadmodus geschikt is voor een 2S LiPo.
- Werkelijke batterijspanningsdeler: 147 kΩ boven (100 kΩ + 47 kΩ in serie), 47 kΩ onder.
