//
// Created by Rita on 12/27/2023.
//

#include <WiFi.h>
#include "WifiController.h"

unsigned long time_start = millis();
unsigned long time_loop = millis();

WiFiMode_t WifiController::WiFiConnect (const char* _ssid, const char* _password, const int timeout){
    const String SSID_AP = "ESP_AP";

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if(time_loop > time_start + timeout) {
            Serial.println("Wifi connection failed !");
            Serial.println();
            WiFi.disconnect();
            Serial.println("Open Wifi access point : ");
            WiFi.softAP(SSID_AP);
            return WIFI_AP;
        }
    }

    Serial.println(("Wifi connection successfull."));
    Serial.print("Camera Stream Ready! Go to: http://");
    Serial.print(WiFi.localIP());

    // Start streaming web server
    // startCameraServer();

    return WIFI_STA;
}

void WifiController::checkNetworks (){
    Serial.println("Scan start");

    // WiFi.scanNetworks will return the number of networks found.
    int networks = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (networks == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(networks);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < networks; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
                case WIFI_AUTH_OPEN:
                    Serial.print("open");
                    break;
                case WIFI_AUTH_WEP:
                    Serial.print("WEP");
                    break;
                case WIFI_AUTH_WPA_PSK:
                    Serial.print("WPA");
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    Serial.print("WPA2");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    Serial.print("WPA+WPA2");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    Serial.print("WPA2-EAP");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    Serial.print("WPA3");
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    Serial.print("WPA2+WPA3");
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    Serial.print("WAPI");
                    break;
                default:
                    Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    // Delete the scan result to free memory.
    WiFi.scanDelete();
}