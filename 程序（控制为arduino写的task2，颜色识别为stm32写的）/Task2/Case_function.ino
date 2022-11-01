//抓夹装置
void Switch_Material(int QR_First,int Colour_code)
{
  int nTemp = 0;
  if(QR_First ==  Colour_code / 100)
  {
       while(1)
      {
        nTemp++;
        Go_straight(100);
        if( nTemp == 30 )
        {
          brake(1,0);
          break;
        }
        delay(10);
      }
      Catch_Right();
  }
  else if(QR_First ==  (Colour_code / 10 % 10) )
  {
       while(1)
      {
        nTemp++;
        Go_straight(100);
        if( nTemp == 35 )
        {
          brake(1,0);
          break;
        }
        delay(10);
      }
      Catch_Min();
  }
  else if(QR_First ==   Colour_code % 10)
  {
       while(1)
      {
        nTemp++;
        Go_straight(100);
        if( nTemp == 30 )
        {
          brake(1,0);
          break;
        }
        delay(10);
      }
      Catch_Left();
  }
  else
  {
    while(1);
  }
  return ;
}
void Put_Material(int QR_First)
{
  if(QR_First == 1)
  {
      while(1)
      {
        Go_straight(100);
        if( digitalRead(SensorRight)==HIGH && digitalRead(SensorLeft)==HIGH )
        {
          brake(1,100);
          delay(100);
          back(100);
          while(1)
          {
            if(digitalRead(SensorRight)==HIGH)
              break;
          }
          delay(100);
          brake(2,0);          
          break;
        }
      }
      Put_Left();
  }
  else if(QR_First == 2)
  {
        Put_Min();
  }
  else if(QR_First == 3)
  {
      while(1)
      {
        Go_straight(100);
        if( digitalRead(SensorRight)==HIGH && digitalRead(SensorLeft)==HIGH )
        {
          brake(1,100);
          break;
        }
      }
      Put_Right();
  }
}
