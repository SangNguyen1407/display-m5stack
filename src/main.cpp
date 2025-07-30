#include <Arduino.h>
// #include <M5Core2.h>
#include <Home.h>

void setup() {
  M5.begin();
  M5.Lcd.setTextFont(&fonts::efontJA_16);
  
  Home home;
  home.show();
}

void loop() {
  M5.update();
  delay(5000);
}