
#include <cstdlib>
#include <iostream>
#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include "secrets.h"
#include "WifiController.h"
#include "CameraServerController.h"
#include "CameraController.h"
#include "ServoController.h"
#include "ServoServerController.h"
#include "IrFilterController.h"


/* TODO:
 *  make IR filter servo movement
 *  Define light values (max and min)
*/

const int ledPin = 33;
const int filterServoPin = 14;
const int tiltServoPin = 13;

WifiController wifiController;
CameraServerController cameraServerController;
ServoServerController servoServerController;
CameraController cameraController;
ServoController tiltServoController(tiltServoPin, 90);
IrFilterController filterController(filterServoPin, GPIO_NUM_32);


void setup() {
    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 

    Serial.begin(115200);
    Serial.setDebugOutput(false);
    
    analogSetAttenuation(ADC_11db);
    pinMode(GPIO_NUM_32, INPUT);

    // Connect to Wi-Fi
    wifiController.checkNetworks();
    wl_status_t connectionStatus = wifiController.WiFiConnect(WIFI_SSID, WIFI_PASSWORD, 30000);

    if (connectionStatus != WL_CONNECTED) {
        Serial.println("Failed to connect to the WiFi network.");
    }

    // Configure pins for camara
    cameraController.cameraConfig(ledPin);

    // Start servers and image streaming
    cameraServerController.startServer();
    servoServerController.startServer();

    // Attach the tilt servo.
    tiltServoController.attach();
    // filterController.attachIrServo();
}

void loop() {
}