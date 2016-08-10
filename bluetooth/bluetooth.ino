
void setup()  
{
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  // set the data rate for the SoftwareSerial port
  Serial.begin(9600);
  // Send test message to other device
  Serial.println("Hello from Arduino");
}
char a; // stores incoming character from other device
void loop() 
{
  if (Serial.available())
  // if text arrived in from BT serial...
  {
    a=(Serial.read());
    if (a=='1')
    {
      digitalWrite(13, HIGH);
      Serial.println("LED on");
    }
    if (a=='2')
    {
      digitalWrite(13, LOW);
      Serial.println("LED off");
    }
    if (a=='?')
    {
      Serial.println("Send '1' to turn LED on");
      Serial.println("Send '2' to turn LED on");
    }   
    // you can add more "if" statements with other characters to add more commands
  }
}
