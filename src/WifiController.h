//
// Created by Rita on 12/27/2023.
//

#ifndef ESPWROOM_TEST_WIFICONNECTION_H
#define ESPWROOM_TEST_WIFICONNECTION_H

#include <WiFi.h>

class WifiController {
    public:
        wl_status_t WiFiConnect(const char* _ssid, const char* _password, const int timeout);
        void checkNetworks();
    private:
};


#endif //ESPWROOM_TEST_WIFICONNECTION_H
