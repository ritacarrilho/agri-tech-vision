#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "WifiController.h"
#include "CameraServerController.h"
#include "CameraController.h"
#include <WiFi.h>
#include "ServoController.h"
#include "ServoServerController.h"

/*
 * LED 4 : front white LED
 * LED 33 : back red LED
 */

#define LIGHT_SENSOR_PIN 34

const int ledPin = 33;
// const int filterServoPin = 14;
const int tiltServoPin = 13;

const char* ssid = "Numericable-c463";
const char* password = "cuqpyhr2tlyg";

// const char* ssid = "EPSI_Hotspot";
// const char* password = "ChangeMe";

WifiController wifiController;
CameraServerController cameraServerController;
ServoServerController servoServerController;
CameraController cameraController;

// Global servo controller instance for tilt (used by the servo server)
ServoController tiltServoController(tiltServoPin, 90);

void measureLight() {
    /* Serial.print("Analog Light Value = ");
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
    } */
}

void setup() {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disable brownout detector

    Serial.begin(115200);
    Serial.setDebugOutput(false);
    analogSetAttenuation(ADC_11db);
    pinMode(LIGHT_SENSOR_PIN, INPUT);

    wifiController.checkNetworks();
    wl_status_t connectionStatus = wifiController.WiFiConnect(ssid, password, 30000); // Connect to Wi-Fi

    if (connectionStatus != WL_CONNECTED) {
        Serial.println("Failed to connect to the WiFi network.");
    }

    cameraController.cameraConfig(ledPin);
    // Start the streaming and servo command servers.
    cameraServerController.startServer();
    servoServerController.startServer();

    // Attach the tilt servo.
    tiltServoController.attach();
}

void loop() {
    // Read the raw ADC value (range typically 0 - 4095).
    int lightValue = analogRead(LIGHT_SENSOR_PIN);

    // Print the value to the Serial Monitor.
    Serial.print("Light sensor reading: ");
    Serial.println(lightValue);

    // Adjust delay as needed (e.g., measure every second).
    delay(1000);

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