#include "TimerOne.h"
#define PIN_AO 0
#define PIN_DO 3

long check_interval_seconds = 1 * 1000000;
int min_humidity = 450;
int pin_relay = 2;
int sensor_level = LOW;
int sensor_number;
int counter = -1;
int water_seconds = 10;

void setup() {
  pinMode(PIN_AO, INPUT);
  pinMode(PIN_DO, INPUT);
  pinMode(pin_relay, OUTPUT);
  Serial.begin(9600);

  Timer1.initialize(check_interval_seconds);
  Timer1.attachInterrupt(callback);
}

void callback() {
  sensor_number = analogRead(PIN_AO);
  sensor_level = digitalRead(PIN_DO);

  if (sensor_level == HIGH) {
    if (sensor_number >= min_humidity) {
      counter=0;
      digitalWrite(pin_relay, HIGH);
    };

    if (counter >= 0) {
      counter++;
    }

    if (counter >= water_seconds) {
      digitalWrite(pin_relay, LOW);
      counter= -1;
    }
    Serial.print("AO=");
    Serial.print(sensor_number);
    Serial.print(", DO=");
    Serial.print(sensor_level);
    Serial.print(", counter=");
    Serial.println(counter);
  };
}

void loop() {
}