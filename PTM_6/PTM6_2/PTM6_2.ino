const byte ledPin = 12;
const byte ledPin2 = 13;
const byte interruptPin = 2;
const byte interruptPin2 = 3;
volatile byte state = LOW;
volatile byte state2 = LOW;

int i=0;

void setup() { 
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), blink2, RISING);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
 
  // prints title with ending line break
  Serial.println("Hello World 249018");
}
 
void loop() {
  Serial.print("Dziala: ");
  Serial.println(i++);
  delay(1000);
  digitalWrite(ledPin, state);
  digitalWrite(ledPin2, state2);
}
void blink() {
  state = !state;
  if(state == LOW)
  {
    Serial.println("Led 1 wylaczone");
  }
  else if(state == HIGH)
  {
    Serial.println("Led 1 wlaczone");
  }
}   
void blink2() {
  state2 = !state2;
  if(state2 == LOW)
  {
    Serial.println("Led 2 wylaczone");
  }
  else if(state2 == HIGH)
  {
    Serial.println("Led 2 wlaczone");
  }
}
