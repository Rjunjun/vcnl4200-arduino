#include <arduino-timer.h>
#include "src/CRC_VCNL4200.h"
#define led_pin 5

CRC_VCNL4200 vcnl4200;
int pinReading = 0;
uint16_t threshold_appxmt = 150;
uint16_t current_appxmt;
auto timer = timer_create_default(); // create a timer with default settings

bool vcnl_timer(void *) {
  current_appxmt = vcnl4200.getProximity();
  Serial.println(current_appxmt);
  if(current_appxmt > threshold_appxmt){
    digitalWrite(led_pin, 0);
    digitalWrite(13, 0);
  }
  else{
    digitalWrite(led_pin, 1);
    digitalWrite(13, 1);
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Booting.");
  if (vcnl4200.exists()) {
    Serial.println("VCNL4200 found");
    vcnl4200.initialize();
    Serial.println("VCNL4200 initialized");
  }
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(led_pin, OUTPUT);
  timer.every(1, vcnl_timer);
}

void loop() {
  timer.tick();
}
