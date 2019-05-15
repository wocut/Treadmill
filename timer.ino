#define ledPin 13
int timer1_counter;
void setup() {
  pinMode(ledPin, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  //timer1_counter = 65536-(62500*0.5);  //0.5s 定时器中断
  timer1_counter = 34286;  //预加载timer1 65536-16Mhz/256/2Hz
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1<< TOIE1);
  interrupts();
 
}
ISR(TIMER1_OVF_vect) {
  TCNT1 = timer1_counter;
  digitalWrite(ledPin, digitalRead(ledPin)^1); 
}
void loop() {
  // put your main code here, to run repeatedly:
}
--------------------- 
作者：zzzw0 
来源：CSDN 
原文：https://blog.csdn.net/zzzw0/article/details/75209357 
版权声明：本文为博主原创文章，转载请附上博文链接！
