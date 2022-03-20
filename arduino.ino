#include <SPI.h>

char buff [100];
volatile byte index;
volatile bool receivedone;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
SPCR |= bit(SPE);         /* Enable SPI */
  pinMode(MISO, OUTPUT);    /* Make MISO pin as OUTPUT */
  index = 0;
  receivedone = false;
  SPI.attachInterrupt();  
pinMode(8,OUTPUT);
}

void loop (void)
{
if (receivedone) {
    buff[index] = 0;
    //Serial.println(buff);
    String std (buff);
    if(std=="1")
    {
      Serial.print("acik: ");
      Serial.println(std);
    digitalWrite(8,LOW);
    }
    else
    {
      Serial.print("kapali: ");
      Serial.println(std);
     digitalWrite(8,HIGH);
    }
     
    index = 0;
    receivedone = false;
  }
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  uint8_t oldsrg = SREG;
  cli();
  char c = SPDR;
  if (index <sizeof buff)
  {
    buff [index++] = c;
    //if (c == '\n'){     /* Check for newline character as end of msg */
     receivedone = true;
    //}
  }
  SREG = oldsrg;
}