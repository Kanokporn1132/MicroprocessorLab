#include <SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
int ledshow[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int i =0 ;
int t;
volatile int timer1_ovf = 62500;

void spi_write_1 (unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1,HIGH);
  digitalWrite (SS_PIN_1,LOW);
}
int c;
void setup(){
  pinMode(SS_PIN_1,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  
  t = 1;
  TCNT1 = t;  // Timer counter register
  TCCR1B |= (1 << CS12);  // Prescaler
  TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt
  
  interrupts();
}

void loop(){
  spi_write_1(ledshow[(i/2+1)%10]);
  delay(500);
}

ISR (TIMER1_OVF_vect){
  i++;
}
