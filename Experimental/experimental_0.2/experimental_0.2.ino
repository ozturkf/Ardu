#include <Servo.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <settings.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

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

int thrust, pitch, roll, gyrox, gyroy;

boolean printTemperature;
boolean printAngle;

int buffersize=10;     //Amount of readings used to average, make it higher to get more precision but sketch will be slower  (default:1000)
int acel_deadzone=8;     //Acelerometer error allowed, make it lower to get more precision, but sketch may not converge  (default:8)
int giro_deadzone=4;     //Giro error allowed, make it lower to get more precision, but sketch may not converge  (default:1)

MPU6050 accelgyro(0x68); 

int16_t ax, ay, az,gx, gy, gz;

int mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz,state=0;
int ax_offset,ay_offset,az_offset,gx_offset,gy_offset,gz_offset;

///////////////////////////////////   FUNCTIONS   ////////////////////////////////////
void meansensors(){
  long i=0,buff_ax=0,buff_ay=0,buff_az=0,buff_gx=0,buff_gy=0,buff_gz=0;

  while (i<(buffersize+101)){
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    if (i>100 && i<=(buffersize+100)){ //First 100 measures are discarded
      buff_ax=buff_ax+ax;
      buff_ay=buff_ay+ay;
      buff_az=buff_az+az;
      buff_gx=buff_gx+gx;
      buff_gy=buff_gy+gy;
      buff_gz=buff_gz+gz;
    }
    if (i==(buffersize+100)){
      mean_ax=buff_ax/buffersize;
      mean_ay=buff_ay/buffersize;
      mean_az=buff_az/buffersize;
      mean_gx=buff_gx/buffersize;
      mean_gy=buff_gy/buffersize;
      mean_gz=buff_gz/buffersize;
    }
    i++;
    delay(2); //Needed so we don't get repeated measures
  }
}

void calibration(){
  ax_offset=-mean_ax/8;
  ay_offset=-mean_ay/8;
  az_offset=(16384-mean_az)/8;

  gx_offset=-mean_gx/4;
  gy_offset=-mean_gy/4;
  gz_offset=-mean_gz/4;

  while (1){
    int ready=0;
    accelgyro.setXAccelOffset(ax_offset);
    accelgyro.setYAccelOffset(ay_offset);
    accelgyro.setZAccelOffset(az_offset);

    accelgyro.setXGyroOffset(gx_offset);
    accelgyro.setYGyroOffset(gy_offset);
    accelgyro.setZGyroOffset(gz_offset);

    meansensors();
    Serial.println("...");

    if (abs(mean_ax)<=acel_deadzone) ready++;
    else ax_offset=ax_offset-mean_ax/acel_deadzone;

    if (abs(mean_ay)<=acel_deadzone) ready++;
    else ay_offset=ay_offset-mean_ay/acel_deadzone;

    if (abs(16384-mean_az)<=acel_deadzone) ready++;
    else az_offset=az_offset+(16384-mean_az)/acel_deadzone;

    if (abs(mean_gx)<=giro_deadzone) ready++;
    else gx_offset=gx_offset-mean_gx/(giro_deadzone+1);

    if (abs(mean_gy)<=giro_deadzone) ready++;
    else gy_offset=gy_offset-mean_gy/(giro_deadzone+1);

    if (abs(mean_gz)<=giro_deadzone) ready++;
    else gz_offset=gz_offset-mean_gz/(giro_deadzone+1);

    if (ready==6) break;
  }
}
///////////////////////////////////   SETUP   ////////////////////////////////////
void setup() {
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz). Leonardo measured 250kHz.

  accelgyro.initialize();
  while (Serial.available() && Serial.read()); // empty buffer
  delay(1000);
  Serial.println("\nYour MPU6050 should be placed in horizontal position, with package letters facing up. \nDon't touch it until you see a finish message.\n");
  delay(1000);
  // verify connection
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  delay(500);
  
  if (state==0){
    Serial.println("\nReading sensors for first time...");
    meansensors();
    state++;
    delay(500);
  }

  if (state==1) {
    Serial.println("\nCalculating offsets...");
    calibration();
    state++;
    delay(1000);
  }

  if (state==2) {

             pinMode(6, OUTPUT);
             pinMode(7, OUTPUT);
             pinMode(8, OUTPUT);
             pinMode(9, OUTPUT);
 
 
             sNose.attach(6);
             sRight.attach(7);
             sTail.attach(8);
             sLeft.attach(9);

    
  }
    
}

///////////////////////////////////   LOOP   ////////////////////////////////////
void loop() {
            Usb.Task();

             if(PS3.PS3Connected || PS3.PS3NavigationConnected) 
               {
                            thrust=map(PS3.getAnalogHat(LeftHatY), 0, 255, 159, 90);
                            pitch=map(PS3.getAnalogHat(RightHatY), 0, 255, 5, -5);
                            roll=map(PS3.getAnalogHat(RightHatX), 0, 255, 5, -5);
                            gyrox=map(gx, -250, 250, -10, 10) ; 
                            gyroy=map(gy, -250, 250, -10, 10);
              
              
                            sNose.write(thrust+gyroy-pitch);
                            sRight.write(thrust-gyrox+roll);
                            sTail.write(thrust+gyroy+pitch);
                            sLeft.write(thrust-gyrox-roll);
               
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

