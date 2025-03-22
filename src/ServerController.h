//
// Created by Rita on 1/1/2024.
//
#pragma once

#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include "esp_http_server.h"

class ServerController {
public:
    ServerController();

    // Starts the HTTP server, registers the /stream and /moveServo endpoints.
    void startServer();

    // HTTP handler for streaming camera frames.
    static esp_err_t handleStreamRequest(httpd_req_t *req);

private:
    static const char* _STREAM_CONTENT_TYPE;
    static const char* _STREAM_BOUNDARY;
    static const char* _STREAM_PART;
};

#endif