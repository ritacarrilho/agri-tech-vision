# AgriTechVision — Système de surveillance IoT pour l'élevage bovin

AgriTechVision est un système de surveillance basé sur l'ESP32-CAM conçu pour surveiller des vaches / animaux d’élevage. Il permet de diffuser un flux vidéo en direct, d’orienter la caméra à distance via un servo-moteur, et d’ajuster dynamiquement un filtre infrarouge selon la luminosité ambiante.

---

## Fonctionnalités principales

- Diffusion vidéo en direct via HTTP (`/stream`)
- Pilotage d’un servo-moteur pour incliner la caméra à distance (`/moveServo`)
- Analyse de la lumière ambiante via photorésistance
- Contrôle automatique ou manuel d’un filtre IR
- Connexion Wi-Fi

---

## Matériel utilisé

- ESP32-CAM
- Servo-moteur x2 (tilt + filtre IR)
- Capteur de luminosité (photorésistance)
- LED de statut
- Alimentation 5V stable

---

## Installation

### 1. Cloner le projet

```bash
git clone https://github.com/ritacarrilho/agri-tech-vision
```

### 2. Configuration
Créez un fichier secrets.h à la racine avec votre SSID/Mot de passe :
```cpp
#define WIFI_SSID "Votre_SSID"
#define WIFI_PASSWORD "Votre_Mot_de_Passe"
```

### 3. Flasher l’ESP32
Le projet utilise PlatformIO (avec CLion ou VSCode) :

```bash
pio run --target upload
```
Assurez-vous que la carte cible est bien configurée dans platformio.ini.

## Accès au flux vidéo
Une fois démarré, ouvrez votre navigateur à l’adresse suivante :

```arduino
http://<adresse_ip>/stream
```
L’adresse IP est définie en statique dans le code, vous pouvez le changer (WifiController.cpp)

## Contrôle du servo à distance
Utilisez les URLs suivantes :

1. Déplacement direct :

```arduino
http://<adresse_ip>/moveServo?pan=90
```
2. Déplacement relatif :

```bash
http://<adresse_ip>/moveServo?dir=left&delta=15
```

## Structure du code
| Fichier                    | Rôle                                       |
| -------------------------- | ------------------------------------------ |
| `main.cpp`                 | Point d’entrée, initialisation des modules |
| `CameraController.*`       | Configuration matérielle de la caméra      |
| `CameraServerController.*` | Serveur HTTP pour le flux vidéo            |
| `ServoController.*`        | Contrôle d’un servo                        |
| `ServoServerController.*`  | Serveur HTTP pour le contrôle du servo     |
| `IrFilterController.*`     | Mesure de lumière + logique du filtre IR   |
| `WifiController.*`         | Connexion et diagnostic Wi-Fi              |

## Confidentialité
Ce projet est privé et destiné à un usage pédagogique, réalisé dans le cadre des cours de Open Innovation.
Toute reproduction, distribution ou diffusion est interdite sans autorisation préalable.

