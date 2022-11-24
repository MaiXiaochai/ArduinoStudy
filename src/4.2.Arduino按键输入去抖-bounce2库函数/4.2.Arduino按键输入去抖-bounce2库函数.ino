# include <Bounce2.h>
# define BUTTON_PIN 7

int i = 0; // 统计按键次数
Bounce b = Bounce(); // 实例化一个Bounce对象

void setup() {
  b.attach(BUTTON_PIN, INPUT_PULLUP);
  b.interval(10);
  Serial.begin(9600);
}

void loop() {
  b.update();   // 读取按键状态, Update the Bounce instance
  if (b.fell()) { //  通过fell函数判断按键是否按下，Call code if button transitions from HIGH to LOW
    i++;
    Serial.println(i);
  };
}
