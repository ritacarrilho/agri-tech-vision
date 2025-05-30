//
// Created by Rita Carrilho on 22/03/2025.
//

#include "ServoServerController.h"
#include "esp_http_server.h"
#include "Arduino.h"
#include "soc/soc.h"
#include "ServoController.h"

extern ServoController tiltServoController;

httpd_handle_t servo_httpd = NULL;

ServoServerController::ServoServerController() {}

esp_err_t ServoServerController::handleMoveServo(httpd_req_t *req) {
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

    char query[50];
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        char panStr[10];
        if (httpd_query_key_value(query, "pan", panStr, sizeof(panStr)) == ESP_OK) {
            int pan = atoi(panStr);
            tiltServoController.moveTo(pan);
            char response[60];
            snprintf(response, sizeof(response), "Servo moved to %d", pan);
            httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
            return ESP_OK;
        }

        char dir[10];
        char deltaStr[10];
        if (httpd_query_key_value(query, "dir", dir, sizeof(dir)) == ESP_OK &&
            httpd_query_key_value(query, "delta", deltaStr, sizeof(deltaStr)) == ESP_OK) {
            int delta = atoi(deltaStr);
            int currentAngle = tiltServoController.getAngle();
            int newAngle = currentAngle;
            if (strcmp(dir, "right") == 0) {
                newAngle = currentAngle + delta;
            } else if (strcmp(dir, "left") == 0) {
                newAngle = currentAngle - delta;
            } else {
                httpd_resp_send(req, "Invalid direction", HTTPD_RESP_USE_STRLEN);
                return ESP_FAIL;
            }
            if (newAngle < 0) newAngle = 0;
            if (newAngle > 180) newAngle = 180;
            tiltServoController.moveTo(newAngle);
            char response[60];
            snprintf(response, sizeof(response), "Servo moved to %d", newAngle);
            httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
            return ESP_OK;
        }
    }
    httpd_resp_send(req, "Invalid parameters", HTTPD_RESP_USE_STRLEN);
    return ESP_FAIL;
}

void ServoServerController::startServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 81;
    config.ctrl_port = 32769;

    if (httpd_start(&servo_httpd, &config) != ESP_OK) {
        Serial.println("Error starting servo server!");
        return;
    }

    httpd_uri_t moveServoUri = {
            .uri       = "/moveServo",
            .method    = HTTP_GET,
            .handler   = ServoServerController::handleMoveServo,
            .user_ctx  = NULL
    };

    esp_err_t err = httpd_register_uri_handler(servo_httpd, &moveServoUri);
    if (err != ESP_OK) {
        Serial.print("Failed to register /moveServo URI. Error: ");
        Serial.println(err);
    }
}
