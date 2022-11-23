#include "TimerOne.h"
int flag = 0;
long c = 0; // 接收新的中断间隔

void setup() {
  Serial.begin(9600);
  while(Serial.read()>=0);
  pinMode(13, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(callback);
}

void callback() {
  digitalWrite(13, flag ? HIGH: LOW);
  flag = !flag;
}


void loop() {
  if(Serial.available()>0) {         // [接收] 判断串口是否有数据输入
    c=Serial.parseInt();             // [接收] 读取输入数据，转换为整数
    Serial.println(c);
    while(Serial.read()>=0);         // 清除缓存
    Timer1.setPeriod(c * 1000);      // 设置新的中断间隔, 设置新的中断间隔, 毫秒转换为微秒
    Timer1.attachInterrupt(callback);
  }
}
