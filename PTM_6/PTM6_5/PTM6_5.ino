String x;
String recent_Data = {"08.02.2021"};      //data odniesienia
int r_day = 0;                            //zmienna int przechowujaca numer dnia z daty odniesienia
int r_month = 0;                          //zmienna int przechowujaca numer miesiaca z daty odniesienia
int r_year = 0;                           //zmienna int przechowujaca numer roku z daty odniesienia
int luty = 0;
int dni_miesiaca[] = {31, luty, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  //tablica ilosci dni w poszeczgolnych miesiacach

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.print("\nDzisiejsza ");
  r_day = Obliczanie_dni(recent_Data[0], recent_Data[1]);                                        //zmiana string na int
  r_month = Obliczanie_miesiecy(recent_Data[3],recent_Data[4]);                                  //zmiana string na int
  r_year = Obliczanie_roku(recent_Data[6], recent_Data[7], recent_Data[8], recent_Data[9]);     //zmiana string na int
  Start(r_day, r_month, r_year);                                                                //Wyswietlanie daty
  Podaj_date();                                                                                 //komunikat aby podac date
}

void loop() {
  if (Serial.available() > 0)             //czekanie na dane
  {
    x = Serial.readString();              //przypisywanie jako string wpisanej liczby
    Czy_pelnoletni(recent_Data, x);       //sprawdzanie czy ktos jest pelnoletni
  }
}


void Czy_pelnoletni(String data, String data2)
{
  int d1 = Obliczanie_dni(data[0], data[1]);                        //przypisywanie zmiennym int wartosci ze stringa , przyklad daty odniesienia
  int m1 = Obliczanie_miesiecy(data[3],data[4]);                          
  int y1 = Obliczanie_roku(data[6], data[7], data[8], data[9]);

  int d2 = Obliczanie_dni(data2[0], data2[1]);                        //przypisywanie zmiennym int wartosci ze stringa , przyklad daty wpisanej
  int m2 = Obliczanie_miesiecy(data2[3],data2[4]);
  int y2 = Obliczanie_roku(data2[6], data2[7], data2[8], data2[9]);

  int liczba_dni_teraz = ile_dni_teraz(d2, m2, y2, d1, m1, y1);       //obliczanie ile dni zyjemy w dniu odniesienia
  int liczba_dni_w_18 = ile_dni_do18(d2, m2, y2);                     //obliczanie ile dni bedziemy mieli w 18 urodziny
  int brakujace_dni = liczba_dni_w_18 - liczba_dni_teraz;             //obliczanie ile dni nam brakuje do 18 urodzin
   
      if(brakujace_dni < 0)
      {
        Serial.println("Jestes pelnoletni");
      }
      else if(brakujace_dni > 0)
      {
        Serial.println("Brakuje ci: ");
        Serial.print(brakujace_dni);
        Serial.print(" dni do 18 urodzin");
      }
      else
      {
        Serial.println("Dzisiaj sa twoje urodziny, Wszystkiego najlepszego !");
      }
      Podaj_date();                         //komunikat aby podac date    
}

int dni_do_pocz(int d, int m, int y)    //funkcja obliczajaca ile dni od daty podanej jako argumenty jest do 1 dnia biezacego roku
{
  int dni = 0;
  int x = 0;
  if(Czy_przestepny(y) == true)         //jesli rok jest przestepny to luty ma 29 dni
  {
    dni_miesiaca[1] = 29;  
  }
  else                                  //jesli rok nie jest przestepny to luty ma 28 dni
  {
    dni_miesiaca[1] = 28;
  }
  for(int i = 0; i < (m-1); i++)
  {
    dni = dni + dni_miesiaca[i];       //zliczanie dni za pomoca tablicy dni poszczegolnych miesiecy
  }
  x = d + dni;                         //obliczanie ile dni do poczatku roku
  return x;
}

int ile_dni_teraz(int d, int m, int y, int d2, int m2, int y2)    //funkcja obliczajaca ile zyjemy dni w dniu daty odniesienia
{
  int il_dni = 0;
  int x = dni_do_pocz(d, m, y);       // liczba dni do poczatku roku od dnia urodzin
  int x2 = dni_do_pocz(d2, m2, y2);   //  liczba dni do poczatku roku od dnia odniesienia
  int  r_diff = y2 - y;               //roznica lat miedzy datami
  
  for(int i = 0; i < r_diff; i++)     //zliczanie dni w latach roznicy miedzy datami
  {
    if(Czy_przestepny(y + i))
    {
      il_dni = il_dni + 366;          //gdy rok przestepny
    }
    else
    {
      il_dni = il_dni + 365;          //gdy rok normalny
    }
  }
  il_dni = il_dni - x + x2;           //koncowy wynik w dniach
  return il_dni;
    
}

int ile_dni_do18(int d, int m, int y)         //funkcja obliczajaca ile dni zyjemy w dniu 18-stych urodzin
{
  int il_dni = 0;
  int x = dni_do_pocz(d, m, y);
  il_dni = il_dni - x;          //niepotrzebna zmienna jednak ulatwia sledzenie obliczen
  
  for(int i = 0; i < 18; i++)   //petla obliczajaca sumuje ilosc dni kazdego roku miedzy rokiem narodzin a rokiem gdy mamy 18 lat  
  {                             //biorac pod uwage lata przestepne
    if(Czy_przestepny(y + i))
    {
      il_dni = il_dni + 366;
    }
    else
    {
      il_dni = il_dni + 365;
    }
  }
  il_dni = il_dni + x;      //niepotrzebna zmienna jednak ulatwia sledzenie obliczen
  return il_dni;
}

void Podaj_date()               //funkcja wyswietlajaca komunikat w jaki sposob wpisac date
{
  Serial.println("\nPodaj date w formacie dd.mm.yyyy");
}

void Start(int day, int month, int year)                  //fucnkcja wyswietlajaca wpisana date
{ 
  if(day < 10)
  {
    Serial.print("data to: 0");
  }
  Serial.print(day);
  Serial.print(".");
  if(month < 10)
  {
    Serial.print("0");
  }
  Serial.print(month);
  Serial.print(".");
  Serial.print(year);
}

int Obliczanie_dni(char d, char d2)         //zmiana char na int w przypadku dnia z daty
{
  int dzien = (d -'0')*10 + (d2 - '0');
  return dzien;
}
int Obliczanie_miesiecy(char m, char m2)         //zmiana char na int w przypadku miesiaca z daty
{
  int month = (m - '0')*10 +(m2 - '0');
  return month;
}
int Obliczanie_roku(char r, char r2, char r3, char r4)             //zmiana char na int w przypadku roku z daty
{
  int year = (r-'0')*1000 +(r2-'0')*100 + (r3-'0')*10 + r4-'0';
  return year;
}

bool Czy_przestepny(int rok)                                        //sprawdzamy czy rok w argumencie jest przestepny
{
  bool x = 0;
  if(rok%4 == 0)
  {
    if(rok%100  == 0)
    {
      if(rok % 400 == 0)
      {
        x = true;
      }
      else
      {
        x = false;
      }
    }
    else
    {
      x = true;
    }
  }
  else
  {
    x = false;
  }
  return x;
}
