
/*
Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
For more information visit my blog: http://blog.tkjelectronics.dk/ or 
send me an e-mail:  kristianl@tkjelectronics.com
*/
#include <Servo.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <settings.h>

USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
PS3BT PS3(&Btd,0xF0,0x65,0xDD,0x64,0x08,0x8C); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

//Servo servo1;
Servo sNose;
Servo sRight;
Servo sTail;
Servo sLeft;

int thrust;
int thrustt;
int thrusttt;
int pitch;
int roll;
boolean printTemperature;
boolean printAngle;

void setup() {
             Serial.begin(115200);
             while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
             if (Usb.Init() == -1) {
                                     Serial.print(F("\r\nOSC did not start"));
                                     while(1); //halt
                                   }
             Serial.print(F("\r\nPS3 Bluetooth Library Started"));
             pinMode(3, OUTPUT);
             pinMode(5, OUTPUT);
             pinMode(6, OUTPUT);
             pinMode(4, OUTPUT);
 
 
             sNose.attach(3);
             sRight.attach(5);
             sTail.attach(6);
             sLeft.attach(4);
           }
           
void loop() {
             Usb.Task();

             if(PS3.PS3Connected || PS3.PS3NavigationConnected) 
               {
                thrust=map(PS3.getAnalogHat(LeftHatY), 0, 255, 163, 90);
                thrustt=map(PS3.getAnalogHat(LeftHatY), 0, 255, 163, 90);
                thrusttt=map(PS3.getAnalogHat(LeftHatY), 0, 255, 163, 90);
                pitch=map(PS3.getAnalogHat(RightHatY), 0, 255, 1, -1);
                roll=map(PS3.getAnalogHat(RightHatX), 0, 255, 1, -1);
                 
                  
                  
                  sNose.write(thrust-pitch);
                  sRight.write(thrustt+roll);
                  sTail.write(thrusttt+pitch);
                  sLeft.write(thrust-roll);
     

   
 }
 else 
  {
 
   sNose.write(90);
   sRight.write(90);
   sTail.write(90);
   sLeft.write(90);
  }
   
   if(PS3.getButtonClick(PS)) {
     PS3.disconnect();
  }
   
 }
