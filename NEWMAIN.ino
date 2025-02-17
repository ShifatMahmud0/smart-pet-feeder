#include <Wire.h>
#include "RTClib.h"
#include "HX711.h"
#include <Servo.h>

#define DT_PIN 2   // Connect the DOUT pin of HX711 to this Arduino pin
#define SCK_PIN 3   // Connect the CLK pin of HX711 to this Arduino pin

#define TRIG_PIN 12 // Connect the TRIG pin of HC-SR04 to this Arduino pin
#define ECHO_PIN 13 // Connect the ECHO pin of HC-SR04 to this Arduino pin

#define P_E 8       // Play edge pin with Arduino for sound

Servo myservo;

HX711 scale;

RTC_Millis rtc;

int pos = 0;
int speak = 0;

void setup() {
    Serial.begin(9600);
    scale.begin(DT_PIN, SCK_PIN);

    Serial.println("Wait a sec....");

    float calibration_factor = 686.875976; // Adjust this value based on calibration
    scale.set_scale(calibration_factor);

    scale.tare(); // Reset the scale to 0 reading
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(P_E, OUTPUT); // Sound
    myservo.attach(9);

    // Initialize the RTC with the current date and time
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

    // Adjust the RTC to a specific date and time
    rtc.adjust(DateTime(2025, 1, 27, 9, 0, 0));
}

void loop() {
    DateTime now = rtc.now();

    if ((now.hour() == 9 && now.minute() >= 0 && now.minute() <= 30) || (now.hour() == 3 && now.minute() >= 32 && now.minute() <= 35)) {

        long duration, distance_cm;

        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);

        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        duration = pulseIn(ECHO_PIN, HIGH);

        distance_cm = (duration * 0.034 / 2); // Calculate distance in centimeters

        Serial.print("Cat Distance: ");
        Serial.print(distance_cm);
        Serial.println(" cm");
        delay(2000);

        int threshold_distance = 20; // Adjust this value as needed

        if (distance_cm > threshold_distance && speak == 0) {
            Serial.println("calling...");

            digitalWrite(P_E, HIGH); // Play audio in a loop
            delay(2000);
            digitalWrite(P_E, LOW);
            delay(1000);
        } else if (distance_cm < threshold_distance) {

            speak = 1;

            digitalWrite(P_E, LOW); // Turn off recording

            if (scale.is_ready()) {
                while (true) { // Keep the motor running until the weight exceeds 50 grams
                    float weight = scale.get_units(10);
                    Serial.print("Weight: ");
                    Serial.print(weight);
                    Serial.println(" grams");

                    if (weight >= 50) {
                        Serial.println("Weight threshold reached, stopping motor.");
                        break; // Exit the loop when weight exceeds 50 grams
                    }

                    // Motor operation
                    for (pos = 0; pos <= 180; pos += 1) {
                        myservo.write(pos); // Move servo to position 'pos'
                        delay(50);          // Wait for the servo to reach the position
                    }
                    for (pos = 40; pos >= 0; pos -= 1) {
                        myservo.write(pos); // Move servo back to position 'pos'
                        delay(10);
                    }

                    delay(1000); // Add a delay before rechecking the weight
                }
            }
        }
    } else {
        Serial.println("It's not time.");
        delay(3000);
        speak = 0;
    }
}
