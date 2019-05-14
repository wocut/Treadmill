//1.1 增加一个超声波
//1.2 
 
#define Trig 2 //引脚Tring 连接 IO D2
#define Echo 3 //引脚Echo 连接 IO D3 
#define Trig2 4 //2号引脚Tring 连接 IO D4
#define Echo2 5 //2号引脚Echo 连接 IO D5 

 
float cm; //距离变量
float temp; // 
float cm2; //2号距离变量
float temp2; // 
int Filter_Value;
 
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Echo2, INPUT);
}
 
void loop() {
  //给Trig发送一个低高低的短时间脉冲,触发测距
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,
  //pulseIn函数会等待引脚变为HIGH,开始计算时间,再等待变为LOW并停止计时
  //返回脉冲的长度
  
  //声速是:340m/1s 换算成 34000cm / 1000000μs => 34 / 1000
  //因为发送到接收,实际是相同距离走了2回,所以要除以2
  //距离(厘米)  =  (回波时间 * (34 / 1000)) / 2
  //简化后的计算公式为 (回波时间 * 17)/ 1000
  
  cm = (temp * 17 )/100; //把回波时间换算成cm
 
  //Serial.print("Echo =");
  //Serial.print(temp);//串口输出等待时间的原始数据
  //Serial.print(" | | Distance = ");
  
  
  
  
  Serial.print(cm);//串口输出距离换算成cm的结果
  Serial.print(",");
  Filter_Value = Filter();       // 获得滤波器输出值
  Value = Filter_Value;          // 最近一次有效采样的值，该变量为全局变量
  Serial.print(Filter_Value); // 串口输出
  Serial.print(",");
  delay(10);
  
  
  
  
  digitalWrite(Trig2, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig2,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig2, LOW); //给Trig发送一个低电平
  
  temp2 = float(pulseIn(Echo2, HIGH)); 
  cm2 = (temp2 * 17 )/100;
  Serial.println(cm2);
  //Serial.println("\n");
  delay(10);
}

    // 限幅滤波法（又称程序判断滤波法）
    #define FILTER_A 100
    int Filter(cm) {
      int NewValue;
      NewValue = cm;
      if(((NewValue - Value) > FILTER_A) || ((Value - NewValue) > FILTER_A))
        return Value;
      else
        return NewValue;
    }
