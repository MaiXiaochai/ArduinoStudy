# include "TimerOne.h"
#define PIN_AO 0
#define PIN_DO 3

long check_interval_seconds = 1 * 1000000;
long water_seconds = 20 * 1000000;
int pin_relay = 2;
int sensor_level = LOW;
int sensor_number;

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
    if (sensor_number >= 500) {
      digitalWrite(pin_relay, HIGH);
      Timer1.initialize(water_seconds);

    } else {
        digitalWrite(pin_relay, LOW);
        Timer1.initialize(check_interval_seconds);
      }
      // Serial.print("AO=");
      // Serial.print(sensor_number);
      // Serial.print(", DO=");
      // Serial.println(sensor_level);
  };
}

void loop() {
}