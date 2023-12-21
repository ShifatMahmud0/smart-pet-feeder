#include "HX711.h"
#include<Wire.h>

#define DOUT_PIN 2   // Connect the DOUT pin of HX711 to this Arduino pin
#define CLK_PIN 3    // Connect the CLK pin of HX711 to this Arduino pin

HX711 scale;

void setup() {
    Serial.begin(9600);
    scale.begin(DOUT_PIN, CLK_PIN);
    float calibration_factor = 802.37;
     scale.set_scale(calibration_factor);
    scale.tare();

}

void loop() {
  if (scale.is_ready()) {
  float weight = scale.get_units(10); 
    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" grams");
    delay(2000);
  }
}
