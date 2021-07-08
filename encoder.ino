
void setupEncoders() {

  encoder_counts = 0;
  prev_encoder_counts = 0;
  
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  
  digitalWrite(encoderA, LOW);
  digitalWrite(encoderB, LOW);

 
  attachInterrupt(digitalPinToInterrupt(encoderA), encoder2A, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(encoderB), encoder2B, CHANGE);
}

void encoder2A() {
  if (digitalRead(encoderA) == digitalRead(encoderB)) {
    encoder_counts = encoder_counts + 1;
  }
  else                                                     {
    encoder_counts = encoder_counts - 1;
  }
}
void encoder2B() {
  if (digitalRead(encoderA) == digitalRead(encoderB)) {
    encoder_counts = encoder_counts - 1;
  }
  else                                                     {
    encoder_counts = encoder_counts + 1;
  }
}
