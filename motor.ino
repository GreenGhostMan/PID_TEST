void setupMotors() {

  
  Release();
}
void getMotorData(float t)  {
  long tmp_count = right_count;
  act_rpm = double((tmp_count - prev_count) * 60) / double(t * enc_ticks);
  prev_count = tmp_count;
}
int updatePid(int old_pwm, int targetValue, int currentValue) {
  double pidTerm = 0; 
  double error = 0;
  double new_rpm = 0;
  double new_pwm = 0;
  static double last_error = 0;
  static double int_error = 0;
  error = targetValue - currentValue;
  
    int_error += error;
    pidTerm = Kp * error + Kd * (error - last_error) + Ki * int_error;
    last_error = error;
 
  new_rpm = constrain(double(old_pwm) * MAX_RPM / 255.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_pwm = 255.0 * new_rpm / MAX_RPM;
  return int(new_pwm);
}

void Forward() {
  digitalWrite(Right_in1, LOW);
  digitalWrite(Right_in2, HIGH);
  analogWrite(ENA1, abs(PWM));
}

void Backward() {
  digitalWrite(Right_in1, HIGH);
  digitalWrite(Right_in2, LOW);
  analogWrite(ENA1, abs(PWM));
}



void Release() {
  digitalWrite(Right_in1, LOW);
  digitalWrite(Right_in2, LOW);
  analogWrite(ENA1, 0);
}
