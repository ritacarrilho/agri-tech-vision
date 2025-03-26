//
// Created by Rita on 1/1/2024.
//

#include "CameraServerController.h"
#include "esp_http_server.h"
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "soc/soc.h"
#include <WiFi.h>

// Global HTTP server handle for camera streaming.
httpd_handle_t camera_httpd = NULL;

const char* CameraServerController::_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace; boundary=frameboundary";
const char* CameraServerController::_STREAM_BOUNDARY = "\r\n--frameboundary\r\n";
const char* CameraServerController::_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

CameraServerController::CameraServerController() {}

esp_err_t CameraServerController::handleStreamRequest(httpd_req_t *req) {
    camera_fb_t *fb = nullptr;
    esp_err_t res = ESP_OK;
    size_t _jpg_buf_len = 0;
    uint8_t *_jpg_buf = nullptr;
    char part_buf[64];

    res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
    if (res != ESP_OK) {
        return res;
    }

    while (true) {
        fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Camera capture failed");
            return ESP_FAIL;
        }

        // Convert frame to JPEG if needed.
        if (fb->format != PIXFORMAT_JPEG) {
            bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
            esp_camera_fb_return(fb);
            fb = nullptr;
            if (!jpeg_converted) {
                Serial.println("JPEG compression failed");
                return ESP_FAIL;
            }
        } else {
            _jpg_buf_len = fb->len;
            _jpg_buf = fb->buf;
        }

        if (_jpg_buf) {
            size_t hlen = snprintf(part_buf, sizeof(part_buf), _STREAM_PART, _jpg_buf_len);
            res = httpd_resp_send_chunk(req, part_buf, hlen);
            if (res == ESP_OK) {
                res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
            }
            if (res == ESP_OK) {
                res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
            }
            if (fb && fb->format != PIXFORMAT_JPEG) {
                free(_jpg_buf);
                _jpg_buf = nullptr;
            }
            if (fb) {
                esp_camera_fb_return(fb);
                fb = nullptr;
            }
        } else {
            if (fb) {
                esp_camera_fb_return(fb);
                fb = nullptr;
            }
            Serial.println("Failed to acquire frame buffer");
            return ESP_FAIL;
        }
        if (res != ESP_OK) {
            break;
        }
    }
    return res;
}

void CameraServerController::startServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;  // Stream server runs on port 80

    httpd_uri_t index_uri = {
            .uri       = "/stream",
            .method    = HTTP_GET,
            .handler   = CameraServerController::handleStreamRequest,
            .user_ctx  = nullptr
    };

    if (httpd_start(&camera_httpd, &config) != ESP_OK) {
        Serial.println("Error starting camera server!");
        return;
    }

    if (httpd_register_uri_handler(camera_httpd, &index_uri) != ESP_OK) {
        Serial.println("Error setting /stream URI handler!");
    } else {
        char url[50];
        snprintf(url, sizeof(url), "http://%s:%d%s", WiFi.localIP().toString().c_str(),
                 config.server_port, index_uri.uri);
        Serial.print("Camera stream server started successfully! URL: ");
        Serial.println(url);
    }
}
