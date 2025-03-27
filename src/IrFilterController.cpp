//
// Created by Rita Carrilho on 27/03/2025.
//

#include "IrFilterController.h"

IrFilterController::IrFilterController(int servoPin, int photoPin)
        : _servoPin(servoPin), _photoPin(photoPin)
{
}

// getters and setters

int IrFilterController::measureLight() {
    int lightValue = analogRead(_photoPin);
    Serial.print("Analog Light Value = ");
    Serial.print(lightValue);

    // if (lightValue < 40) {
    //     Serial.println(" => Dark");
    // } else if (lightValue < 800) {
    //     Serial.println(" => Dim");
    // } else if (lightValue < 2000) {
    //     Serial.println(" => Regular");
    // } else if (lightValue < 3200) {
    //     Serial.println(" => Bright");
    // } else {
    //     Serial.println(" => Very bright");
    // } 
    return lightValue;
} 

void IrFilterController::attachIrServo() {
    _servo.attach(_servoPin);
}

void IrFilterController::moveServo(){
    int servoMinRotation = 0;
    int servoMaxRotation = 90;
}

void IrFilterController::applyFIlter() {
    int lightValue = analogRead(_photoPin);

    if (lightValue < 40) {
        Serial.println(" => Dark \n");
    } else if (lightValue < 800) {
        Serial.println(" => Dim \n");
    } else if (lightValue < 2000) {
        Serial.println(" => Regular \n");
    } else if (lightValue < 3200) {
        Serial.println(" => Bright \n");
    } else {
        Serial.println(" => Very bright \n");
    } 
}