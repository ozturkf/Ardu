#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;

int sax;
int say;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(4000);   // Bits per sec
  Serial.begin(9600);
}



void loop()
{
    int say = constrain(map(analogRead(A1),100,1000,0,90),0,90);
    int sax = constrain(map(analogRead(A2),100,1000,0,90),0,90);
  char msg[2] = {sax,say};


  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.print(msg);
  digitalWrite(led_pin, LOW);
  delay(500);
}
