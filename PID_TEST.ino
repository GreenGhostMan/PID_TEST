
/* Author: Pyae Soan Aung © ROM ROBOTICS */

#define encoderA      2   
#define encoderB      3 

#define ENA 10
#define IN1 9
#define IN2 8

#include <Wire.h>
#include "robot_specs.h"

unsigned long prev_MilliSec = 0;   


int pwm = 0;

volatile long encoder_counts = 0;
long prev_encoder_counts = 0;

void setup() {
  Serial.begin(115200);
  setupMotors();  
  
  pwm = int(255 * 0.0);
}
void loop() {
  unsigned long now_t = millis();
  
  if (now_t - prev_MilliSec >= 70)   { 
    
    if ( pwm > 0 ) 
    {
      Forward();
    }
    else if ( pwm < 0 ) 
    {
      Backward();
    }
    if ( pwm == 0 ) 
    {
      Release();
    }  
    prev_MilliSec = now_t;

    //Serial.print(" ");Serial.print(set_rpm);
    //Serial.print(" ");Serial.print(actual_rpm);
    Serial.print(" ");Serial.print(pwm);
    Serial.println();
    }
}
