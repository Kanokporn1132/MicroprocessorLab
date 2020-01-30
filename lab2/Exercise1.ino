int clk_pin = 6; //SHCP
int data_pin = 5; //DS
int latch_pin = 4; //STCP


void brokenmicro1(int DATA) {
  digitalWrite(latch_pin, LOW);
  for(int i = 0 ; i < 16 ; i++){
    digitalWrite(data_pin, (DATA >> (15-i)) & 0b0000000000000001);
    //digitalWrite(data_pin, 0b0000000000000000);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
    digitalWrite(latch_pin,HIGH);
    delay(100);
    digitalWrite(latch_pin,LOW);
  }
//  digitalWrite(latch_pin,HIGH);
//  delay(100);
//  digitalWrite(latch_pin,LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
    delay(100);
  pinMode(data_pin,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  int data = 0b1000000000000000;
  
  for(int i = 0; i < 16; i++){
    brokenmicro1(data);
  }

  
}
