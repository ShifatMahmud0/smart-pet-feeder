// Date and time functions using just software, based on millis() & timer

#include <Wire.h>
#include "RTClib.h"
#include "HX711.h"
#include <Servo.h>


#define DT_PIN 2   // Connect the DOUT pin of HX711 to this Arduino pin
#define SCK_PIN 3    // Connect the CLK pin of HX711 to this Arduino pin

#define TRIG_PIN 12   // Connect the TRIG pin of HC-SR04 to this Arduino pin
#define ECHO_PIN 13   // Connect the ECHO pin of HC-SR04 to this Arduino pin
//#define LED_PIN 6    // Connect the LED to this Arduino pin

#define P_E 8   //play edge pin with arduino for sound

Servo myservo;

HX711 scale;

RTC_Millis rtc;

int pos=0;
int speak=0;


void setup () {
    Serial.begin(9600);
    scale.begin(DT_PIN, SCK_PIN);
  
  Serial.println("Waitta Sec....");

  float calibration_factor = 802.37; // Adjust this value based on calibration
  //scale.set_scale(calibration_factor);
  scale.set_scale(calibration_factor);
  
  scale.tare();      // Reset the scale to 0 reading
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 // pinMode(LED_PIN, OUTPUT);
  pinMode(P_E, OUTPUT); // sound
  myservo.attach(9);


    // following line sets the RTC to the date & time this sketch was compiled
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    
  rtc.adjust(DateTime(2023, 12, 17, 17, 25, 0));
}

void loop () {
  DateTime now = rtc.now();

  if (now.hour() == 17 && now.minute() >= 0 && now.minute() <= 30  || now.hour()==3 && now.minute() >=32 && now.minute() <=35 ) {

      
      long duration, distance_cm;
  
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
  
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
  
      duration = pulseIn(ECHO_PIN, HIGH);
  
      distance_cm = (duration*0.034/2);  // Calculate distance in centimeters
  
      Serial.print("Cat Distance: ");
      Serial.print(distance_cm);
      Serial.println(" cm");
      delay(2000);
     // Set a threshold distance to turn on/off the LED
      int threshold_distance = 20; // Adjust this value as needed

    if (distance_cm > threshold_distance && speak == 0) {
      Serial.println("calling...");

       // //speaker
       digitalWrite(P_E, HIGH);   // play audio in a loop
       delay(2000);                       
       digitalWrite(P_E, LOW);    // 
       delay(1000);
    
      }


    else if(distance_cm < threshold_distance){
    
       speak=1;

       digitalWrite(P_E, LOW);  // turn off recording 

      if (scale.is_ready()) {
        float weight = scale.get_units(10); 
        Serial.print("Weight: ");
        Serial.print(weight);
        Serial.println(" grams");
        if (weight < 50){
          // Wait for a moment before taking another measurement
           //digitalWrite(LED_PIN, HIGH);  // Turn on the LED // running motor
      
      

          for (pos = 0; pos <= 40; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(50);                       // waits 15 ms for the servo to reach the position
    
           }
          for (pos = 40; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(10);          
           }               // waits 15 ms for the servo to reach the position
      
        }
           Serial.println("food is given");
           //digitalWrite(LED_PIN, LOW);

            delay(1000);
       }

     } 
  
   } 
    
  else 
  {
    Serial.println("its not time");
    delay(3000);
    speak=0;
  }
       
}
