void setup() {
  // 设定13引脚用来输出
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // 13引脚接高电平，亮
  delay(2000);  // 延时 2000ms,即 2s

  digitalWrite(13, LOW); // 13引脚接低电平，灭
  delay(1000);
}
