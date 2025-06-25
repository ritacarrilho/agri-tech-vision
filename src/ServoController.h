//
// Created by Rita Carrilho on 22/03/2025.
//

#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoController {
public:
    ServoController(int servoPin, int initialAngle = 0);
    void attach();
    void moveTo(int angle);
    int getAngle() const;

private:
    int _servoPin;
    Servo _servo;
    int _currentAngle;
};

#endif