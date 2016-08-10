#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;

int sax,say,sol;

char msg[20];
void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(4000);   // Bits per sec
  Serial1.begin(9600);
}



void loop()
{
    int say = constrain(map(analogRead(A1),840,160,-90,90),-100,100);
    int sax = constrain(map(analogRead(A2),840,160,-90,90),-100,100);
    int sol = constrain(map(analogRead(A3),840,160,0,180),0,170);
sprintf(msg, "%d,%d,%d.",sax,say,sol);

  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.print(msg);
  Serial.println();
  digitalWrite(led_pin, LOW);
  delay(20);
}
