#include <VirtualWire.h>
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
            
             

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(4000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
Serial.begin(9600);
                 
                for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    
    sRight.write(pos);
   
    sLeft.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  
                }
                 
                 }

void loop()
{
  
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
     
    sscanf ((char*)buf, "%d%*c%d%*c%d", &sax, &say, &sol);
    digitalWrite(led_pin, HIGH); // Flash a light to show received good message
sax=sax/5;
say=say/5;
sol=constrain(sol,0,180);
 
                 
                  sRight.write(sol-sax);
                  
                  sLeft.write(sol+sax);
                  delay(20);
                 
  }
  else
  {
    
                
                  sRight.write(90);
                 
                  sLeft.write(90);
                  delay(20);
                  
  }               
  
  
        digitalWrite(led_pin, LOW);
    }

