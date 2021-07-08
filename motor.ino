void setupMotors() {
  set_rpm = 0;
  actual_rpm = 0;

  pwm = 0;
  Release();
}
void getMotorData(unsigned long time_)  {
  actual_rpm = double((encoder_counts - prev_encoder_counts) * 60000) / double(time_ * new_enc_ticks);

  prev_encoder_counts = encoder_counts;
}
int updatePid(int id,int old_pwm, double targetValue, double currentValue,float dt) 
{
  double pidTerm = 0; 
  double error = 0;
  double new_pwm = 0;
  static double prev_left_err  = 0;
  static double left_integral_err  = 0;

  error = targetValue - currentValue;
  Serial.print(" ");Serial.print(error);
    left_integral_err  += (error*dt);
    pidTerm = (Kp * error) + (Ki * left_integral_err) + (Kd * ( (error - prev_left_err )/dt ));
    prev_left_err  = error;

  new_pwm = constrain(double(old_pwm) + pidTerm, -255, 255); 
  return int(new_pwm);
}

void Forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, abs(pwm));
}

void Backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, abs(pwm));
}

void Release() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
