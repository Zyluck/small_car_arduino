//机械臂
#include <Servo.h>
Servo Servo_Stage;    
Servo Servo_Arm;      //
Servo Servo_Arm2;      //
Servo Servo_Claw;     //

#define INIT_ARM 58
#define INIT_ARM2 150
#define INIT_STAGE 12
#define INIT_CLAW 3

#define Catch_ARM2 180
#define Put_ARM2 156

#define Catch_ARM 67
#define Catch_CLAW 117

#define Catch_Left_STAGE 0
#define Catch_Right_STAGE 28
#define Catch_Min_STAGE 12

#define Put_ARM 55
#define Put_CLAW 117

#define Put_Min_STAGE 144
#define Put_Left_STAGE 180
#define Put_Right_STAGE 96

void Put_Right()
{
    Change_Stage(Put_Right_STAGE,5);
    Change_Arm(Put_ARM,5);
    Change_Claw(Put_CLAW,8);
    Change_Arm2(Put_ARM2,5);
    ServoInit2();
}
void Catch_Right()
{
    Change_Arm(Catch_ARM,5);
    Change_Stage(Catch_Right_STAGE,5);
    Change_Claw(Catch_CLAW,8);
    Change_Arm2(Catch_ARM2,5);
    Change_Claw(INIT_CLAW,5);
    Change_Stage(INIT_STAGE,5);
}
void Put_Left()
{
    Change_Stage(Put_Left_STAGE,5);
    Change_Arm(Put_ARM,5);
    Change_Claw(Put_CLAW,8);
    Change_Arm2(Put_ARM2,5);
    ServoInit2();
}
void Catch_Left()
{
    Change_Arm(Catch_ARM,5);
    Change_Stage(Catch_Left_STAGE,5);
    Change_Claw(Catch_CLAW,8);
    Change_Arm2(Catch_ARM2,5);
    Change_Claw(INIT_CLAW,5);
    Change_Stage(INIT_STAGE,5);
}
void Put_Min()
{
    Change_Arm(Catch_ARM,5);
    Change_Stage(Put_Min_STAGE,5);
    Change_Claw(Put_CLAW,8);
    Change_Arm2(Put_ARM2,5);
    ServoInit2();
}
void Catch_Min()
{
    Change_Stage(Catch_Min_STAGE,5);
    Change_Claw(Catch_CLAW,8);
    Change_Arm2(Catch_ARM2,5);
    Change_Claw(INIT_CLAW,5);
}
void ServoInit2()
{  
    Change_Arm2(141,5);
    Change_Arm(Catch_ARM,5);
    Change_Claw(INIT_CLAW,5);
    Change_Stage(Catch_Min_STAGE,5);
}
void Change_Stage(int angle,int delay_time)
{
  for(int i=Servo_Stage.read();i != angle; )
  {
    if(i > angle) i--;
    else i++;
    Servo_Stage.write(i);
    delay(delay_time);
  } 
}
void Change_Arm(int angle,int delay_time)
{
  for(int i=Servo_Arm.read();i != angle; )
  {
    if(i > angle) i--;
    else i++;
    Servo_Arm.write(i);
    delay(delay_time);
  } 
}
void Change_Arm2(int angle,int delay_time)
{
  for(int i=Servo_Arm2.read();i != angle; )
  {
    if(i > angle) i--;
    else i++;
    Servo_Arm2.write(i);
    delay(delay_time);
  } 
}
void Change_Claw(int angle,int delay_time)
{
  for(int i=Servo_Claw.read();i != angle; )
  {
    if(i > angle) i--;
    else i++;
    Servo_Claw.write(i);
    delay(delay_time);
  } 
}
void ServoInit()
{
  Servo_Stage.attach(2); //
  Servo_Arm.attach(7);
  Servo_Arm2.attach(46);
  Servo_Claw.attach(12);
  
  Servo_Arm.write(INIT_ARM);
  Servo_Arm2.write(80);
  Servo_Stage.write(INIT_STAGE);
  Servo_Claw.write(INIT_CLAW); //
}
//void setup2()
//{
//  ServoInit();
//  Serial.begin(9600);
//  while (Serial.read() >= 0) {} //
//  
//  Serial2.begin(9600);
//  while (Serial1.read() >= 0) {} //
//}
//void loop3()
//{
//  int nTemp = 0;
//  while(!Serial.available());
//  char chTemp = Serial.read();
//  Serial.print(chTemp); 
//  switch(chTemp)
//  {
//    case '1':
//        nTemp = Servo_Stage.read();nTemp += 3;
//        Servo_Stage.write(nTemp);
//      break;
//    case '2':
//       nTemp = Servo_Stage.read();nTemp -= 3;
//       Servo_Stage.write(nTemp);
//      break;
//      
//    case '3':
//        nTemp = Servo_Arm.read();nTemp += 3;
//        Servo_Arm.write(nTemp);
//      break;
//    case '4':
//       nTemp = Servo_Arm.read();nTemp -= 3;
//       Servo_Arm.write(nTemp);
//      break;
//      
//    case '5':
//        nTemp = Servo_Arm2.read();nTemp += 3;
//        Servo_Arm2.write(nTemp);
//      break;
//    case '6':
//       nTemp = Servo_Arm2.read();nTemp -= 3;
//       Servo_Arm2.write(nTemp);
//      break;
//      
//    case '7':
//        nTemp = Servo_Claw.read();nTemp += 3;
//        Servo_Claw.write(nTemp);
//      break;
//    case '8':
//       nTemp = Servo_Claw.read();nTemp -= 3;
//       Servo_Claw.write(nTemp);
//      break;
//    case '9':
//          Serial.print("Stage:"); Serial.print(Servo_Stage.read()); 
//          Serial.print("Arm:"); Serial.print(Servo_Arm.read()); 
//          Serial.print("Arm2:"); Serial.print(Servo_Arm2.read()); 
//          Serial.print("Claw:"); Serial.print(Servo_Claw.read());  
//      break;
//  }
//}
