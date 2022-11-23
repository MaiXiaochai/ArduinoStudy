char c; // 记录接收到的数据

void setup() {
  Serial.begin(9600); // 设置波特率为9600
  while (Serial.read() >= 0); // 清除缓存，只要有缓存就一直读
}

void loop() {
  while (Serial.available()) {  // 判断串口是否有数据输入
    c=Serial.read();            // 读取输入数据
    if(c=='R')                  // 判断输入是否为R
      Serial.println("Hello world!"); // 通过串口输出 Hello World！ Arduino语法中，如果if下边只执行一条语句，可以不用大括号"{}"包围
  }
}
