#define MOTOR_D1_PIN 9
#define MOTOR_D2_PIN 10
#define MOTOR_PWM_PIN 11
int interruptChannelAPin = 2;
int interruptChannelBPin = 3;
int delay_count = 0;
int setpoint=0;
int fb_speed = 0;

volatile int encoderCount = 0;
volatile int encoderDir = 0;
void moveForward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,HIGH);
  digitalWrite(MOTOR_D2_PIN,LOW);
  analogWrite(MOTOR_PWM_PIN,speed);
}
void moveBackward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,speed);
}
void setSpeed (int speed)
{
  if (speed>0)
  {
    if(speed>100){speed=100;}
    moveForward(speed);
  }
 else if (speed<0)
 {
   speed=speed*(-1);
   if (speed>100){speed=100;}
   moveBackward(speed);
 }
 else
 {
   moveForward(1);}
 }
void Timer_initialize (int period)
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (16000000.0/(256.0*1000.0))*period - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12)|(0 << CS11)|(0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}
void setup()
{
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);

  pinMode(interruptChannelAPin,INPUT_PULLUP);
  pinMode(interruptChannelBPin,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannelAPin),
                 ChannelA_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannelBPin),
                 ChannelB_callback, RISING);
  Serial.begin(9600);
  Timer_initialize(300);
}
int errorr = 0;
float kp = 1.0;
float ki = 0.3;

void loop()
{
  int error = setpoint - fb_speed;
  int pid = kp*(float)(error)+ki*(float)(errorr);
  errorr += error;
  setSpeed(pid);
  Serial.print(",");
  Serial.println(fb_speed);
  delay(100);
}
void serialEvent()
{
  setpoint = Serial.parseInt();
}
void ChannelA_callback()
{
  if (digitalRead(interruptChannelAPin)==1 && 
  digitalRead(interruptChannelBPin)==0)
   {encoderCount++;}
}

void ChannelB_callback()
{
  if (digitalRead(interruptChannelAPin)==0 && 
  digitalRead(interruptChannelBPin)==1)
   {encoderCount--;}
}


ISR(TIMER1_COMPA_vect)
{
  fb_speed = encoderCount;
  encoderCount = 0;
}