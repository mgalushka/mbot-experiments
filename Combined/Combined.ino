/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    ColorLoopTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/02
 * @brief   Description: this file is sample code for RGB LED, It used for random color change
 *
 * Function List:
 * 1. bool MeRGBLed::setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
 * 2. void MeRGBLed::show()
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2015/09/02    1.0.0          rebuild the old lib
 * </pre>
 */
#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>


MeRGBLed ledLeft(7, 2);
MeLineFollower lineFinder(PORT_2); 

MeBuzzer buzzer;

float j, f, k;

uint32_t lastTick = millis();
uint32_t startBuzz = 0;
bool buzzing = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  color_loop();
  readLineSensor();
  buzzIninterrupted();
}

void color_loop() {
  for(uint8_t t = 1; t <= 2; t++) {
    uint8_t red	= 64 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    ledLeft.setColor(t, red, green, blue);
    ledLeft.show();
  }
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

void readLineSensor() {
  uint32_t currentTick = millis();
  if (currentTick - lastTick >= 200) {
    lastTick = currentTick;
    int sensorState = lineFinder.readSensors();
    switch(sensorState) {
      case S1_IN_S2_IN:   Serial.println("S1_IN_S2_IN"); stopBuzz(); break;
      case S1_IN_S2_OUT:  Serial.println("S1_IN_S2_OUT"); startBuzzing(); break;
      case S1_OUT_S2_IN:  Serial.println("S1_OUT_S2_IN"); startBuzzing(); break;
      case S1_OUT_S2_OUT: Serial.println("S1_OUT_S2_OUT"); startBuzzing(); break;
      default: break;
    }  
  }
}

void startBuzzing() {
  buzzing = true; 
  startBuzz = millis();
}

void stopBuzz() {
  buzzing = false; 
}

void buzzIninterrupted() {
  uint32_t currentBuzz = millis();
  if (buzzing && currentBuzz - startBuzz <= 1000) {
    buzzer.tone(600, 20);
    Serial.println("Buzzing");
  }
}
