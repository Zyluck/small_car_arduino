//读取颜色,二维码
int get_Colour() 
{
  int _nTemp = 0;
  char Buffer[5] = {0};
  while(!Serial.available());
  for(int i=0;i<3;i++)
  {
    Buffer[i] = Serial.read();
    delay(3);
  }
  //Serial.println(Buffer);     
  _nTemp = atoi(Buffer);
  return _nTemp;
}
int get_QRcode() 
{
  int _nTemp = 0;
  int Delay_temp = 0;
  char Buffer[5] = {0};
  delay(300);
   while(!Serial2.available())
   {
      delay(30);
       if(Delay_temp < 40)
       {
          motor_run(0,53);
          Delay_temp++;
       }
       else
       {
        back(53);
        Delay_temp++;
        if(Delay_temp == 80)
        {
          Delay_temp = 0;
        }
       }
   }
   brake(1,0);
   for(int i=0;i<3;i++)
   {
     Buffer[i] = Serial2.read();
     if(Buffer[i] == 0)
     i--;
     delay(3);
    }
  _nTemp = atoi(Buffer);
  lcd.setCursor(0, 0);
  lcd.print(_nTemp);     
  return _nTemp;
}
