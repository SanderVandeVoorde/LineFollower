# Testplan na de GitHub-software-update

**Doel:** de nieuwe firmwarefuncties veilig controleren voordat deze als fysiek bewezen in de HOGENT-documentatie worden aangeduid.

> De vorige robotfuncties zijn op 22-11-2026 door de gebruiker bevestigd. De wijzigingen hieronder zijn nadien in de broncode aangebracht en zijn nog niet fysiek gevalideerd.

## 1. Wi-Fi-configuratie

1. Kopieer `code/esp32/secrets.example.h` naar `code/esp32/secrets.h`.
2. Stel een uniek wachtwoord in van minstens acht tekens.
3. Doe hetzelfde voor de wireless POC als je die afzonderlijk gebruikt.
4. Controleer dat `secrets.h` niet verschijnt in `git status` en niet wordt gepusht.
5. Upload de ESP32-firmware en verbind met het nieuwe wachtwoord. Zonder lokaal secrets.h hoort het accesspoint niet te starten.

**Belangrijk:** de oude standaardwaarde stond in de publieke Git-geschiedenis. Beschouw die als gecompromitteerd en wijzig het wachtwoord vóór gebruik.

## 2. Power-on-led D13

1. Zet de hoofdschakelaar uit: de LED moet uit zijn.
2. Zet de hoofdschakelaar aan en wacht tot de Nano is opgestart.
3. Controleer dat D13 blijft branden, ook wanneer de robot op STOP staat.
4. Druk START en STOP; de LED moet als voedingsindicator blijven branden.
5. Schakel de hoofdvoeding uit en controleer dat de LED dooft.

Als de LED niet overeenkomt met de werkelijke voedingstoestand, controleer de aansluiting en polariteit. Verander de bedrading niet onder spanning.

## 3. EEPROM-opslag

1. Upload eerst de finale Nano-firmware en daarna de ESP32-firmware.
2. Verbind het dashboard en wijzig bijvoorbeeld Kp of basissnelheid.
3. Druk TOEPASSEN en wacht op de configuratiebevestiging.
4. Druk OPSLAAN en controleer de melding dat Nano-EEPROM en ESP32-NVS bevestigd zijn.
5. Schakel de robot volledig uit en opnieuw in.
6. Open het dashboard en controleer dat de ingestelde waarden terugkomen.
7. Controleer ook dat de Nano zonder ESP32 de laatst geldige EEPROM-configuratie laadt (test dit alleen als je UART veilig kunt onderbreken).

Noteer de gekozen waarden, de bevestiging en het resultaat na herstart in TEST_RESULTS.md.

## 4. Handmatige sensorcalibratie

1. Zet de robot stil en plaats de volledige sensorarray boven een egaal wit oppervlak.
2. Druk WIT VASTLEGGEN.
3. Wacht op de melding dat de witte waarden opgeslagen zijn.
4. Plaats de volledige sensorarray boven het zwarte lijnmateriaal.
5. Druk ZWART VASTLEGGEN.
6. Wacht op de melding dat de zwarte waarden opgeslagen zijn.
7. Schakel de robot volledig uit en opnieuw in.
8. Controleer met de debugweergave dat de ruwe waarden logisch verschillen tussen wit en zwart.
9. Voer eerst een korte test op lage snelheid uit.

De calibratiecode weigert een opname wanneer het contrast te klein is. Leg wit en zwart opnieuw vast als de ondergrond of sensorhoogte verandert.

## 5. Debugweergave

1. Schakel Diagnostische debuggegevens in.
2. Druk TOEPASSEN.
3. Controleer dat ruwe ADC-waarden en PID-/PI-diagnostiek zichtbaar worden.
4. Schakel debug uit en controleer dat het debugpaneel verdwijnt.
5. Druk OPSLAAN als je de keuze blijvend wilt bewaren.

## 6. Veiligheids- en integratietest

- Test de motoren eerst met de aangedreven wielen vrij van de grond.
- Test de fysieke STOP-knop en de draadloze STOP afzonderlijk.
- Controleer dat de robot stopt bij lijnverlies.
- Controleer dat de UART-communicatie stabiel blijft wanneer debug aanstaat.
- Voer pas daarna een volledige baanproef uit.

## Resultaten

| Test | Resultaat | Datum | Notities |
|---|---|---|---|
| Wi-Fi met lokaal secrets.h | Nog niet uitgevoerd | | |
| D13 power-on-led | Nog niet uitgevoerd | | |
| SAVE → Nano-EEPROM → volledige herstart | Nog niet uitgevoerd | | |
| Witte sensorcalibratie | Nog niet uitgevoerd | | |
| Zwarte sensorcalibratie | Nog niet uitgevoerd | | |
| Debug aan/uit | Nog niet uitgevoerd | | |
| Volledige rijtest na update | Nog niet uitgevoerd | | |
