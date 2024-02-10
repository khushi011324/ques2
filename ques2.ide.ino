const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  Serial.begin(9600);
  startTimer(0.5);  // Set the initial timer frequency
}

void loop() {
  // Empty loop, as the main work is done through interrupts.
}

void startTimer(double frequency) {
  noInterrupts();
  int prescaler = 1024;  // Adjust based on your specific timer and Arduino model
  long timerValue = F_CPU / prescaler / frequency - 1;
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = timerValue;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}
