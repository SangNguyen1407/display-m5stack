#include <Arduino.h>
#include "Home.h"
#include "AppController.h"

AppController app;

void setup() {
  M5.begin();
  M5.Lcd.setTextFont(&fonts::efontJA_16);

}

void loop() {
  M5.update();
  app.run();
  
  delay(5000);
}