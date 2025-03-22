//
// Created by Rita Carrilho on 22/03/2025.
//

#include "ServoController.h"

ServoController::ServoController(int servoPin, int initialAngle)
        : _servoPin(servoPin), _currentAngle(initialAngle)
{
}

void ServoController::attach() {
    _servo.attach(_servoPin);
    _servo.write(_currentAngle);
}

void ServoController::moveTo(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    _currentAngle = angle;
    Serial.print("Servo on pin ");
    Serial.print(_servoPin);
    Serial.print(" moving to angle ");
    Serial.println(_currentAngle);
    _servo.write(_currentAngle);
}

int ServoController::getAngle() const {
    return _currentAngle;
}
