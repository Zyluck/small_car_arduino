//定义元件端口
int beep = A3;    //蜂鸣器
#include <LiquidCrystal.h>
//LiquidCrystal lcd(22, 23, 24, 25, 26, 27);    //液晶显示屏
void beep_500()   //
{
    digitalWrite(beep,HIGH);
    delay(500);
    digitalWrite(beep,LOW);
}
//初始化
void setup() {
    Serial.begin(9600);   //串口初始化
  while (Serial.read() >= 0) {} //
  Serial2.begin(9600);
  while (Serial1.read() >= 0) {} //
  ServoInit();//舵机初始化
  Motorinit();//电机初始化
//  lcd.begin(16, 2);
//  lcd.clear();//液晶屏初始化 
}
//按键启动
void loop2()
{
  keysacn();
  int nColour = get_Colour(); 
}
//物料颜色识别，抓取，运送
void loop() 
{
  keysacn();//看basic
  Go_Out();//看task
  Stop_on_QRCode();
  ServoInit2();
  int nQR_code = get_QRcode();
  back_to_Material_Area();
  int nColour = get_Colour();
  Arrive_Blue();

  int QR_code_Ary[3];
  QR_code_Ary[0] = nQR_code / 100;
  QR_code_Ary[1] = nQR_code / 10 % 10;
  QR_code_Ary[2] = nQR_code % 10;
  
  for(int i=0;i<3;i++)
  {
    Switch_Material( QR_code_Ary[i] , nColour);//选择抓取材料
    if(QR_code_Ary[i] == 2)
    {
      Green_to_Red(1);
      brake(1,0);   
    }
    else 
    {
      Green_to_Red(2);
    }
    Put_Material(QR_code_Ary[i]);
    if(i == 2)
    {
      Go_Home();
      beep_500();
      break;  
    }     
    Back_to_AA(QR_code_Ary[i]);
  }
}
