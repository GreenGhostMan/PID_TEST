
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#define right_encoderA      2     // (interrupt numbers 1)
#define right_encoderB      3

#define LOOPTIME        100

#define ENA1 10
#define Right_in1 8
#define Right_in2 9

#include <Wire.h>
#include "robot_specs.h"


unsigned long prev_time = 0;

int set_rpm = 60;
double act_rpm = 0;

int PWM = 0; // right

volatile long right_count = 0;
long prev_count = 0;

  float Kp = 0.35;    // 0.35
  float Ki =  0.000023;   //0.000023
  float Kd =   5.5;    //5.5
  


void setup() {
  Serial.begin(9600);
  setupMotors();
  setupEncoders();
}
void loop() {
  unsigned long now_time = millis();
  long samp_time = now_time - prev_time;

  float s = samp_time / 1000.0;
  
    getMotorData(s);

    PWM = updatePid(PWM, set_rpm, act_rpm);
   
    if (PWM > 0 ) {
      Forward();
    }
    else if (PWM < 0 ) {
      Backward();
    }
    else {
      Release();
    }
  
  
    prev_time = now_time;

  Serial.print(" ");Serial.print(set_rpm);
  Serial.print(" ");Serial.print(act_rpm);
  //Serial.print(" ");Serial.print(PWM);
  //Serial.print(" ");Serial.print(right_count-prev_count);
  Serial.println();
  
}
