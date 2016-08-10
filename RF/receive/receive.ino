#include <VirtualWire.h>




const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup()
{
   
             

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(4000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
  // Message with a good checksum received, print it.
  Serial.print("Got: ");
  
  for (i = 0; i < buflen; i++)
  {
    Serial.print(buflen);
       Serial.print(buf[i]);
      Serial.print(' ');
  }
 
  Serial.println();
        digitalWrite(led_pin, LOW);
    }


}