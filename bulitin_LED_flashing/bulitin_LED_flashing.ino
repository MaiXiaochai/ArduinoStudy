//默认延迟秒数
const int delaySecond = 1;
 
//开灯
void trun_off_the_lights(int delaySecond)
{
  // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(LED_BUILTIN, LOW);
}
 
//关灯
void trun_on_the_lights(int delaySecond)
{
  // Turn the LED off by making the voltage HIGH
  digitalWrite(LED_BUILTIN, HIGH);
}
 
void setup() {
  // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
   
// the loop function runs over and over again forever
void loop() {
  Serial.println("Panda Test - Light On");
  trun_on_the_lights(delaySecond);
  // Wait
  delay(delaySecond * 1000);
  
  Serial.println("Panda Test - Light Off");
  trun_off_the_lights(delaySecond);
  // Wait
  delay(delaySecond * 2000);
  
}