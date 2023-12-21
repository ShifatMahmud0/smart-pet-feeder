#include<Servo.h>


Servo motor;

int pos=0;
void setup() {
  Serial.begin(9600);
  motor.attach(9);

}

void loop() {
   for (pos = 0; pos <= 40; pos += 1) { // goes from 0 degrees to 180 degrees
       // in steps of 1 degree
         motor.write(pos);              // tell servo to go to position in variable 'pos'
         delay(50);                       // waits 15 ms for the servo to reach the position
    
      }
      for (pos = 40; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        motor.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);          
      }  



      /*for (pos = 0; pos >= 60; pos -= 1) { // goes from 0 degrees to 180 degrees
       // in steps of 1 degree
         motor.write(pos);              // tell servo to go to position in variable 'pos'
         delay(50);                       // waits 15 ms for the servo to reach the position
    
      }
      for (pos = 60; pos <= 0; pos += 1) { // goes from 180 degrees to 0 degrees
        motor.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);          
      } */ 

}
