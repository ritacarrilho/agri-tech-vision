#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "WifiController.h"
#include "ServerController.h"
#include "CameraController.h"
#include <WiFi.h>
#include "ServoController.h"

/*
 * LED 4 : front white LED
 * LED 33 : back red LED
 */
const int ledPin = 33;
// const int filterServoPin = 14;
const int tiltServoPin = 13;

const char* ssid = "Numericable-c463";
const char* password = "cuqpyhr2tlyg";

// const char* ssid = "EPSI_Hotspot";
// const char* password = "ChangeMe";

WifiController wifiController;
ServerController serverController;
CameraController cameraController;

// Create the tilt servo controller as a global instance so that it can be used by the server handler.
ServoController tiltServoController(tiltServoPin, 90);

void mesureLight(int analogVal) {
    Serial.print("Analog Light Value = ");
    Serial.print(analogVal);

    if (analogVal < 40) {
        Serial.println(" => Dark");
    } else if (analogVal < 800) {
        Serial.println(" => Dim");
    } else if (analogVal < 2000) {
        Serial.println(" => Light");
    } else if (analogVal < 3200) {
        Serial.println(" => Bright");
    } else {
        Serial.println(" => Very bright");
    }
}

void setup() {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disable brownout detector

    Serial.begin(115200);
    Serial.setDebugOutput(false);

    wifiController.checkNetworks();
    wl_status_t connectionStatus = wifiController.WiFiConnect(ssid, password, 30000); // Connect to Wi-Fi

    if (connectionStatus != WL_CONNECTED) {
        Serial.println("Failed to connect to the WiFi network.");
    }

    cameraController.cameraConfig(ledPin);
    // Start the HTTP server (this registers both /stream and /moveServo endpoints)
    serverController.startServer();

    // Attach the tilt servo
    tiltServoController.attach();
}

void loop() {
    /*// Rotate continuously clockwise (full speed)
    tiltServo.write(0);
    filterServo.write(90);
    delay(2000); // Rotate for 2 seconds

    // Stop the servo (assuming 90 is the neutral stop for your servo)
    tiltServo.write(90);
    filterServo.write(0);
    delay(1000); // Stop for 1 second

    // Rotate continuously counterclockwise (full speed)
    tiltServo.write(180);
    filterServo.write(90);
    delay(2000); // Rotate for 2 seconds

    // Stop the servo again
    tiltServo.write(90);
    filterServo.write(1800);
    delay(1000); // Stop for 1 second */
}