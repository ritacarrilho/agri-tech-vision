//
// Created by Rita on 1/1/2024.
//

#include "CameraController.h"
#include "esp_camera.h"
#include "Arduino.h"
#include <camera_pins.h>

sensor_t *camera_sensor2 = NULL;
extern void ComboLog(String message);

CameraController::CameraController() {}

void CameraController::blinkLED(const int ledPin, int onTime, int offTime, int repetitions) {
    for (int i = 0; i < repetitions; i++) {
        digitalWrite(ledPin, HIGH); // Turn on the LED
        delay(onTime); // Wait for the specified onTime
        digitalWrite(ledPin, LOW); // Turn off the LED
        delay(offTime); // Wait for the specified offTime
    }
}

void CameraController::cameraConfig(const int ledPin) {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.fb_location = CAMERA_FB_IN_DRAM;
    config.frame_size = current_cam_framesize;
    config.jpeg_quality = current_cam_quality;

    current_cam_framesize = FRAMESIZE_HVGA;
    current_cam_quality = 20; //10-63 lower number means higher quality
    current_cam_gain = (gainceiling_t)0;

    pinMode(ledPin, OUTPUT);

    if(psramFound()){
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config); // Camera init

    if (err != ESP_OK) {
        digitalWrite(ledPin, LOW);
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    blinkLED(ledPin, 500, 500, 6);
}

void CameraController::setCameraFramesize(int size)
{
    if (size < 0 || size > 13)
    {
        ComboLog(F("Not supported framesize!"));
        return;
    }

    current_cam_framesize = (framesize_t)size;
    camera_sensor2->set_framesize(camera_sensor2, current_cam_framesize);
}

void CameraController::setCameraQuality(int quality)
{
    if (quality < 10 || quality > 63)
    {
        ComboLog(F("Not supported quality!"));
        return;
    }

    current_cam_quality = quality;
    camera_sensor2->set_quality(camera_sensor2, current_cam_quality);
}

void CameraController::setCameraGain(int gain)
{
    if (gain < 0 || gain > 6)
    {
        ComboLog(F("Not supported gain!"));
        return;
    }

    current_cam_gain = (gainceiling_t)gain;
    camera_sensor2->set_gainceiling(camera_sensor2, current_cam_gain);
}

