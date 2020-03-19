#define LED_PIN 8
#define INT_PIN 3

int t;
int mode;
volatile int timer1_ovf = 62500;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  Serial.begin(9600);
  mode = 1;
  
  
  noInterrupts(); 
  TCCR1A = 0;  
  TCCR1B = 0;  
  
 
  
  t = 1;
  TCNT1 = t; // Timer counter register
  TCCR1B |= (1 << CS12); // Prescaler
  TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt
  
  interrupts();
  
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(mode*1000); 
  digitalWrite(LED_PIN, LOW);
  delay(mode*1000);
}

ISR (TIMER1_OVF_vect){
  if (mode < 3){
    mode++;
  }
  else{
    mode = 1;
  }
  
  Serial.println(mode);
}
