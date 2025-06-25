//
// Created by Rita Carrilho on 22/03/2025.
//

#ifndef AGRI_TECH_VISION_SERVOSERVERCONTROLLER_H
#define AGRI_TECH_VISION_SERVOSERVERCONTROLLER_H

#include "esp_http_server.h"

class ServoServerController {
public:
    ServoServerController();
    void startServer();
    static esp_err_t handleMoveServo(httpd_req_t *req);
};

#endif //AGRI_TECH_VISION_SERVOSERVERCONTROLLER_H
