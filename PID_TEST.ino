
/* Author: Pyae Soan Aung © ROM ROBOTICS */

#define encoderA      2   
#define encoderB      3 

#define ENA 10
#define IN1 9
#define IN2 8

#include <Wire.h>
#include "robot_specs.h"

// SLAMTEC ROBOT POLOLU 100 RPM DC MOTOR ( LEFT )
//float Kp=0.13, Ki=0.001, Kd=0.01; // encoder_ticks = 6533 ( 2 pins mode )
float Kp=0.13, Ki=0.003, Kd=0.015;  // encoder_ticks = 3266.5 ( 1 pins mode )
unsigned long prev_MilliSec = 0;   

int pwm = 0;

volatile long encoder_counts = 0;
long prev_encoder_counts = 0;

double set_rpm = 50;
double actual_rpm = 0;

void setup() {
  Serial.begin(9600);
  setupMotors();
  setupEncoders();
}
void loop() {
  unsigned long now_t = millis();
  if (now_t - prev_MilliSec >= 100)   {   
   
    long delta_t = now_t - prev_MilliSec;
    float delta_t_Sec = delta_t / 1000.0;
    
    getMotorSpeed(delta_t);
    pwm = updatePID( pwm, set_rpm, actual_rpm, delta_t_Sec );
    
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

    Serial.print("\t");Serial.print(set_rpm);
    Serial.print("\t");Serial.print(actual_rpm);
    //Serial.print(" ");Serial.print(pwm);
    //Serial.print(" ");Serial.print(encoder_counts);
    Serial.println();
    }
}
