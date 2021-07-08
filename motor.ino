void setupMotors() { 
  actual_rpm = 0;
  pwm = 255/2;
  Release();
}

void getMotorSpeed(unsigned long time_)
{
  actual_rpm = double( (encoder_counts - prev_encoder_counts) * 60000) / double ( time_ * new_enc_ticks );
  prev_encoder_counts = encoder_counts;
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
