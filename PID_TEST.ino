
/* Author: Pyae Soan Aung © ROM ROBOTICS */

#define encoderA      2   
#define encoderB      3 

#define ENA 10
#define IN1 9
#define IN2 8

#include <Wire.h>
#include "robot_specs.h"

unsigned long lastMilli = 0;   

float Kp = 1.0; 
float Ki = 0.0;
float Kd = 0.0;
double set_rpm = 50;
double actual_rpm = 0;


int pwm = 0;

volatile long encoder_counts = 0;
long prev_encoder_counts = 0;

void setup() {
  Serial.begin(115200);
  setupMotors();
  setupEncoders();
}
void loop() {
  unsigned long now_t = millis();
  if (now_t - lastMilli >= 100)   { 
    
    long delta_t = now_t - lastMilli;    
    getMotorData(delta_t);
    float delta_t_sec = delta_t / 1000.0; 
    
    pwm = updatePid(2, pwm, set_rpm, actual_rpm,delta_t_sec);
    //pwm = 255/2;
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
    lastMilli = now_t;

    //Serial.print(" ");Serial.print(set_rpm);
    //Serial.print(" ");Serial.print(actual_rpm);
    Serial.print(" ");Serial.print(pwm);
    Serial.println();
    }
}
