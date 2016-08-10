/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <SoftwareServo.h>

SoftwareServo dort;
SoftwareServo bes;
SoftwareServo alti;
SoftwareServo yedi;// create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  dort.attach(4);  // attaches the servo on pin 9 to the servo object
bes.attach(5);
alti.attach(6);  // attaches the servo on pin 9 to the servo object
yedi.attach(7);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    dort.write(pos);
    bes.write(pos);
    alti.write(pos);
    yedi.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  SoftwareServo::refresh();
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    dort.write(pos);
    bes.write(pos);// tell servo to go to position in variable 'pos'
    alti.write(pos);
    yedi.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  SoftwareServo::refresh();
  }
}

