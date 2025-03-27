#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "WifiController.h"
#include "CameraServerController.h"
#include "CameraController.h"
#include <WiFi.h>
#include "ServoController.h"
#include "ServoServerController.h"
#include "IrFilterController.h"

/*
 * LED 4 : front white LED
 * LED 33 : back red LED
 */

const int ledPin = 33;
const int filterServoPin = 14;
const int tiltServoPin = 13;

const char* ssid = "Numericable-c463";
const char* password = "cuqpyhr2tlyg";

// const char* ssid = "EPSI_Hotspot";
// const char* password = "ChangeMe";

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
    
    // analogSetAttenuation(ADC_11db);
    // pinMode(GPIO_NUM_32, INPUT);

    // Connect to Wi-Fi
    // wifiController.checkNetworks();
    // wl_status_t connectionStatus = wifiController.WiFiConnect(ssid, password, 30000); 

    // if (connectionStatus != WL_CONNECTED) {
    //     Serial.println("Failed to connect to the WiFi network.");
    // }

    // // Configure pins for camara
    // cameraController.cameraConfig(ledPin);
    // // Start the streaming and servo servers.
    // cameraServerController.startServer();
    // servoServerController.startServer();

    // Attach the tilt servo.
    tiltServoController.attach();
    filterController.attachIrServo();
}

void loop() {
    // static uint8_t state = LOW;
    // int lightValue = analogRead(GPIO_NUM_32);

    // Serial.print("Light sensor reading: ");
    // Serial.println(lightValue);
    // measureLight();

    filterController.measureLight();
    delay(1000);
}