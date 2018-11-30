int left_full=250;
int right_full=250;
int left_now;
int right_now;
int ifs=0;
double coco=0;
char asd[100];
char asd1[100];
double hightotal;
double hightotal1;
double highindex=0;
double highindex1=0;
int left=0;
int right=0;
int c=0;
double change;
double total;
double total1;
int start=1;
int inde=0;
void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL1V1);
   Serial.begin(9600); 
   //setP16( );   // Prescaler = 16
  //setP128( ); // Prescaler = 128 = default
   left_now=left_full;
   right_now=right_full;
    analogWrite(9, 0);//9 ports use for left pwm
  analogWrite(10, 0);//10 ports use for right pwm
  /*
  for(int j=0;j<5;j++)
  {
    total=0;
    total1=0;
    hightotal=0;
    hightotal1=0;
    for(int i=0;i<100;i++)
    {
       asd1[i] = analogRead(A1);
       asd[i] = analogRead(A0);
       total+=asd[i];
       total1+=asd1[i];
    }
    total=total/100;
    total1=total1/100;
    for(int i=0;i<100;i++)
    {
      hightotal+=(total-asd[i])*(total-asd[i]);
      hightotal1+=(total1-asd1[i])*(total1-asd1[i]);
    }
   //  Serial.print("all is ");
       //Serial.println(highindex);
       hightotal/=10;
       hightotal1/=10;
       hightotal=abs(hightotal);
       hightotal1=abs(hightotal1);
       coco+=hightotal-hightotal1;
  }
  
  coco/=5*/
  coco=0;
  Serial.println("coco");  // 100
  
  Serial.println(coco);  // 100
  
}
void setP16( ) {
  Serial.println("ADC Prescaler = 16");  // 100
  ADCSRA |=  (1 << ADPS2);   // 1
  ADCSRA &=  ~(1 << ADPS1);  // 0
  ADCSRA &=  ~(1 << ADPS0);  // 0
}
void loop() {
  // put your main code here, to run repeatedly:
  
   if (Serial.available() > 0) {
              // read the incoming byte:
              inde = Serial.parseInt();
              if(inde==0)
              {
                if(start==0)
                {
                  start=1;
                }
                else
                {
                  start=0;
                }
              }
              
      }
  total=0;
  total1=0;
  hightotal=0;
  hightotal1=0;
  highindex=0;
  highindex1=0;
  for(int i=0;i<100;i++)
  {
     asd1[i] = analogRead(A1);
     asd[i] = analogRead(A0);
     total+=asd[i];
     total1+=asd1[i];
  }
  total=total/100;
  total1=total1/100;
  for(int i=0;i<100;i++)
  {
    hightotal+=(total-asd[i])*(total-asd[i]);
    hightotal1+=(total1-asd1[i])*(total1-asd1[i]);
  }
 //  Serial.print("all is ");
     //Serial.println(highindex);
     hightotal/=10;
     hightotal1/=10;
     hightotal=abs(hightotal);
     hightotal1=abs(hightotal1);
     change=hightotal-hightotal1;
     //hightotal1+=18;
     
  Serial.print(hightotal);
  Serial.print("   ");
  Serial.print(hightotal1);
  Serial.print("   ");
  Serial.print(change);
//  if(hightotal>39&&hightotal1<26)
//  {
//    Serial.println("   right");
//  }
//  else if(hightotal<37&&hightotal1>27)
//  {
//    Serial.println("   left");
//  }
//  else if(hightotal>47)
//  {
//    Serial.println("   right super");
//  }
//  else if(hightotal1>30)
//  {
//    Serial.println("   left super");
//  
//  }
  if(change>coco+1.5)
  {
     if(right_now==right_full)
     {
       left_now-=40;
       if(left_now<0)
       {
         left_now=0;
       }
     }
     else
     {
       right_now+=40;
       if(right_now>right_full)
       {
         right_now=right_full;
       }
     }
     Serial.print("   ");
     Serial.print(left_now);
     Serial.print("   ");
     Serial.print(right_now);
     Serial.print("   left");
  }
  else if(change<coco-1.5)
  {
    if(left_now==left_full)
     {
       right_now-=40;
       if(right_now<0)
       {
         right_now=0;
       }
     }
     else
     {
       left_now+=40;
       if(left_now>left_full)
       {
         left_now=left_full;
       }
     } 
     Serial.print("   ");
     Serial.print(left_now);
     Serial.print("   ");
     Serial.print(right_now);
     Serial.print("   right");
  }
  else
  {
    
    if(right_now!=right_full)
    {
      right_now+=5;
    }
    else
    {
      left_now+=5;
    }
    if(right_now>right_full)
    {
      right_now=right_full;
    }
    if(left_now>left_full)
    {
      left_now=left_full;
    }
    Serial.print("   ");
    Serial.print(left_now);
    Serial.print("   ");
    Serial.print(right_now);
    Serial.print("   ");
  }
  
  if(start==0)
  {
    analogWrite(9, 0);//9 ports use for left pwm
    analogWrite(10, 0);//10 ports use for right pwm
     Serial.println("   c");
    
  }
  else
  {
    if(ifs%5<1)
    {
      if(left_now<(left_full*14/15))
      {  
        analogWrite(9, 0);//9 ports use for left pwm
        analogWrite(10, right_now);//10 ports use for right pwm
      }
      else if(right_now<(right_full*14/15))
      {
        analogWrite(9, left_now);//9 ports use for left pwm
        analogWrite(10, 0);//10 ports use for right pwm
      }
      else
      {
        analogWrite(9, left_now);//9 ports use for left pwm
        analogWrite(10, right_now);//10 ports use for right pwm
      }
    }
    else
    {
      analogWrite(9, 0);//9 ports use for left pwm
      analogWrite(10, 0);//10 ports use for right pwm
    }
    ifs++;
    Serial.println("   o");
  }
//  if(hightotal>hightotal1)
//  {
//    change=hightotal-hightotal1;
//    analogWrite(9, left_full);//9 ports use for left pwm
//    analogWrite(10, right_full-change*80);
//  }
//  else
//  {
//    change=hightotal-hightotal1;
//    analogWrite(9, left_full-change*80);
//    analogWrite(10, right_full);
//  }
   // Serial.println(total);
   //  Serial.print(",");
   
}




