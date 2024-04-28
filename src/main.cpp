/*
 * unsigned : type modifier used with integer types to indicate that the variable will only hold non-negative values (zero or positive).
 * signed : default, variable that can hold both positive and negative values.
 * const : declare constants, its value cannot be changed after initialization (immutability).
 * * :  variables that store memory addresses as their values (dynamic memory allocation). It is possible to change value of a variable through the pointer. Pointers can be powerful but require careful handling to prevent issues like memory leaks, segmentation faults, or accessing invalid memory addresses.
 */

#include "esp_camera.h"
#include "Arduino.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "WifiController.h"
#include "CameraServerController.h"
#include "CameraController.h"

const int ledPin = 4;

const char* ssid = "Numericable-c463";
const char* password = "cuqpyhr2tlyg";

const int time_interval = 1000;
// const char* ssid = "";
// const char* password = "";

WifiController wifiController;
CameraServerController cameraServerController;
CameraController cameraController;

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
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

    Serial.begin(115200);
    Serial.setDebugOutput(false);

    wifiController.checkNetworks();

    // Initialize camera
    cameraController.cameraConfig();

    // Connect to Wi-Fi
    wifiController.WiFiConnect(ssid, password, time_interval);

    // Start the camera server to stream video
    cameraServerController.startCameraServer();

    // pinMode(ledPin, OUTPUT);
}

void loop() {
    // delay(1);

    /* Turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("LED on");
    delay(1000);  // Wait for 1 second

    // Turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("LED off");
    delay(1000);  // Wait for 1 second
     */
}

/*
 * make local server / API
 * send data to server / api
 */