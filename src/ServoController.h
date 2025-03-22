//
// Created by Rita Carrilho on 22/03/2025.
//

#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoController {
public:
    // Constructor: pass the servo pin and optional initial angle (default 90°)
    ServoController(int servoPin, int initialAngle = 90);

    // Attach the servo to the specified pin and set it to the initial angle
    void attach();

    // Move the servo to a specified angle (constrained between 0 and 180)
    void moveTo(int angle);

    // Retrieve the current angle
    int getAngle() const;

private:
    int _servoPin;
    Servo _servo;
    int _currentAngle;
};

#endif