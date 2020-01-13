#include <DFRobot_LIS2DH12.h>
#include <Wire.h>

// DFRobot LIS2DH12 Accelerometer Sensor

#define _SDA PB9
#define _SCL PB8

DFRobot_LIS2DH12 accel;

int16_t x, y, z;

void setup() {
    Serial.begin(115200);
    Wire.begin(0x18);
    while(!Serial);
    delay(100);

    while(accel.init(LIS2DH12_RANGE_2GA) == -1) {
        Serial.println("No I2C devices found");
        delay(1000);
    }
    Serial.println("Connection Complete!");
}

void loop() {
    acceleration();
}

void acceleration() {
    delay(100);
    accel.readXYZ(x, y, z);
    accel.mgScale(x, y, z);
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(",   y: ");
    Serial.print(y);
    Serial.print(",   z: ");
    Serial.println(z);
}
