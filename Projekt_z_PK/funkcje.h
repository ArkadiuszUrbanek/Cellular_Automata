/** @file */
#ifndef funkcje_h
#define funkcje_h

#include <wchar.h>
#include <stdbool.h>
#include <windows.h>

#include "stale.h"
#include "struktury.h"

/** Funkcja statyczna u¿ywana przez funkcjê @ref zaznacz_komorki_na_planszy()
 * @param[in] indeks_kolumny indeks kolumny, dla którego ma zostaæ wyznaczona kolumna, od której nale¿y wyœwietliæ planszê
 * @return Indeks kolumny, od którego powinna byæ wyœwietlona plansza. (int)
*/
static int zbadaj_przedzial_dla_kolumny(int indeks_kolumny);

/** Funkcja statyczna u¿ywana przez funkcjê @ref zaznacz_komorki_na_planszy()
 * @param[in] indeks_wiersza indeks wiersza, dla którego ma zostaæ wyznaczony wiersz, od którego nale¿y wyœwietliæ planszê
 * @return Indeks wiersza, od którego powinna byæ wyœwietlona plansza. (int)
*/
static int zbadaj_przedzial_dla_wiersza(int indeks_wiersza);

/** Funkcja statyczna u¿ywana przez funkcjê @ref zaznacz_komorki_na_planszy() oraz funkcjê @ref gra_w_zycie()
 * Wyœwietla planszê do gry w ¿ycie od konkretnych indeksów. 
 * @param[in] plansza wskaŸnik na wskaŸnik na wchar_t s³u¿¹cy do poruszania siê po tablicy
 * @param[in] szerokosc_planszy szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc_planszy wysokoœæ planszy do gry w ¿ycie
 * @param[in] wskazany_wiersz wiersz, od którego ma byæ wyœwietlona plansza do gry w ¿ycie
 * @param[in] wskazana_kolumna kolumna, od której ma byæ wyœwietlona plansza do gry w ¿ycie
*/
static void wyswietl_plansze_od_indeksow(wchar_t** plansza, int szerokosc_planszy, int wysokosc_planszy, int wskazany_wiersz, int wskazana_kolumna);

/** Funkcja s³u¿¹ca do zaznaczania komórek na planszy do gry w ¿ycie.
 * @param[in,out] plansza tablica dwuwymiarowa do gry w ¿ycie o nazwie plansza
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy do gry w ¿ycie
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void zaznacz_komorki_na_planszy(wchar_t** plansza, const int* szerokosc, const int* wysokosc, const HANDLE* uchwyt);

/** Funkcja dodaj¹ca komórkê na koniec listy jednokierunkowej.  
 * @param[in,out] ppglowa wskaŸnik na wskaŸnik na g³owê listy 
 * @param[in] x wskaŸnik na wspó³rzêdn¹ X
 * @param[in] y wskaŸnik na wspó³rzêdn¹ Y
*/
void wstaw_komorke_do_listy(komorka** ppglowa, const int* x, const int* y);

/** Funkcja usuwaj¹ca listê jednokierunkow¹ komórek.
 * @param[in,out] ppglowa wskaŸnik na wskaŸnik na g³owê listy
*/
void usun_liste_komorek(komorka** ppglowa);

/** Funkcja usuwaj¹ca jedn¹ komórkê z koñca listy jednokierunkowej. 
 * @param[in,out] ppglowa wskaŸnik na wskaŸnik na g³owê listy
*/
void usun_komorke_z_konca_listy(komorka** ppglowa);

/** Funkcja nadpisuj¹ca dane wybranej komórki z listy komórek.
 * @param[in] pglowa wskaŸnik na g³owê listy
 * @param[in] x wskaŸnik na wspó³rzêdn¹ X
 * @param[in] y wskaŸnik na wspó³rzêdn¹ Y
 * @param[in] wybrana_komorka wskaŸnik na numer komórki, której dane maj¹ zostaæ nadpisane
*/
void zmien_wspolrzedne_komorki(komorka* pglowa, const int* x, const int* y, const int* wybrana_komorka);

/** Funkcja statyczna u¿ywana przez funkcjê @ref gra_w_zycie()
 * Uaktualnia planszê do gry w ¿ycie o nowe pokolenie.
 * @param[in,out] plansza tablica dwuwymiarowa do gry w ¿ycie o nazwie plansza
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy do gry w ¿ycie
 * @param[in,out] ppglowa wskaŸnik na wskaŸnik na g³owê listy 
 * @param[in] poprzednia_dlugosc_listy wskaŸnik na d³ugoœæ listy jednokierunkowej ¿ywych komórek
*/
static void nowe_pokolenie(wchar_t** plansza, const int* szerokosc, const int* wysokosc, komorka **ppglowa, int* poprzednia_dlugosc_listy);

/** Funkcja s³u¿¹ca do realizowania algorytmu automatu komórkowego "Gra w ¿ycie".
 * @param[in,out] plansza tablica dwuwymiarowa do gry w ¿ycie o nazwie plansza
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy do gry w ¿ycie
 * @param[in] sekundy czas ¿ycia jednego pokolenia wyrazony w sekundach
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
 * @return WskaŸnik na strukturê. (komorka*)
*/
komorka* gra_w_zycie(wchar_t** plansza, const int* szerokosc, const int* wysokosc, const int* sekundy, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do zapisu gry w ¿ycie.
 * @param[in] nazwa_pliku ³añcuch znaków z nazw¹ pliku
 * @param[in] pglowa wskaŸnik na g³owê listy jednokierunkowej ¿ywych komórek
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy do gry w ¿ycie
 * @return Wartoœæ true lub false
*/
bool zapisz_gre_w_zycie(const wchar_t nazwa_pliku[], komorka* pglowa, const int* szerokosc, const int* wysokosc);

/** Funkcja s³u¿¹ca do odczytu gry w ¿ycie.
 * Sprawdza ona równie¿ poprawnoœæ sk³adni pliku. 
 * @param[in] nazwa_pliku ³añcuch znaków z nazw¹ pliku
 * @param[in,out] ppglowa wskaŸnik na wskaŸnik na g³owê listy jednokierunkowej ¿ywych komórek
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy do gry w ¿ycie
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy do gry w ¿ycie
 * @return Wartoœæ true lub false
*/
bool odczytaj_gre_w_zycie(const wchar_t nazwa_pliku[], komorka** ppglowa, int* szerokosc, int* wysokosc);

/** Funkcja statyczna u¿ywana przez funkcjê @ref mrowka_langtona()
 * Wyœwietla widzian¹ przez u¿ytkownika czêœæ planszy.
 * @param[in] plansza tablica dwuwymiarowa, po której porusza siê mrówka
 * @param[in] kawalek_planszy struktura zawieraj¹ca wspó³rzêdne lewego górnego rogu i prawego dolnego rogu widocznej dla u¿ytkownika czêœci planszy
 * @param[in] pozycja_mrowki struktura zawieraj¹ca informacje o mrówce
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
static void odswiez_plansze_dla_mrowki_langtona(const bool** plansza, const prostokat* kawalek_planszy, const mrowka* pozycja_mrowki, const HANDLE* uchwyt);

/** Funkcja statyczna uzywana przez funkcjê @ref mrowka_langtona()
 * Uaktualnia planszê do gry o kolejny krok mrówki oraz dodatkowo wyœwietla wprowadzone zmiany na ekranie konsoli, tylko je¿eli bêd¹ one widoczne dla u¿ytkownika.
 * @param[in,out] plansza tablica dwuwymiarowa, po której porusza siê mrówka
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy
 * @param[in] kawalek_planszy struktura zawieraj¹ca wspó³rzêdne lewego górnego rogu i prawego dolnego rogu widocznej dla u¿ytkownika czêœci planszy
 * @param[in, out] pozycja_mrowki struktura zawieraj¹ca informacje o mrówce
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
static void kolejny_krok_mrowki(bool** plansza, const int* szerokosc, const int* wysokosc, const prostokat* kawalek_planszy, mrowka* pozycja_mrowki, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do realizacji algorytmu "Mrówka Langtona".
 * @param[in,out] plansza tablica dwuwymiarowa, po której porusza siê mrówka
 * @param[in] szerokosc wskaŸnik na szerokoœæ planszy
 * @param[in] wysokosc wskaŸnik na wysokoœæ planszy
 * @param[in] sekundy czas w sekundach, po którym mrówka wykona kolejny krok
 * @param[in, out] informacja_o_mrowce struktura zawieraj¹ca informacje o mrówce
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void mrowka_langtona(bool** plansza, const int* szerokosc, const int* wysokosc, const int* sekundy, mrowka* informacja_o_mrowce, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do czyszczenia wskazanego wiersza konsoli od wskazanej kolumny.
 * @param[in] x wskaŸnik na wspó³rzêdna X
 * @param[in] y wskaŸnik na wspó³rzêdn¹ Y
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void wyczysc_wiersz(const short int* x, const short int* y, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do bezpiecznego wczytywania zmiennej typu int.
 * @note Funkcja zapobiega wczytaniu przez swcanf danej, która nie jest liczb¹ oraz czyœci bufor wejœciowy po wczytaniu danej
 * @param[in,out] zmienna zmienna, do której przypisywana bêdzie wartoœæ 
 * @param[in] komunikat ³añcuch znaków zawieraj¹cy treœæ komunikatu, który bêdzie wyœwietlony podczas wczytywania danej
 * @param[in] x_komunikatu wskaŸnik na wspó³rzêdn¹ X komunikatu, który bêdzie wyœwietlony podczas wczytywania danej
 * @param[in] y_komunikatu wskaŸnik na wspó³rzêdn¹ Y komunikatu, który bêdzie wyœwietlony podczas wczytywania danej
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void wczytaj_int(int* zmienna, const wchar_t* komunikat, const short int x_komunikatu, const short int y_komunikatu, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do wczytywania ³añcuchów znaków typu wchar_t o okreœlonej d³ugoœci.
 * @warning Funkcja nie sprawdza czy tablica posiada odpowiedni¹ d³ugoœæ, aby móc wczytaæ podan¹ iloœæ znaków
 * @param[in,out] lancuch ³añcuch znaków, do którego m¹j¹ zostaæ wczytane dane
 * @param[in] ilosc_znakow_do_wczytania maksymalna iloœæ znaków, która ma zostaæ wczytana do tablicy
 * @return Iloœæ odczytanych znaków. (int)
*/
int getwline(wchar_t* lancuch, const unsigned int ilosc_znakow_do_wczytania);

/** Funkcja s³u¿¹ca do wyœwietlania menu g³ównego.
 * @param[in] tablica_lancuchow tablica ³añcuchów typu wchar_t przechowuj¹ca opcje menu g³ównego
 * @param[in] ilosc_wierszy wskaŸnik na iloœæ wierszy do wyswietlenia
 * @param[in] wiersz_z_znacznikiem wskaŸnik na wiersz, na którego koñcu ma zostaæ wyœwietlona dodatkowo strza³ka
*/
void wyswietl_menu(const wchar_t tablica_lancuchow[][MAX_ILOSC_ZNAKOW_OPCJI_MENU], const unsigned short int* ilosc_wierszy, const unsigned short int* wiersz_z_znacznikiem);

/** Funkcja ustawiaj¹ca widocznoœæ kursora w konsoli.
 * @param[in] czy_widoczny okreœla czy kursor konsoli ma byæ widoczny dla u¿ytkownika
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void ustaw_widocznosc_kursora(const bool czy_widoczny, const HANDLE* uchwyt);

/** Funkcja ustawiaj¹ca kursor w konsoli.
 * @param[in] x wskaŸnik na wspó³rzêdn¹ X
 * @param[in] y wskaŸnik na wspó³rzêdn¹ Y
 * @param[in] uchwyt wskaŸnik na uchwyt do konsoli
*/
void ustaw_kursor(const short int* x, const short int* y, const HANDLE* uchwyt);

/** Funkcja s³u¿¹ca do obliczania liczby cyfr podanej liczby ca³kowitej bez znaku.
 * @param[in] liczba podana liczba
 * @return Iloœæ cyfr z jakiej sk³ada siê zmienna liczba. (int)
*/
int policz_cyfry_uint(unsigned int liczba);

/** Funkcja konwertuj¹ca liczbe ca³kowita bez znaku na ³añcuch znaków typu wchar_t.
 * @attention Nale¿y pamietaæ o zwolnieniu pamiêci zajmowanej przez nowo utworzony ³añcuch znaków 
 * @param[in] liczba podana liczba
 * @return WskaŸnik na dynamicznie zaalokowany ³añcuch znaków. (wchar_t*) 
*/
wchar_t* uint_na_wchar_t(unsigned int liczba);

/** Funkcja ³¹czaca dwa ³añcuchy znaków typu wchar_t.
 * @attention Nale¿y pamietaæ o zwolnieniu pamiêci zajmowanej przez nowo utworzony ³añcuch znaków
 * @param[in] str_1 ³añcuch znaków, do którego bêdzie doklejony ³añcuch str_2
 * @param[in] lz_1 d³ugoœæ ³añcucha znaków str_1
 * @param[in] str_2 ³añcuch znaków który bêdzie doklejony do ³añcucha znaków str_1
 * @param[in] lz_2 d³ugoœæ ³añcucha znaków str_2
 * @return WskaŸnik na dynamicznie zaalokowany ³añcuch znaków. (wchar_t*)
*/
wchar_t* scal_dwa_lancuchy_wchar_t(const wchar_t* str_1, unsigned int lz_1, const wchar_t* str_2, unsigned int lz_2);

#endif
