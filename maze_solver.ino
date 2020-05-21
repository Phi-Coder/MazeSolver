#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int LS1=13; //
int LS2=14; // 
int RS1=12; //
int RS2=4; //
int MS1=8; // 8
int MS2=7; 
int FP=15;
int EML=10; //enable motor left(motor connection to motor driver)  //WHITE
int EMR=11;// enable motor right   //GREY
int inp_1=6; //6            //input 1 for left motor terminal 1      //BlACK
int inp_2=3;// input 2 for left motor terminal 2    //ORANGE
int inp_3=5;// input 3 for right motor terminal 1   //RED
int inp_4=9;// input  4 for right motor terminal 2   //BROWN
int i=0;
char dr[150];
char sp[100];
int led = 16;//led 

void motor_straight() //motor will move forward
{
  digitalWrite(inp_1,HIGH);//left motor terminal 1 positive
  digitalWrite(inp_2,LOW);//left motor terminal 2 negative
  analogWrite(EML,69);//pwm speed 167 for left motor
  digitalWrite(inp_3,HIGH);//right motor terminal 1 positive
  digitalWrite(inp_4,LOW);//right motor terminal 2 negative
  analogWrite(EMR,69);//pwm speed 167 for right motor
}

void motor_uturn() //right motor will stop while left motor moves forward about 167 degree making a uturn
{
  digitalWrite(inp_1,LOW);//left motor terminal 1 positive
  digitalWrite(inp_2,HIGH);//left motor terminal 2 negative
  analogWrite(EML,71);
  digitalWrite(inp_3,HIGH);//right motor terminal 1 low
  digitalWrite(inp_4,LOW);//right motor terminal 2 low
  analogWrite(EMR,71); //or no speed 
}

void motor_left() //left motor will stop while right motor moves forward making a left turn about the axis of wheel
{
  digitalWrite(inp_1,LOW);//left motor terminal 1 low
  digitalWrite(inp_2,HIGH);//left motor terminal 2 low
  analogWrite(EML,71);
  digitalWrite(inp_3,HIGH);//right motor terminal 1 positive
  digitalWrite(inp_4,LOW);//right motor terinal 2 negative
  analogWrite(EMR,71);
}

void motor_right() //right motor will stop while left motor moves forward making a right turn about the axis of wheel
{
  digitalWrite(inp_1,HIGH);//left motor terminal 1 positive
  digitalWrite(inp_2,LOW);//left motor terminal 2 negative
  analogWrite(EML,71);//pwm speed is 67
  digitalWrite(inp_3,LOW);//right motor terminal 1 low
  digitalWrite(inp_4,LOW);//right motor terminal 2 low
  analogWrite(EMR,71);//pwm speed is 67
}

void motor_stop() //both left and right motor stops
{
  digitalWrite(inp_1,LOW);
  digitalWrite(inp_2,LOW);
  digitalWrite(inp_3,LOW);
  digitalWrite(inp_4,LOW);
}

void setup() 
{
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  
  pinMode(LS2,INPUT);   //extreme left sensor
  pinMode(LS1,INPUT);   //left sensor
  pinMode(MS1,INPUT);   //centre middle sensor
  pinMode(MS2,INPUT);   //centre forward middle sensor
  pinMode(RS1,INPUT);   //right sensor
  pinMode(RS2,INPUT);   //extreme right sensor
  pinMode(FP,INPUT);    //final point sensor
  pinMode(inp_1,OUTPUT);   //left motor terminal 1
  pinMode(inp_2,OUTPUT);   //left motor terminal 2
  pinMode(inp_3,OUTPUT);   //right motor terminal 1
  pinMode(inp_4,OUTPUT);   //right motor terminal 2
  pinMode(EML,OUTPUT); //enable motor left
  pinMode(EMR,OUTPUT); //enable motor right
  pinMode(led,OUTPUT);
}
// 0 = white , 1 = black

void loop() {
    if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(MS2)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0 && digitalRead(FP)==0 )
    //10)stop or end
    {
     motor_stop();
     digitalWrite(led,HIGH);
     delay(1000);
     digitalWrite(led,LOW);
     lcd.clear();
     for(i=0;i<150;i++)
     {
      lcd.print(dr[i]);
     }
    }
  
    //11011
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //1)straight conition(only middle sensors will sense white line)
    {
     motor_straight(); 
     dr[i]='S';
     lcd.print("S");
     lcd.setCursor(0,0);
     i++;
     }
         
    //00011
    else if(digitalRead(LS2)== 0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //2)direct left turn
    {
     motor_left();
     dr[i]='L';
     lcd.print("L");
     lcd.setCursor(0,1);
     i++;
    }
    
    //11000 //
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(MS2)==1 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //3)direct right turn
    {
     motor_right();
     dr[i]='R';
     lcd.print("R");
     lcd.setCursor(0,3);
     i++;
    }
     
    //00000 //&& digitalRead(MS2)==1
    else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //6)straigth T turn
    {
     motor_left();
     dr[i]='L';
     lcd.print("L");
     lcd.setCursor(0,4);
     i++;
    }
    
    //000110
    else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(MS2)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
    //5)left T turn
    {
     motor_left();
     dr[i]='L';
     lcd.print("L");
     lcd.setCursor(0,5);
     i++; 
    }
    
    //110000
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(MS2)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //8)right T turn
    {
     motor_straight();
     dr[i]='S';
     lcd.print("S");
     lcd.setCursor(0,6);
     i++;
    }
    
    //111110
    else if(digitalRead(LS2)==1 &&  digitalRead(LS1)==1 && digitalRead(MS1)== 1 && digitalRead(MS2)==0 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
                                                       //digitalRead(MS1)==0 or digitalRead(MS2)== 0
    //4)line break
    {
     motor_straight();
     dr[i]='S';
     lcd.print("S");
     lcd.setCursor(0,7);
     i++;
    }  
    
    //111111
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==1 && digitalRead(MS2)==1 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //7)dead end
    {
     motor_uturn();
     dr[i]='B';
     lcd.print("B");
     lcd.setCursor(0,8);
     i++;
    }
    
    //00000 //digitalRead(MS2) ==0
    else if(digitalRead(LS1)==0 && digitalRead(LS2)==0 && digitalRead(MS1)==0 && digitalRead(MS2) ==0 &&  digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //9)plus turn or chaurayaa
    {
      while(digitalRead(LS2)== 1 &&digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
      {
        while(digitalRead(LS2)== 1 &&digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
        {
          while(digitalRead(LS2)== 0 &&digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
          {
           motor_left();  
          }
          motor_left(); 
        }
       motor_left(); 
      }
     motor_left();
     dr[i]='L';
     lcd.print("L");
     lcd.setCursor(0,9);
     i++;
    }
    
    //00100  ******
     else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==1 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //deflection towards left sensor 
    {
      motor_left(); 
    }
    
    //0010   ******
     else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==1 && digitalRead(RS1)==0 )
    //deflection towards left sensor 
    {
      motor_left(); 
    }
    
    //001_0
     else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==1 && digitalRead(RS2)==0 )
    //deflection towards left sensor 
    {
      motor_left(); 
    }
      
    //1110 ** //
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==1 && digitalRead(RS2)==0)
    //10)deflection towards extreme left 
    {
     motor_right();
    } 
//*******    
    
    //10111 **   
     else if(digitalRead(LS2)==1 && digitalRead(LS1)==0 && digitalRead(MS1)==1 && digitalRead(RS1)==1&& digitalRead(RS2)==1)
    //deflection towards left sensor 
    {
      motor_left(); 
    }  
    
    //0111   **
    else if(digitalRead(LS2)==0 && digitalRead(MS1)==1 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //10)deflection towards extreme right
    {
      motor_left();
    }
    
    //1100 **
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(RS1)==0)
    //deflection towards left sensor 
    {
     motor_right();
    }   
                                 
    //11100 **
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==1 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //10)deflection
    {
     motor_right();
    }   
        
    //1100
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(RS2)==0)
    //10)deflection
    {
     motor_right();
    }   
    
    //10001
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
    //10)deflection
    {
     motor_left();
    }   

    //00111
    else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==1 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //10)deflection
    {           
     motor_left();
    }   
              
    //10011 ************
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==1 && digitalRead(RS2)==1)
    //deflection
    {
     motor_left();
    } 
    
    //11001
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==1 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
    //deflection  
    {
     motor_right();
    }
    
    else if(digitalRead(LS2)==1 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(MS2)==1 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //deflection  
    {     
     while(digitalRead(LS2)== 1&&digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
     {
      motor_right();
     while(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(MS2)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
     {
      motor_right();
     }
     }
     motor_right();
    }        
       
    //10000  ****
    else if(digitalRead(LS2)== 1&&digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==0)
    //deflection
    {
     motor_left();
    }
    
    //00001  ****
    else if(digitalRead(LS2)==0 && digitalRead(LS1)==0 && digitalRead(MS1)==0 && digitalRead(RS1)==0 && digitalRead(RS2)==1)
    //deflection   
    {
     motor_left();
    } 
                 
    //0000000
    
    else
    {
     motor_straight();
    }
}
