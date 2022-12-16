#include <Keypad.h> // 声明库函数

const byte ROWS = 4; //四行
const byte COLS = 4; //四列
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // 连接到矩阵键盘的行的引脚
byte colPins[COLS] = {5, 4, 3, 2}; // 连接到矩阵键盘的列的引脚

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if(key){
    Serial.print("Key Pressed: ");
    Serial.println(key); // 将得到的字符发送到串口
  }
}
