#include "TimerOne.h"
#define PIN_AO 0
#define PIN_DO 3

int led_pin = 13;
int led_flag;
// 是否打印相关数据
bool show_data = false;

long check_interval_seconds = 1 * 1000000;
// 最小湿度值设置，高于这个值时，会启动水泵浇水。
// 值越大，土壤越干。值范围为[0, 1023]
int min_humidity = 600;
// 电磁继电器pin脚
int pin_relay = 2;
int sensor_level = LOW;
int sensor_number;

// counter用于记录湿度传感器检测到有水的秒数，因为1s中断一次，所以，可以用它来作为粗略的时间计数器
int sensor_detched_water_counter = -1;
// 湿度值满足要求后，继续浇水的秒数
// 注意：这个值一定要小于下面的 pump_running_seconds_limit
int max_sensor_deteched_water_seconds = 8;

/* 定义has_water_in_bucket和pump_running_seconds_limit 两个值，用来判断和记录水桶里是否还有水，防止水桶没有水时，又恰巧需要浇花时，湿度值达不到条件值而导致水泵一直空转的情况
 * 注意：这里防止水泵空转的逻辑，只适用于整个电路会定期开断电的场景下。比如：通过智能插座设置16:00 ~ 00:00才给开发板通电。
 * 此时，在没水的情况下，每次只会在需要浇水的时候，让水泵运行一次。最大可能地避免了没有情况下，又需要浇水的时候，水泵长时间空转的问题，延长了水泵寿命，节省了电能，避免了噪音。
 * 
 * Q: 你都有智能插座了，为什么不用智能插座直接控制浇水，而多此一举地搞一些开发板来控制？
 * A：智能插座控制水泵浇水是我早期的做法，但，有很多缺点
 *  1) 稳定性差，有多次，智能插座开启水泵后，关闭水泵时出错，导致水泵关闭失败，水溢出，流的到处都是
 *  2) 浇水效果受浇水时长、喷头流量、喷头堵塞、阳光光照和空气温湿度等影响，若只用智能插座，则需要时不时手动调整系统中的一些硬件参数（比如浇水时长、喷头流量等）并多次测试，才能达到满意的效果。
 *     这与我使用自动浇水的初衷是相悖的，我用自己动浇水就是懒得每天浇水，更别提时不时让我调整这些硬件和测试了。
*/
bool has_water_in_bucket = true;
// 水泵运行时间，和满足湿度的时间不是一个时间，因为从水泵开始运转到水流到花盆需要时间t1，水在花盆中的量达到设定的温湿度值的标准又需要时间t2
// pump_running_seconds_limit = t1 + t2 + sensor_detched_water_counter
int pump_running_seconds_limit = 30;
int pump_running_seconds = -1;

void setup() {
  pinMode(PIN_AO, INPUT);
  pinMode(PIN_DO, INPUT);
  pinMode(pin_relay, OUTPUT);
  // LED
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);

  Timer1.initialize(check_interval_seconds);
  Timer1.attachInterrupt(callback);
}

void callback() {
  sensor_number = analogRead(PIN_AO);
  sensor_level = digitalRead(PIN_DO);

  if (sensor_level == HIGH) {
    if (has_water_in_bucket && sensor_number >= min_humidity) {
      // 这里的判断是为了只给继电器发送一次高电平就行，不用重复发送，其实没有判断也行，但是会浪费资源
      if (sensor_detched_water_counter == -1) {
        digitalWrite(pin_relay, HIGH);
        sensor_detched_water_counter = 0;
      }

      if (pump_running_seconds == -1){
        pump_running_seconds =0;
      }
    }

    if (pump_running_seconds >= pump_running_seconds_limit) {
      digitalWrite(pin_relay, LOW);
      sensor_detched_water_counter= -1;
      pump_running_seconds = -1;

      // 这里的判断，是为了防止测试的时候，给传感器水后的max_sensor_deteched_water_seconds还未达到而pump_running_seconds_limit先达到导致的has_water_in_bucket为false的情况
      if (sensor_number >= min_humidity) {
        has_water_in_bucket = false;
      }
    }

    if (pump_running_seconds >= 0) {
      pump_running_seconds++;
    }
    // 当传感器检测到已经有水了，并且满足设定的湿度条件时，才开始计数
    if (sensor_number < min_humidity && sensor_detched_water_counter >= 0) {
      sensor_detched_water_counter++;
    }

    if (sensor_detched_water_counter >= max_sensor_deteched_water_seconds) {
      digitalWrite(pin_relay, LOW);
      sensor_detched_water_counter= -1;
    }
    // 如果水桶里没有，则大号LED亮一秒灭一秒
    if (!has_water_in_bucket) {
      digitalWrite(led_pin, led_flag ? HIGH : LOW);
      led_flag = !led_flag;
    }

    if (show_data) {
      Serial.print("AO=");
    Serial.print(sensor_number);
    Serial.print(", DO=");
    Serial.print(sensor_level);
    Serial.print(", sensor_detched_water_counter=");
    Serial.print(sensor_detched_water_counter);
    Serial.print(", pump_running_seconds=");
    Serial.print(pump_running_seconds);
    Serial.print(", has_water_in_bucket=");
    Serial.println(has_water_in_bucket);
    }
  };
}

void loop() {
}