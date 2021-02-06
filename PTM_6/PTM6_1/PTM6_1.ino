const byte ledPin = 12;
const byte ledPin2 = 13;
const byte interruptPin = 2;
const byte interruptPin2 = 3;
volatile byte state = LOW;
volatile byte state2 = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), blink2, RISING);
}

void loop() {
  digitalWrite(ledPin, state);
  digitalWrite(ledPin2, state2);
}

void blink() {
  state = !state;
}   
void blink2() {
  state2= !state2;
}   
