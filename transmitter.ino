#define ledpin 8
#define trig 9
void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(trig, OUTPUT);

}

void loop() {
  digitalWrite(ledpin, LOW);
  delay(10);
  digitalWrite(ledpin, HIGH);
  delayMicroseconds(120);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
}
