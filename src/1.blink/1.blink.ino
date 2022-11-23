int flag;
unsigned long time_now = 0;

void setup() {
  // 设定13引脚用来输出
  pinMode(13, OUTPUT);
}

void loop() {
  // 统计当前时刻，与上次LED状态更新的时刻经过的时间>1000ms，达成了delay(1000)的功能
  if (millis() > time_now + 1000) {
    time_now = millis();
    digitalWrite(13, flag ? HIGH: LOW);
    // 对flag变量的值取反（代表了LED所连接的13引脚电平）
    flag = !flag;
  }
}
