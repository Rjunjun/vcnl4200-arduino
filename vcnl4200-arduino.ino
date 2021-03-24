#include <arduino-timer.h>
#include "src/CRC_VCNL4200.h"
#define led_pin_sensor 5
#define led_pin_on 6
#define led_pin_error 9

CRC_VCNL4200 vcnl4200;
int pinReading = 0;
uint16_t threshold_appxmt = 150;
uint16_t current_appxmt;
auto timer = timer_create_default(); // create a timer with default settings
int counter = 0;

bool count_timer(void *) {
  counter++;
  if(counter > 2){
    digitalWrite(led_pin_error, 1);
    digitalWrite(led_pin_sensor, 0);
    return false;
  }
  return true;
}

bool vcnl_timer(void *) {
  current_appxmt = vcnl4200.getProximity();
  if(current_appxmt == 0){
    Serial.println(current_appxmt);
    return false;
  }
  counter = 0;
  digitalWrite(13, 0);
  digitalWrite(led_pin_error, 0);
  Serial.println(current_appxmt);
  if(current_appxmt > threshold_appxmt){
    digitalWrite(led_pin_sensor, 0);
  }
  else{
    digitalWrite(led_pin_sensor, 1);
  }
  return true;
}

void setup() {
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(led_pin_sensor, OUTPUT);
  pinMode(led_pin_on, OUTPUT);
  pinMode(led_pin_error, OUTPUT);
  digitalWrite(13, 1);
  digitalWrite(led_pin_error, 1);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Booting.");
  if (vcnl4200.exists()) {
    Serial.println("VCNL4200 found");
    vcnl4200.initialize();
    Serial.println("VCNL4200 initialized");
    digitalWrite(led_pin_error, 1);
    digitalWrite(13, 1);
    timer.every(50, vcnl_timer);
    timer.every(100, count_timer);
    digitalWrite(led_pin_on, 1);
  }
  else{
    Serial.println("VCNL4200 not found");
    digitalWrite(led_pin_error, 1);
    digitalWrite(13, 1);
    }
}

void loop() {
  timer.tick();
}
