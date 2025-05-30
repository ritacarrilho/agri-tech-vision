//
// Created by Rita on 12/27/2023.
//

#include <WiFi.h>
#include "WifiController.h"

unsigned long time_start = millis();
unsigned long time_loop = millis();

wl_status_t WifiController::WiFiConnect(const char* _ssid, const char* _password, const int timeout) {
    IPAddress staticIP(192, 168, 1, 94);
    IPAddress gateway(192, 168, 1, 94);
    IPAddress subnet(255, 255, 255, 0);
    // IPAddress staticIP(192, 168, 0, 15);
    // IPAddress gateway(192, 168, 0, 15);
    // IPAddress subnet(255, 255, 255, 0);
    // IPAddress staticIP(10, 3, 141, 15);
    // IPAddress gateway(10, 3, 141, 165);
    // IPAddress subnet(255, 255, 255, 0);

    WiFi.disconnect(true);
    if (!WiFi.config(staticIP, gateway, subnet)) {
        Serial.println("STA Failed to configure");
        return WL_DISCONNECTED;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED && millis() - time_start < timeout) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection failed!");
        return WL_CONNECT_FAILED;
    } else {
        Serial.println("WiFi connection successful.");
        return WL_CONNECTED;
    }
}

void WifiController::checkNetworks (){
    Serial.println("Scan start");

    int networks = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (networks == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(networks);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < networks; ++i) {
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
    WiFi.scanDelete();
}