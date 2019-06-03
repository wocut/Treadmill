/*

* 0.1 摇杆可以控制鼠标，但极品飞车只能支持字符

* 0.2 摇杆可以输出 @ B

* 0.3 加上Y轴信号,但不能向下

*   0.31串口打印K

*   0.32 对0.31优化，可以准确输出左右信息

*       Keyborad不能用双引号“”，只能用单引号‘’

* 0.4 加上声波测距
*0.5 准备 一个超声波管前后，另两个管左右
    cm 接前后
    cm2 转左，
    cm3 转右
 *1.0 加上两上舵机，

*/

#include "Keyboard.h"



//const int xAxis = A0;         // joystick X axis

//const int yAxis = A1;         // joystick Y axis

const int TrigPin = 2; 

const int EchoPin = 3; 


const int TrigPin2 = 5; 

const int EchoPin2 = 6; 


const int TrigPin3 = 9; 

const int EchoPin3 = 8; 
//

int running=0;
int cm=0; 
int cm2=0;
int cm3=0;
#include <Servo.h> 
Servo myservo;
Servo myservo2;

int Filter_Value;
int FV2;
int FV3;
int Value;
int Value2;
int Value3;

void setup() {

  Keyboard.begin();

Serial.begin(9600); 
  myservo.attach(11); 
  myservo.attach(10);
  

pinMode(TrigPin, OUTPUT); 

pinMode(EchoPin, INPUT); 

pinMode(TrigPin2, OUTPUT); 

pinMode(EchoPin2, INPUT); 

pinMode(TrigPin3, OUTPUT); 

pinMode(EchoPin3, INPUT); 


Value = 300;
Value2=300;
Value3=300;

}



void loop() {

 //int xReading = analogRead(A0);

 //int yReading = analogRead(A1);
 
 
 //----------------------------------0--------------------------------
 //-------------------------------VVVVVVVVV---------------------------

digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin, LOW); 
cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
Filter_Value = Filter(cm,Value);       // 获得滤波器输出值
Value = Filter_Value;          // 最近一次有效采样的值，该变量为全局变量
Serial.print(cm); 
Serial.print(","); 
Serial.print(Value); 
Serial.print(",");
//delay(50);
//---------------------------------------------2-----------------------------
//----------------vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------

digitalWrite(TrigPin2, LOW); //低高低电平发一个短时间脉冲去TrigPin 
delayMicroseconds(2); 
digitalWrite(TrigPin2, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin2, LOW); 
cm2 = pulseIn(EchoPin2, HIGH) / 58.0;
FV2 = Filter(cm2,Value2);       // 获得滤波器输出值
Value2 = FV2;          // 最近一次有效采样的值，该变量为全局变量
Serial.print(cm2); 
Serial.print(","); 
Serial.print(Value2); 
Serial.print(","); 
//---------------------------------------------3-----------------------------
//----------------vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------

digitalWrite(TrigPin3, LOW); //低高低电平发一个短时间脉冲去TrigPin 
delayMicroseconds(2); 
digitalWrite(TrigPin3, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin3, LOW); 
cm3 = pulseIn(EchoPin3, HIGH) / 58.0;
FV3 = Filter(cm3,Value3);       // 获得滤波器输出值
Value3 = FV3;          // 最近一次有效采样的值，该变量为全局变量
Serial.print(cm3); 
Serial.print(","); 
Serial.println(Value3); 

//-----------------------------------------------

  if (cm <=55  &&  cm>20) {  

    Keyboard.releaseAll();
    //Keyboard.press('u');

    Keyboard.press( KEY_UP_ARROW );
    //delay(50);dddd
    Runnow();
     if (cm2 <=45  &&  cm2>15){
        Keyboard.release(KEY_RIGHT_ARROW);
        Keyboard.press(KEY_LEFT_ARROW);
        //Keyboard.press('l');
      }
     if(cm3 <=45  &&  cm3>15){
        Keyboard.release(KEY_LEFT_ARROW);
        Keyboard.press(KEY_RIGHT_ARROW);
        //Keyboard.press('r');
      }

    }

   else if (cm >=60 &&  cm<100 )  {   
      Keyboard.releaseAll();
      //Keyboard.press('d');
      Keyboard.press(KEY_DOWN_ARROW);
      //delay(50);
       }

    

 else {

    Keyboard.releaseAll();
    Stopnow();

    }
    
    /*
    
    
    */
    

}



  int Filter(int A1,int V1){
    int ag;
    ag=A1;
    if (A1-V1>10)
      {
        return V1+5;
      }
    else
      {
        return A1;
        //ag=A1*2;
      }
    
    
    }
    
  int Runnow(){
    while (running=0){
      myservo.write(0);
      delay(50);
      myservo.write(180);
      delay(50);
      runing=1;
    }
  }
  int Stopnow(){
    while (running!=0){
    myservo2.write(0);
    delay(50);
    myservo2.write(180);
    delay(50);
    }
  }
