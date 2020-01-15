#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//
//MeRGBLed led(PORT_3);
//
//void setup() {
//  // reset led
//  led.reset(PORT_3);
//}
//
//void loop() {
//  // do nothing
//}


MeRGBLed rgbled_7(7, 2);

void setup() {
  Serial.begin(9600);
}


void loop() {
//  rgbled_7.setColor(1, 0, 128, 0);
//  rgbled_7.show();
//  rgbled_7.setColor(2, 255, 0, 0);
//  rgbled_7.show();

  for(uint8_t t = 1; t <= 2; t++) {
    uint8_t red = random(0, 255);
    uint8_t green = random(0, 255);
    uint8_t blue = random(0, 255);
    Serial.println(t);
    rgbled_7.setColor(2, red, green, blue);
    rgbled_7.show();
  }
  delay(100);
}
