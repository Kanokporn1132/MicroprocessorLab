#define LED_PIN 8
#define INT_PIN 3

int mode;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                  ISR_Callback, RISING);
  Serial.begin(9600);
  mode = 1;
  Serial.println(mode);
  
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(mode*1000); 
  digitalWrite(LED_PIN, LOW);
  delay(mode*1000); 
}

void ISR_Callback() {
  if (mode < 3){
    mode++;
  }
  else{
    mode = 1;
  }
  Serial.println(mode);

}
