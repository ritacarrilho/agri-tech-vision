//
// Created by Rita on 1/1/2024.
//
#pragma once

#ifndef AGRI_TECH_CAMERASERVERCONTROLLER_H
#define AGRI_TECH_CAMERASERVERCONTROLLER_H
#include "esp_http_server.h"
#include <config.h>

class CameraServerController {
    private:
        httpd_handle_t stream_httpd = NULL;
        static const char* _STREAM_CONTENT_TYPE;
        static const char* _STREAM_BOUNDARY;
        static const char* _STREAM_PART;
    public:
        CameraServerController();
        static esp_err_t handleStreamRequest(httpd_req_t *req);
        void startCameraServer();
};

#endif //AGRI_TECH_CAMERASERVERCONTROLLER_H
