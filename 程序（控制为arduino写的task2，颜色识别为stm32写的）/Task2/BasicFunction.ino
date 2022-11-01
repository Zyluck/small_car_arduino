//所有电机动作程序
int Left_motor = 8;     //电机程序1
int Left_motor_pwm = 9;     //电机程序2
int Right_motor_pwm = 10;     // 电机程序3
int Right_motor = 11;     // 电机程序4
int key = A2;     //
int SL;     //传感器
int SR;     //传感器
int SM;     //传感器
int SB;     //传感器
const int SensorRight = 3;     //传感器1（数线）
const int SensorLeft = 4;      //传感器2（数线）
const int SensorMin = 44;      //传感器3（定位）
const int SensorBack = 5;      //传感器4（巡线）
const int SensorBackLeft = 45;      //传感器5（巡线）
void Motorinit()
{
  //brake(1,0);
  pinMode(Left_motor,OUTPUT);     // 
  pinMode(Left_motor_pwm,OUTPUT);     // 
  pinMode(Right_motor_pwm,OUTPUT);      // 
  pinMode(Right_motor,OUTPUT);      // 
  pinMode(key,INPUT);     //
  pinMode(beep,OUTPUT);
  pinMode(47,OUTPUT);
  digitalWrite(47,HIGH);
  
  pinMode(SensorRight, INPUT);      //
  pinMode(SensorLeft, INPUT);     //
  pinMode(SensorMin, INPUT);      //
  pinMode(SensorBack, INPUT);     //
}
void motor_run(int Delay_time = 0,unsigned char _speed = 120)     //
{ 
  digitalWrite(Right_motor,LOW);      //
  digitalWrite(Right_motor_pwm,HIGH);     //     
  analogWrite(Right_motor_pwm,_speed);      //

  digitalWrite(Left_motor,LOW);     //
  digitalWrite(Left_motor_pwm,HIGH);      //     
  analogWrite(Left_motor_pwm,_speed);     //
  if(Delay_time != 0)
  {
    delay(Delay_time);
    brake(1,0);
  }
}
void spin_left_first()      //
{
  digitalWrite(Right_motor,LOW);      //
  digitalWrite(Right_motor_pwm,HIGH);  // 
  analogWrite(Right_motor_pwm,120);     //
  
  digitalWrite(Left_motor,HIGH);  //
  digitalWrite(Left_motor_pwm,LOW);  //
  analogWrite(Left_motor_pwm,120);//
}
void spin_right()        //
{
  digitalWrite(Right_motor,HIGH);  // 
  digitalWrite(Right_motor_pwm,HIGH);  // 
  analogWrite(Right_motor_pwm,140);//  
  
  digitalWrite(Left_motor,LOW);  //
  digitalWrite(Left_motor_pwm,HIGH);  //
  analogWrite(Left_motor_pwm,140);//
}
void Go_straight(int Speed = 100)
{

    SR = digitalRead(SensorRight);//
    SL = digitalRead(SensorLeft);//
    
    if (SL == LOW && SR==LOW)
      motor_run(0,Speed);   //
    else if (SL == HIGH & SR == LOW)// 
      spin_left_first();
    else if (SL == LOW & SR == HIGH) //  
      spin_right(); 
    else
    {
        motor_run(0,Speed);  
    }
}
void brake(int flag,int delay_time)         //
{
  if(flag != 1)
  {
    digitalWrite(Left_motor,HIGH);
    digitalWrite(Right_motor,HIGH);
  }
  else
  {
    digitalWrite(Left_motor,LOW);
    digitalWrite(Right_motor,LOW);
  }
  if(delay_time != 0)
    delay(delay_time);
  if(flag == 1)
  {
    digitalWrite(Left_motor,HIGH);
    digitalWrite(Right_motor,HIGH);
  }
  else
  {
    digitalWrite(Left_motor,LOW);
    digitalWrite(Right_motor,LOW);
  }
  digitalWrite(Right_motor_pwm,255);   
  digitalWrite(Left_motor_pwm,255);  //  
  delay(30);
  digitalWrite(Right_motor_pwm,LOW);  // 
  analogWrite(Right_motor_pwm,0);//

  digitalWrite(Left_motor_pwm,LOW);  //
  analogWrite(Left_motor_pwm,0);//
}

void back(int _Speed = 100)          
{
  digitalWrite(Right_motor,HIGH);  
  digitalWrite(Right_motor_pwm,HIGH);   
  analogWrite(Right_motor_pwm,_Speed);
  
  
  digitalWrite(Left_motor,HIGH);  
  digitalWrite(Left_motor_pwm,HIGH);  //  
  analogWrite(Left_motor_pwm,_Speed);//
}
void back_straight()
{
    SR = digitalRead(SensorBack);//
    SL = digitalRead(SensorBackLeft);//
    
    if (SL == LOW && SR==LOW)
      back(90);   //
    else if (SL == HIGH & SR == LOW)// 
      spin_right();
    else if (SL == LOW & SR == HIGH) //  
      spin_left_first(); 
    else
    {
        back(90);
        delay(100);
    }
}
void keysacn()//检测按键是否按下
{
  int val;
  val=digitalRead(key);//
  while(!digitalRead(key))//
  {
    val=digitalRead(key);//
  }
  while(digitalRead(key))//
  {
    delay(10);  //
    val=digitalRead(key);//
    if(val==HIGH)  //
    {
      digitalWrite(beep,HIGH);
      while(!digitalRead(key))
      digitalWrite(beep,LOW);
    }
    else
      digitalWrite(beep,LOW);//
  }
}
