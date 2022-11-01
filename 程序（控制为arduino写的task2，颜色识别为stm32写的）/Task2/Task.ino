//逻辑执行
int Count_lines(bool flag_restart, int Sensor)
{
  static int Pre_SM = 0;
  static int Count = 0;
  if(flag_restart == true)
  {
    Pre_SM = 0;
    Count = 0;
    return 0;
  }
  SM = digitalRead(Sensor);  
  if(SM == HIGH && Pre_SM == LOW)
  {
    Count++;
  }
  Pre_SM = SM;
  delay(20);
  return Count;
}
void Go_Out()//出发程序
{
  int Count = 0;
  motor_run(0,90);
  Count_lines(true,0);
  while(1)
  {
    Count = Count_lines(false,SensorMin);
    if(Count == 4)
    {
      brake(1,0);
      break;
    }
  }
  spin_right();
  Count_lines(true,0);
  while(1)
  {
    Count = Count_lines(false,SensorRight);
    if(Count == 3)
    {
      brake(1,0);
      break;
    }
  }
}
void Stop_on_QRCode()
{
  int myCount_lines = 0;
  Count_lines(true,0);
  while(1)
  {
    if(myCount_lines == 3)
      digitalWrite(47,LOW);
    myCount_lines = Count_lines(false,SensorMin);
    if(myCount_lines == 6)
    {
      break;
    }
    if(myCount_lines < 5)
       Go_straight(120);
    else
       Go_straight(70);
  }
  brake(1,0);
}
void back_to_Material_Area()
{
  int myCount_lines = 0;
  back(100);
  delay(500);
  Count_lines(true,0);
  while(1)
  { 
    myCount_lines = Count_lines(false,SensorMin);
    if(myCount_lines == 2)
    {
      brake(2,0);
      break;
    }
  }
}

void Green_to_Red(int Line_Counts)
{
  if(Line_Counts == 0)
    return;
  motor_run(0,100);
  Count_lines(true,0);
  int nTemp = 0;
  while(1)
  { 
    if(nTemp < 20)
    {
      nTemp++;
      delay(30);
      if(nTemp == 20){ Count_lines(true,0); }
    }
    if( nTemp == 20 && Count_lines(false,SensorMin) == Line_Counts)  
    {
      break;      
    }
    Go_straight(100);
  }
}
void Arrive_Blue()
{
  delay(100);
  while(1)
  { 
    if(digitalRead(SensorMin) == HIGH)  
    {
      brake(1,0);
      break;
    }
    Go_straight(100);
  }           //到达左转位置
  spin_left_first(); 
  delay(100);
  Count_lines(true,0);
  while(1)
  {
     if(Count_lines(false,SensorLeft) == 1)  
    {
      brake(1,0);
      break;
    }
  }  //左转完成
  Count_lines(true,0);
  while(1)
  {
    if(Count_lines(false,SensorMin) == 1)  
    {
      brake(1,0);
      break;
    }
    Go_straight(100);
  }  //前进完成
  int nTemp = 0;
  while(1)
  { 
    if(nTemp < 30)
    {
      nTemp++;
      delay(30);
      if(nTemp == 30){ Count_lines(true,0); }
    }
    if( nTemp == 30 && Count_lines(false,SensorMin) == 3)  
    {
      brake(2,0);
      break;
    }
    back_straight();
  }
}
void Back_to_AA(int QR_code)
{
  int Lines = 3;
  int nTemp = 20;
  if(QR_code == 2)
  {
    nTemp = 0;
    Lines = 1;    
  }    
  Count_lines(true,0);
  while(1)
  { 
    if(nTemp < 20)
    {
      nTemp++;
      delay(30);
      if(nTemp == 20){ Count_lines(true,0); }
    }
    if(nTemp == 20 && Count_lines(false,SensorMin) == Lines)  
    {
      digitalWrite(Left_motor,LOW);
      digitalWrite(Right_motor,LOW);
      digitalWrite(Right_motor_pwm,255);   
      digitalWrite(Left_motor_pwm,255);  
      delay(70);
      analogWrite(Right_motor_pwm,0);
      analogWrite(Left_motor_pwm,0);
      break;
    }
    back_straight();
  }
}
void Go_Home()
{
  back(80);
  Count_lines(true,0);
  while(1)
  {
     if(Count_lines(false,SensorMin) == 1)  
    {
      brake(2,0);
      break;
    }
  }  //后退完成
  spin_left_first(); 
  delay(200);
  Count_lines(true,0);
  while(1)
  {
     if(Count_lines(false,SensorLeft) == 1)  
    {
      brake(1,0);
      break;
    }
  }  //左转完成
  delay(100);
  Green_to_Red(3); //前进完成
  brake(1,0);
  spin_left_first(); 
  delay(200);
  Count_lines(true,0);
  while(1)
  {
     if(Count_lines(false,SensorLeft) == 1)  
    {
      brake(1,0);
      break;
    }
  }  //左转完成
  Green_to_Red(2); //前进完成
  brake(1,0);
  spin_right();
  delay(500);
  motor_run(0,120);
  delay(500);
  brake(1,0);
}
