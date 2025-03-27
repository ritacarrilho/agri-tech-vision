//
// Created by Rita Carrilho on 27/03/2025.
//

#ifndef IR_FILTER_CONTROLLER_H
#define IR_FILTER_CONTROLLER_H

#include <Arduino.h>
#include <ESP32Servo.h>


class IrFilterController{
    public:
        IrFilterController(int servoPin, int PhotoPin);
        int  measureLight();
        void attachIrServo();
        void moveServo();
        void applyFIlter();
    private:
        int lightValue;
        int _servoPin;
        int _photoPin;
        Servo _servo;
        int _currentAngle;
};

#endif