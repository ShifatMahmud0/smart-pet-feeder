#define trig 12
#define echo 13

void setup(){
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop(){
  long duration, distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration= pulseIn(echo, HIGH);

  distance=(duration*0.034/2);

  Serial.print(" distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(2000);
}