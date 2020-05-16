#include <math.h>
#define irsig 12
#define trig1 8
#define echo1 9
#define trig2 6
#define echo2 7
#define dist3 6.4
#define latchPin  2
#define clockPin  3
#define dataPin  4


void setup() {

  pinMode(trig1, OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(irsig,INPUT);
 
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  Serial.begin(9600);


}

void loop() {
 
  float dist1, dist2;

  dist1=distance(trig1, echo1);
  dist2=distance(trig2, echo2);
  if(!(dist1&&dist2)){return;}
  float emit_angle=angle(dist2, dist1);
  if(isnan(emit_angle)){return;}
  displaydiode(emit_angle);



}
float distance(unsigned long trig, unsigned long echo){
  unsigned long t;
  float dist;
  while(digitalRead(irsig)){}
  while(!digitalRead(irsig)){}
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  t=pulseIn(echo, HIGH,10000);
  if(!t){return 0;}
  dist=(340*t);
  dist/=10000;
  return dist;

  
}


float angle(float dist1, float dist2)
{
    float a=dist2;
    float b=dist1;
    float c=dist3;
  

  

    float M=sqrt(0.25*(2*a*a+2*b*b-c*c));

    float X = acos(((c/2)*(c/2)+M*M-b*b)/(2*(c/2)*M));
    X=X*57.295779;//radians to degrees
    return X;



}

void displaydiode(float angle)
{
  int leds=0;
  bitSet(leds,angletodiode(angle)); 

  updateShiftRegister(leds);
}

void updateShiftRegister(int leds)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   shiftOut(dataPin, clockPin, LSBFIRST, (leds>>8));
   digitalWrite(latchPin, HIGH);
}

int angletodiode(float angle)
{
  if(angle>173){return 15;}
  int step1=180/16;
  int diode=angle/step1;
    return diode;
  
}
