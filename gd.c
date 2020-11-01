#include <Time.h>
#include <TimeLib.h>

#define GREENLIGHT 13
#define REDLIGHT 12
#define NEEDS_WATER_THRESHOLD 300

int shinerPins[] = {8,9,10};
int pinsSize = sizeof(shinerPins) / sizeof(shinerPins[0]);

void setup() {
  for (int i = 0; i < pinsSize; i++) {
    pinMode(shinerPins[i], OUTPUT);
  }
  pinMode(GREENLIGHT, OUTPUT);
  pinMode(REDLIGHT, OUTPUT);
}

void loop() {
  checkShineLights();
  checkMoisture();
  delay(2000);
}

void checkShineLights() {
  if (hour() >= 0 && hour() <= 10) {
    setShineLights(true);
  }
  else {
    setShineLights(false);
  }
}

void setShineLights(boolean on) {
  int setting = on ? HIGH : LOW;
  for (int i = 0; i < pinsSize; i++) {
    digitalWrite(shinerPins[i], setting);
  }
}

void checkMoisture() {
  int moistureValue = analogRead(A0);
  if (moistureValue > NEEDS_WATER_THRESHOLD) {
    turnOnAlertLight(REDLIGHT);
  }
  else {
    turnOnAlertLight(GREENLIGHT);
  } 
}

void turnOnAlertLight(int light) {
  if (light == GREENLIGHT) {
    digitalWrite(GREENLIGHT, HIGH);
    digitalWrite(REDLIGHT, LOW);
  }
  else if (light == REDLIGHT){
    digitalWrite(REDLIGHT, HIGH);
    digitalWrite(GREENLIGHT, LOW);
  }
}
