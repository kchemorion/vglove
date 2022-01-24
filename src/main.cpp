#include <Arduino.h>
#include "MPU9250.h"

#define BUTTON GPIO_NUM_17

MPU9250 mpu;

void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
    Serial.print("X, Y, Z: ");
    Serial.print(mpu.getEulerX(), 2);
    Serial.print(", ");
    Serial.print(mpu.getEulerY(), 2);
    Serial.print(", ");
    Serial.println(mpu.getEulerZ(), 2);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(GPIO_NUM_18,GPIO_NUM_19);
    delay(2000);
    pinMode(BUTTON, INPUT_PULLUP);

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
}

// void loop() {
//     if (mpu.update()) {
//         static uint32_t prev_ms = millis();
//         if (millis() > prev_ms + 25) {
//             print_roll_pitch_yaw();
//             prev_ms = millis();
//         }
//     }
// }

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if ((millis() > (prev_ms + 25)) && !digitalRead(BUTTON)) {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
}
