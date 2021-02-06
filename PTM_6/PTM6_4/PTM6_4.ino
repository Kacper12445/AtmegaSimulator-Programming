int obecny_rok = 2020;
int podany_rok = 0;
int incomingByte = 0;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("Witaj");
  Serial.println("Ten program oblicza wiek na podstawie roku urodzenia");
  Serial.print("\nPodaj rok urodzenia: ");
}

void loop() {
  if (Serial.available() > 0) 
  {
    podany_rok = Serial.parseInt();
    //Serial.println(podany_rok);
    Obliczanie_wieku(obecny_rok, podany_rok);
    Zapytanie();
  } 
}



void Obliczanie_wieku(int obecny_rok, int podany_rok)
{
  int x = obecny_rok - podany_rok;
  Serial.print("Masz ");
  Serial.print(x);
  Serial.print(" lat, jestes ");
  if(x < 18)
  {
    Serial.print("Niepelnoletni");
  }
  else if(x >= 18 && x <25)
  {
    Serial.print("prawdopodobnie studentem");
  }
  else if(x >= 25 && x <65)
  {
    Serial.print(" pracownikiem");
  }
  else if(x >= 65)
  {
    Serial.print(" na emeryturze");
  }
  else if(x > 125 || x < 0)
  {
    Serial.print("pewny wpisanego roku ? Sprobuj ponownie");
  }
}

void Zapytanie()
{
   Serial.print("\n\nPodaj rok urodzenia: ");
}
