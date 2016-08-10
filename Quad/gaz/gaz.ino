
#include <Servo.h>



Servo sRight;

Servo sLeft;
int sax,say,sol;
int thrust;
int pitch;
int roll;
const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
int pos=0;
void setup()
{
  
             sLeft.attach(4);
             sRight.attach(5);
            
             

                for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    
    sRight.write(pos);
   
    sLeft.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

                }
                 
                 }

void loop()
{
  
  
  

                 
                  sRight.write(120);
                  
                  sLeft.write(170);
                
                  
  
    }

