# AtmegaSimulator-Programming

Polecenia 

PTM_1
1. Przygotować program, który będzie posiadał 3 tryby działania:

    I tryb (domyślny, po uruchomieniu) – dioda miga z częstotliwością 0,5Hz
    II tryb – dioda świeci ciągle
    III tryb – dioda jest wyłączona
2. Zmiana trybów następuje przez naciskanie przycisku, należy uwzględnić problem z drganiami styków i długiego przytrzymania przycisku. Jedno przyciśnięcie-> zmiana na kolejny tryb
***************************************************************************************************************************************************************************************************************************************************
PTM_2
1. Napisać funkcję setLED(uint8_t led,uint8_t stan), gdzie led to numer diody od 1-8, a stan 1-dioda świeci 0 – dioda nie świeci,
2. Napisać funkcję getButton(), która zwraca numer przyciśniętego przycisku na klawiaturze z zakresu 1-12, oraz numer 13-16 dla dodatkowych przycisków.
3. Stworzyć program (wykorzystując stworzone funkcje), który po wciśnięciu przycisku 1-8 (z klawiatury spowoduje zaświecenie odpowiedniej diody), ponowne przyciśnięcie przycisku wyłączy diodę, dodatkowo “*” włącza wszystkie diody, “#” wyłącza wszystkie diod led.
***************************************************************************************************************************************************************************************************************************************************
PTM_3
1. Stworzyć program realizujący obsługę kalkulatora, umożliwiającego wprowadzanie liczb od 0-999, wykonującego działania dodawanie, odejmowanie, mnożenie oraz kasowanie obliczeń.

***************************************************************************************************************************************************************************************************************************************************
PTM_4
1. Umieścić na schemacie mikrokontoler, dwa potencjometry zadający napięcie w zakresie 0-5V, dwa mierniki napięcia (Voltimeter) do mierzenia napięcia z potencjometrów i wyświetlacz LCD
2. Podłączyć elementy i napisać program, gdzie mikrokontroler wykorzystuje przetwornik A/D do pomiaru napięcia i  wyświetla je na wyświetlaczu LCD
3. Wpierwszej linii LCD wyświetlana jest wartość mierzonego napięcia w woltach i wartość od 0-100, proporcjonalnie odpowiadająca mierzonemu napięciu, 0V to 0, 2,5V to 50 itd.
4. W drugiej linii LCD wyświetlamy wartości z drugiego potencjometru
5. Tworzymy 3 funkcje, jedna funkcja to jeden regulator, funkcja przyjmuje parametr (uint8_t wartośćZadana, uint8_t wartoscRzeczywista)
zadaniem każdej funkcji jest realizacja następującego działania:

    regulator dwupołożeniowy – realizuję działanie regulatora dwustanowego i wyświetla swoje stany na diodzie L1
    regulator dwupołożeniowy z histerezą – realizuję działanie regulatora dwustanowego z histerezą i wyświetla swoje stany na diodzie L2, histerezę ustawić na 0,5V
    regulator trójpołożeniowego – realizuję działanie regulatora trójpołożeniowego i wyświetla swoje stany na diodach L3A i L3B

6. Wartość zadana to wartość z 1 potencjometru, a wartość rzeczywista to napięcie z 2 potencjometru,
7. Dodajemy funkcję, realizującą zdanie regulatora PID – przyjmuje takie same parametry jak pozostałe funkcje regulatorów
    - W obecnym zadaniu działanie regulatora PID ograniczamy tylko do członu “P”,
    - Wyliczamy uchyb regulacji,
    - Uchyb przeliczamy przez współczynnik członu proporcjonalnego “Kp” i otrzymujemy wartość sterującą,
    - Wartość sterująca powinna być w zakresie 0-100, gdzie 50 to gdy uchyb wynosi 0 a pozostałe wartości są proporcjonalne i wypełniają cały zakres sterowania,
    - Wartość wyświetlamy w 3 linijce wyświetlacza LCD 
***************************************************************************************************************************************************************************************************************************************************
PTM_5

1.PTM5_3
   Utworzyć program, który w pętli głównej co jedną sekundę zwiększa licznik o 1 – sekundnik, licznik może mieć wartości od 0-255, stan licznika wyświetlany jest w pierwszej linii LCD,
     -Po wciśnięcia przycisku należy odczytać aktualny licznik i zapisać jego wartość do pamięci eeprom przy użyciu funkcji “eeprom_write_byte”,
     -Każde kolejne wciśnięcie przycisku jest zapisywane do kolejnej komórki pamięci eeprom, maksymalnie może być 100 zapisanych wartości,
     -Indeks aktualnie zapisywanej komórki należy wyświetlić w drugiej linijce wyświetlacza LCD,
     -Sprawdzić czy poprawnie są zapisywane wartości do pamięci eeprom przez podgląd pliku pamięci, w tym celu po wykonaniu kilku przyciśnięć przycisku należy wykonać operację “Save EEPROM data” dostępne w opcjach mikrokontrolera. Zapisany plik można podglądnąć w notatniku. Powinien zawierać kolejne zapisane czasy naszego programu.

2. PTM5_4
   Utworzyć program, który będzie odczytywał kolejne liczby z pamięci eeprom:
     -Symulacja zawiera wyświetlacz LCD,
     -Po załadowaniu programu i należy załadować plik z zapisem pamięci eeprom,
     -W pliku zapisana są dane, liczby od 1 do 10 a następnie występuje liczba 255, która oznacza koniec odczytywania,
     -Program powinien odczytywać kolejne liczby z pamięci EEPROM przy użyciu funkcji “eeprom_read_byte”, wyświetlacz na wyświetlaczu kolejną liczbę co 1 sekundę i zakończyć działanie po osiągnięciu oznaczenia końca liczb,
     -W czasie oceniania plik z zapisem pamięci eeprom może być inny, więc program powinien działać prawidłowo na różnych plikach, maksymalna ilość liczb do wczytania to 20.

3. PTM5_5
  Utworzyć program, który loguje dane pomiarowe.
    -Symulacja powinna zawierać wyświetlacz LCD, potencjometr do zadawania napięcia-dane pomiarowe,
    -Program maksymalnie może zapisać 10 pomiarów w pamięci eeprom,
    -Zapis nowego pomiaru,napięcia dokonywany jest co 5 sekund,
    -Po dokonaniu zapisu 10 pomiarów, na wyświetlaczu pojawia się komunikat o końcu logowania i następuje wyświetlanie po kolei zapisanych wyników w postaci pomiar1:x.x – gdzie x.x to napięcie w formacie 2.5V,
    -Po wyświetleniu wszystkich pomiarów program kończy swoje działanie.
***************************************************************************************************************************************************************************************************************************************************
PTM_6
1. PTM6_1
    -Stworzyć symulację z płytką Arduino Uno, dodać dwa przyciski dołączone do pinów 2 i 3, oddać 2 diody LED,
    -Utworzyć program, który za pomocą przerwania z przycisku 1 będzie włączył/wyłączał diodę 1,
    -Analogicznie do poprzedniego punktu, uruchomić przycisk 2 i diodę 2.
2. PTM6_2
    -Na podstawie programu z zadania 1, należy uruchomić obsługę komunikacji UART,
    -Ustawić prędkość komunikacji UART na 9600
    -Na początku programu (tylko jeden raz), należy wysłać do terminala napis “Hello world – numer indeksu”, gdzie za napis numer indeksu podstawiamy swój numer,
    -W pętli głównej programu utworzyć licznik zliczający o 1, co 1 sekundę
    -Na każdą zmianę licznika powinien zostać przesłany po interfejsie uart napis “dziala: n”, gdzie n to stan licznika,
    -Każdy kolejny napis powinien być w nowej linijce,
    -Dodać do obsługi przerwań przesyłanie komunikatu po UART o zmianie stanu diody LED.

3. PTM6_3
  Utworzyć nowy program i skonfigurować komunikację UART jak w zadaniu 2.
    -Na początku programu (tylko jeden raz), należy wysłać do terminala napis “Hello world – numer indeksu”, gdzie za napis numer indeksu podstawiamy swój numer,
    -Program co 1 sekundę sprawdza czy został wysłane do mikrokontrolera jakiś znak po UART, jeśli tak to odbiera go i wyświetla na ekranie napis “Odebralem: x-nn”, gdzie x to przesłany znak w postaci znaku ASCII, a nn to jego kod liczbowy,czyli dla przesłanego znaku “a” ma zostać wyświetlony komunikat “Odebrałem: a-97”
    -Co każde 10 sekund jeśli nie został przesłany jakiś znak, wyświetla na ekranie napis “Czekam na znak, pospiesz się…”

4. PTM6_4
  Utworzyć program, który oblicza wiek osoby na podstawie wprowadzonego roku urodzenia.
    -Po uruchomieniu program przedstawia się, krótkim komunikatem z nazwą programu i opisem co robi,
    -Następnie prosi o podanie roku urodzenia,
    -Wczytane dane zamienia na liczbę i dokonuje obliczenia wieku osoby (dla uproszczenia proszę przyjąć rok obecny na 2020),
    -Wyświetla na ekranie komunikat, gdzie x to obliczony wiek, a “…” to miejsce na wymyślony komentarz, logiczne dokończenie komunikatu:
        jeśli wiek <18 – “Masz x lat, ale jesteś …”,
        dla 18<=wieku < 25 – “Masz x lat, jesteś …”,
        dla 25<=wieku < 65 – “Masz x lat, czy już …”,
        dla 65<=wieku – “Masz x lat, czy to już …”,
    -Następnie program ponownie rozpoczyna działanie od początku.

5. PTM6_5
  Utworzyć program, który na podstawie wprowadzonej daty urodzenia określa czy osoba jest pełnoletnia.
    -Program prosi o podanie daty urodzenia w formacie dd.mm.yyyy, czyli 01.05.2000,
    -Oblicza czy osoba ma skończone 18 lat, dla uproszczenia proszę przyjąć dzisiejszą datę jako 08.02.2021,
    -Wyświetla na ekranie komunikat “Jesteś już pełnoletni.” lub “Jeszcze nie masz 18 lat, musisz poczekać: xxx dni”, gdzie xxx to ilość dni jaka pozostała aby dana osoba osiągnęła pełnoletność.
