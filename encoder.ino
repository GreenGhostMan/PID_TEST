void setupEncoders() {

  right_count = 0;
  prev_count = 0;

  pinMode(right_encoderA, INPUT);
  pinMode(right_encoderB, INPUT);

  digitalWrite(right_encoderA, LOW);
  digitalWrite(right_encoderB, LOW);

  attachInterrupt(0, encoder1A, CHANGE);
  attachInterrupt(1, encoder1B, CHANGE);
}

void encoder1A() {
  if (digitalRead(right_encoderA) == digitalRead(right_encoderB)) {
    right_count = right_count - 1;
  }
  else                                                     {
    right_count = right_count + 1;
  }
}
void encoder1B() {
  if (digitalRead(right_encoderA) == digitalRead(right_encoderB)) {
    right_count = right_count + 1;
  }
  else                                                     {
    right_count = right_count - 1;
  }
}
