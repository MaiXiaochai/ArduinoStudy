# include "TimerOne.h"

int BUTTON=7;   // 定义按钮在7号引脚，连接一个下拉电阻
int val=0;      // 存储按钮的状态
int old_val=0;  // 暂存val变量的上一个时间状态
int i=0;        // 计数 
int check_interval = 10*1000;   // Time1.initialize的时间单位是微秒

void setup() {
  pinMode(BUTTON,INPUT_PULLUP); // INPUT PULLUP,输入上拉模式
  Serial.begin(9600);           // 用于串口输出
  // 采用中断的方式延迟检测
  Timer1.initialize(check_interval);
  Timer1.attachInterrupt(callback);
}

void callback() {
  val = digitalRead(BUTTON);    // 读取输入模式并且存储
  if((val==HIGH) && (old_val==LOW)) { // 检查按钮的变化情况
    i++;
    Serial.println(i);
  };
  old_val=val;
}

// 采用delay延迟
void loop() {
  // val = digitalRead(BUTTON);    // 读取输入模式并且存储
  // if((val==HIGH) && (old_val==LOW)) { // 检查按钮的变化情况
  //   delay(10);                        // 改成用中断
  //   i++;
  //   Serial.println(i);
  // };
  // old_val=val; // 存旧值
}
