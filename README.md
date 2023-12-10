# Arduino CO2 Sensor Project

Ce projet Arduino vise à mesurer la concentration de CO2, l'humidité et la température à l'aide de capteurs et à afficher ou télécharger ces données en fonction du scénario d'utilisation.

## Contenu du Projet

1. **CapteurTestUno**
   - Fichier: `CapteurTestUno.ino`
   - Matériel requis: Arduino Uno, capteur de CO2 (mq135), capteur DHT11, écran LCD, LEDs (verte et rouge)
   - But: Tester les capteurs et afficher les données sur l'écran LCD. Les LEDs indiquent les conditions (verte: bonnes conditions, rouge: CO2 trop élevé).

2. **CapteurTestESP8266**
   - Fichier: `CapteurTestESP8266.ino`
   - Matériel requis: ESP8266, capteur de CO2 (mq135), capteur DHT11
   - But: Tester les capteurs et afficher les données sur le moniteur série. Aucun écran LCD ni LED n'est utilisé ici.

3. **ThingSpeakUploader**
   - Fichier: `ThingSpeakUploader.ino`
   - Matériel requis: ESP8266, capteur de CO2 (mq135), capteur DHT11
   - But: Mesurer les données et les téléverser sur ThingSpeak. Les données sont stockées dans trois champs (CO2, humidité, température). Un fichier `secrets.h` doit être configuré avec les informations Wi-Fi et ThingSpeak.

## Configuration du Fichier Secrets

Le fichier `secrets.h` doit être créé pour chaque projet, et il contient des informations sensibles telles que le nom du réseau Wi-Fi et le mot de passe, ainsi que les informations ThingSpeak.

```cpp
#define SECRET_SSID "NomDuReseauWiFi"    // Remplacer NomDuReseauWiFi par le nom de votre réseau Wi-Fi
#define SECRET_PASS "MotDePasseWiFi"      // Remplacer MotDePasseWiFi par le mot de passe de votre réseau Wi-Fi

#define SECRET_CH_ID 000000               // Remplacer 000000 par le numéro de votre canal ThingSpeak
#define SECRET_WRITE_APIKEY "VotreCleAPI" // Remplacer VotreCleAPI par votre clé API d'écriture ThingSpeak
```

Assurez-vous de ne pas partager ce fichier avec d'autres personnes.

## Licence

Ce projet utilise la licence [MIT](LICENSE) - voir le fichier LICENSE pour plus de détails.
