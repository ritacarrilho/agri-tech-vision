//
// Created by Rita on 1/1/2024.
//

#ifndef AGRI_TECH_CAMERACONTROLLER_H
#define AGRI_TECH_CAMERACONTROLLER_H

#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include <config.h>
#include <camera_pins.h>

class CameraController {
    private:
        framesize_t current_cam_framesize;
        int current_cam_quality;
        gainceiling_t current_cam_gain;
    public:
        CameraController();
        void cameraConfig(const int ledPin);
        void linkLED(const int ledPin, int onTime, int offTime, int repetitions);
        void setCameraGain(int gain);
        void setCameraQuality(int quality);
        void setCameraFramesize(int size);
};

#endif //AGRI_TECH_CAMERACONTROLLER_H
