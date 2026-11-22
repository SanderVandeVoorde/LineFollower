# Security policy – LineFollower V2

## Wi-Fi-credentials

- Commit nooit een bestand met de naam `secrets.h`, een Wi-Fi-wachtwoord, API-token of andere geheime waarde.
- Kopieer de meegeleverde `secrets.example.h` naar `secrets.h` in de betreffende sketchmap en gebruik een uniek wachtwoord van minstens acht tekens.
- De echte `secrets.h`-bestanden zijn opgenomen in de repository-root `.gitignore`.
- De fallback-credentials in de broncode zijn uitsluitend bedoeld om automatische compilatie mogelijk te maken. Zonder lokaal secrets.h start het Wi-Fi-accesspoint niet. Configureer lokale secrets vóór je de ESP32 of de draadloze POC gebruikt.

## Eerder gepubliceerde credentials

Een eerdere publieke versie bevatte een standaard Wi-Fi-wachtwoord. Beschouw dat wachtwoord als gecompromitteerd en wijzig het op de ESP32/AP-configuratie voordat je de robot opnieuw gebruikt. Een nieuwe commit verwijdert een waarde niet uit de bestaande Git-geschiedenis; wachtwoordrotatie is daarom noodzakelijk.

## Meldingen

Meld beveiligingsproblemen rechtstreeks en privé aan de repository-eigenaar. Publiceer geen werkende credentials in een issue of pull request.
