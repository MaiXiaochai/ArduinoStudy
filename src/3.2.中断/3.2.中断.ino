#include "TimerOne.h"
int flag = 0;

void setup() {
  pinMode(13, OUTPUT); // 设置13引脚用来输出
  Timer1.initialize(1000000); // 初始化定时器，每1s进一次中断服务程序
  Timer1.attachInterrupt(callback); // 设置中断回调函数
}

// 回调函数
// callback 没有放在loop中，因为callback不用循环执行，只要中断来的时候执行一次就行
void callback() {
  digitalWrite(13, flag ? HIGH: LOW);
  flag = !flag;
}

void loop() {
}
