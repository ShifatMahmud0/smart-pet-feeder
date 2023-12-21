#include "RTClib.h"

#define P_E 8   //play edge pin with arduino for sound

RTC_Millis rtc;


void setup () {
    Serial.begin(9600);
  
  Serial.println("Waitta Sec........");

  pinMode(P_E, OUTPUT); // sound


    // following line sets the RTC to the date & time this sketch was compiled
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    
  rtc.adjust(DateTime(2023, 12, 2, 12, 25, 0));
}

void loop () {
  DateTime now = rtc.now();

  if (now.hour() == 12 && now.minute() >= 0 && now.minute() <= 30  || now.hour()==3 && now.minute() >=32 && now.minute() <=35 ) {
    Serial.println("calling..");


    // //speaker
    digitalWrite(P_E, HIGH);   // play audio in a loop
    delay(2000);                       
    digitalWrite(P_E, LOW);    // 
    delay(1000);
  }

  else{
    digitalWrite(P_E, LOW); 
    delay(2000);
  }
    
}
