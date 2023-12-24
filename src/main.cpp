//
// Created by Rita on 12/21/2023.
//
#include <WiFi.h>
#define LIGHT_SENSOR_PIN   35
// #define PORT_LED_FLASH      4

/*
 * unsigned : type modifier used with integer types to indicate that the variable will only hold non-negative values (zero or positive).
 * signed : default, variable that can hold both positive and negative values.
 * const : declare constants, its value cannot be changed after initialization (immutability).
 * * :  variables that store memory addresses as their values (dynamic memory allocation). It is possible to change value of a variable through the pointer. Pointers can be powerful but require careful handling to prevent issues like memory leaks, segmentation faults, or accessing invalid memory addresses.
 */

const char* SSID_L = "Numericable-c463";
const char* MOT_DE_PASSE_L = "cuqpyhr2tlyg";
wl_status_t StatutConnexion_L;

const int TIMEOUT_WIFI = 10000;

WiFiMode_t  FCT_WiFI_Init (const char* _ssid, const char* _password){
    unsigned long time_start = millis();
    unsigned long time_boucle;

    const String SSID_AP = "ESP_AP";

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_L, MOT_DE_PASSE_L);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        time_boucle = millis();
        if(time_boucle > time_start + TIMEOUT_WIFI) {
            Serial.println("Wifi connection failed !");
            Serial.println();
            WiFi.disconnect();
            Serial.println("Open Wifi access point : ");
            WiFi.softAP(SSID_AP);
            return WIFI_AP;
        }
    }

    Serial.println(("Wifi connection successfull."));
    return WIFI_STA;
}


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

void setup()
{
    Serial.begin(115200);
    // pinMode(PORT_LED_FLASH, OUTPUT);

    FCT_WiFI_Init(SSID_L, MOT_DE_PASSE_L);
     StatutConnexion_L = WiFi.status();
       while ((StatutConnexion_L != WL_NO_SSID_AVAIL)&&(StatutConnexion_L != WL_CONNECTED)&&(StatutConnexion_L != WL_CONNECT_FAILED))
       {
           StatutConnexion_L = WiFi.status();
           // digitalWrite(PORT_LED_FLASH, HIGH);
           // delay(100);
           // digitalWrite(PORT_LED_FLASH, LOW);
           // delay(500);
       }

       if (StatutConnexion_L == WL_CONNECTED)
       {
           Serial.println("Password OK");
           Serial.println("Connection OK");
           Serial.println("IP address: ");
           Serial.print(WiFi.softAPIP());
       }
       else if (StatutConnexion_L == WL_NO_SSID_AVAIL)
       {
           Serial.println("SSID not found");
       }
       else if (StatutConnexion_L == WL_CONNECT_FAILED)
       {
           Serial.println("Password KO");
       }
       else
       {
           Serial.println("Other error");
       }

    Serial.println(' ');
}

void loop()
{
    int analogValue = analogRead(LIGHT_SENSOR_PIN); // from 0 (no light) to 1023 (maximal light)

    delay(10);
    mesureLight(analogValue);
    // digitalWrite(PORT_LED_FLASH, HIGH);
    // delay(1000);
    // digitalWrite(PORT_LED_FLASH, LOW);
    delay(1000);
}
