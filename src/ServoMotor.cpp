//
// Created by Rita Carrilho on 29/02/2024.
//

#include <config.h>
#include "ServoMotor.h"
// #include "Arduino.h"
// #include <Servo.h>

// Servo servo;
int angle = 10;

ServoMotor::ServoMotor() {
    // servo test
    // servo.attach(8);
    // servo.write(angle);
}

void ServoMotor::panMovement() {
    // scan from 0 to 180 degrees
    for(angle = 10; angle < 180; angle++)
    {
        // servo.write(angle);
        // delay(15);
    }
    // now scan back from 180 to 0 degrees
    for(angle = 180; angle > 10; angle--)
    {
        // servo.write(angle);
        // delay(15);
    }
}