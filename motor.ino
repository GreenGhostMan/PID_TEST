void setupMotors() { 
  actual_rpm = 0;
  pwm = 0;
  Release();
}

void getMotorSpeed(unsigned long time_)
{
  actual_rpm = double( (encoder_counts - prev_encoder_counts) * 60000) / double ( time_ * new_enc_ticks );
  prev_encoder_counts = encoder_counts;
}

int updatePID( int old_pwm, double targetValue, double currentValue, float dt )
{
  double pidTerm = 0;
  double error = 0;
  double new_pwm = 0;
  static double prev_error = 0;
  static double integral_error = 0;

  error = targetValue - currentValue;

  integral_error += ( error*dt );
  pidTerm = (Kp*error) + (Ki*integral_error) + (Kd*((error-prev_error)/dt));
  prev_error = error;

  new_pwm = constrain( double(old_pwm) + pidTerm, -255, 255 );
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
