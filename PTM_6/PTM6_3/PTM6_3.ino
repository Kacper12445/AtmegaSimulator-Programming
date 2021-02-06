int incomingByte = 0;
int i = 0;
void setup() {
  Serial.setTimeout(100);
  Serial.begin(9600);
  Serial.println("Hello World - 249018\n");
}

void loop() {
  
  if (Serial.available() > 0) { 
    incomingByte = Serial.read();
    
    Serial.print("\nOtrzymalem: ");
    Serial.print((char)incomingByte);
    Serial.print("-");
    Serial.print(incomingByte, DEC);
    i = 0;
  }
else
{
  i++;
  delay(1000);
}
if(i == 10)
  {
    Serial.println("\nCzekam na znak, pospiesz sie...");
    i = 0;
  }
}
