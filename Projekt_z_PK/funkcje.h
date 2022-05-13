/** @file */
#ifndef funkcje_h
#define funkcje_h

#include <wchar.h>
#include <stdbool.h>
#include <windows.h>

#include "stale.h"
#include "struktury.h"

/** Funkcja statyczna u�ywana przez funkcj� @ref zaznacz_komorki_na_planszy()
 * @param[in] indeks_kolumny indeks kolumny, dla kt�rego ma zosta� wyznaczona kolumna, od kt�rej nale�y wy�wietli� plansz�
 * @return Indeks kolumny, od kt�rego powinna by� wy�wietlona plansza. (int)
*/
static int zbadaj_przedzial_dla_kolumny(int indeks_kolumny);

/** Funkcja statyczna u�ywana przez funkcj� @ref zaznacz_komorki_na_planszy()
 * @param[in] indeks_wiersza indeks wiersza, dla kt�rego ma zosta� wyznaczony wiersz, od kt�rego nale�y wy�wietli� plansz�
 * @return Indeks wiersza, od kt�rego powinna by� wy�wietlona plansza. (int)
*/
static int zbadaj_przedzial_dla_wiersza(int indeks_wiersza);

/** Funkcja statyczna u�ywana przez funkcj� @ref zaznacz_komorki_na_planszy() oraz funkcj� @ref gra_w_zycie()
 * Wy�wietla plansz� do gry w �ycie od konkretnych indeks�w. 
 * @param[in] plansza wska�nik na wska�nik na wchar_t s�u��cy do poruszania si� po tablicy
 * @param[in] szerokosc_planszy szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc_planszy wysoko�� planszy do gry w �ycie
 * @param[in] wskazany_wiersz wiersz, od kt�rego ma by� wy�wietlona plansza do gry w �ycie
 * @param[in] wskazana_kolumna kolumna, od kt�rej ma by� wy�wietlona plansza do gry w �ycie
*/
static void wyswietl_plansze_od_indeksow(wchar_t** plansza, int szerokosc_planszy, int wysokosc_planszy, int wskazany_wiersz, int wskazana_kolumna);

/** Funkcja s�u��ca do zaznaczania kom�rek na planszy do gry w �ycie.
 * @param[in,out] plansza tablica dwuwymiarowa do gry w �ycie o nazwie plansza
 * @param[in] szerokosc wska�nik na szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc wska�nik na wysoko�� planszy do gry w �ycie
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void zaznacz_komorki_na_planszy(wchar_t** plansza, const int* szerokosc, const int* wysokosc, const HANDLE* uchwyt);

/** Funkcja dodaj�ca kom�rk� na koniec listy jednokierunkowej.  
 * @param[in,out] ppglowa wska�nik na wska�nik na g�ow� listy 
 * @param[in] x wska�nik na wsp�rz�dn� X
 * @param[in] y wska�nik na wsp�rz�dn� Y
*/
void wstaw_komorke_do_listy(komorka** ppglowa, const int* x, const int* y);

/** Funkcja usuwaj�ca list� jednokierunkow� kom�rek.
 * @param[in,out] ppglowa wska�nik na wska�nik na g�ow� listy
*/
void usun_liste_komorek(komorka** ppglowa);

/** Funkcja usuwaj�ca jedn� kom�rk� z ko�ca listy jednokierunkowej. 
 * @param[in,out] ppglowa wska�nik na wska�nik na g�ow� listy
*/
void usun_komorke_z_konca_listy(komorka** ppglowa);

/** Funkcja nadpisuj�ca dane wybranej kom�rki z listy kom�rek.
 * @param[in] pglowa wska�nik na g�ow� listy
 * @param[in] x wska�nik na wsp�rz�dn� X
 * @param[in] y wska�nik na wsp�rz�dn� Y
 * @param[in] wybrana_komorka wska�nik na numer kom�rki, kt�rej dane maj� zosta� nadpisane
*/
void zmien_wspolrzedne_komorki(komorka* pglowa, const int* x, const int* y, const int* wybrana_komorka);

/** Funkcja statyczna u�ywana przez funkcj� @ref gra_w_zycie()
 * Uaktualnia plansz� do gry w �ycie o nowe pokolenie.
 * @param[in,out] plansza tablica dwuwymiarowa do gry w �ycie o nazwie plansza
 * @param[in] szerokosc wska�nik na szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc wska�nik na wysoko�� planszy do gry w �ycie
 * @param[in,out] ppglowa wska�nik na wska�nik na g�ow� listy 
 * @param[in] poprzednia_dlugosc_listy wska�nik na d�ugo�� listy jednokierunkowej �ywych kom�rek
*/
static void nowe_pokolenie(wchar_t** plansza, const int* szerokosc, const int* wysokosc, komorka **ppglowa, int* poprzednia_dlugosc_listy);

/** Funkcja s�u��ca do realizowania algorytmu automatu kom�rkowego "Gra w �ycie".
 * @param[in,out] plansza tablica dwuwymiarowa do gry w �ycie o nazwie plansza
 * @param[in] szerokosc wska�nik na szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc wska�nik na wysoko�� planszy do gry w �ycie
 * @param[in] sekundy czas �ycia jednego pokolenia wyrazony w sekundach
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
 * @return Wska�nik na struktur�. (komorka*)
*/
komorka* gra_w_zycie(wchar_t** plansza, const int* szerokosc, const int* wysokosc, const int* sekundy, const HANDLE* uchwyt);

/** Funkcja s�u��ca do zapisu gry w �ycie.
 * @param[in] nazwa_pliku �a�cuch znak�w z nazw� pliku
 * @param[in] pglowa wska�nik na g�ow� listy jednokierunkowej �ywych kom�rek
 * @param[in] szerokosc wska�nik na szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc wska�nik na wysoko�� planszy do gry w �ycie
 * @return Warto�� true lub false
*/
bool zapisz_gre_w_zycie(const wchar_t nazwa_pliku[], komorka* pglowa, const int* szerokosc, const int* wysokosc);

/** Funkcja s�u��ca do odczytu gry w �ycie.
 * Sprawdza ona r�wnie� poprawno�� sk�adni pliku. 
 * @param[in] nazwa_pliku �a�cuch znak�w z nazw� pliku
 * @param[in,out] ppglowa wska�nik na wska�nik na g�ow� listy jednokierunkowej �ywych kom�rek
 * @param[in] szerokosc wska�nik na szeroko�� planszy do gry w �ycie
 * @param[in] wysokosc wska�nik na wysoko�� planszy do gry w �ycie
 * @return Warto�� true lub false
*/
bool odczytaj_gre_w_zycie(const wchar_t nazwa_pliku[], komorka** ppglowa, int* szerokosc, int* wysokosc);

/** Funkcja statyczna u�ywana przez funkcj� @ref mrowka_langtona()
 * Wy�wietla widzian� przez u�ytkownika cz�� planszy.
 * @param[in] plansza tablica dwuwymiarowa, po kt�rej porusza si� mr�wka
 * @param[in] kawalek_planszy struktura zawieraj�ca wsp�rz�dne lewego g�rnego rogu i prawego dolnego rogu widocznej dla u�ytkownika cz�ci planszy
 * @param[in] pozycja_mrowki struktura zawieraj�ca informacje o mr�wce
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
static void odswiez_plansze_dla_mrowki_langtona(const bool** plansza, const prostokat* kawalek_planszy, const mrowka* pozycja_mrowki, const HANDLE* uchwyt);

/** Funkcja statyczna uzywana przez funkcj� @ref mrowka_langtona()
 * Uaktualnia plansz� do gry o kolejny krok mr�wki oraz dodatkowo wy�wietla wprowadzone zmiany na ekranie konsoli, tylko je�eli b�d� one widoczne dla u�ytkownika.
 * @param[in,out] plansza tablica dwuwymiarowa, po kt�rej porusza si� mr�wka
 * @param[in] szerokosc wska�nik na szeroko�� planszy
 * @param[in] wysokosc wska�nik na wysoko�� planszy
 * @param[in] kawalek_planszy struktura zawieraj�ca wsp�rz�dne lewego g�rnego rogu i prawego dolnego rogu widocznej dla u�ytkownika cz�ci planszy
 * @param[in, out] pozycja_mrowki struktura zawieraj�ca informacje o mr�wce
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
static void kolejny_krok_mrowki(bool** plansza, const int* szerokosc, const int* wysokosc, const prostokat* kawalek_planszy, mrowka* pozycja_mrowki, const HANDLE* uchwyt);

/** Funkcja s�u��ca do realizacji algorytmu "Mr�wka Langtona".
 * @param[in,out] plansza tablica dwuwymiarowa, po kt�rej porusza si� mr�wka
 * @param[in] szerokosc wska�nik na szeroko�� planszy
 * @param[in] wysokosc wska�nik na wysoko�� planszy
 * @param[in] sekundy czas w sekundach, po kt�rym mr�wka wykona kolejny krok
 * @param[in, out] informacja_o_mrowce struktura zawieraj�ca informacje o mr�wce
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void mrowka_langtona(bool** plansza, const int* szerokosc, const int* wysokosc, const int* sekundy, mrowka* informacja_o_mrowce, const HANDLE* uchwyt);

/** Funkcja s�u��ca do czyszczenia wskazanego wiersza konsoli od wskazanej kolumny.
 * @param[in] x wska�nik na wsp�rz�dna X
 * @param[in] y wska�nik na wsp�rz�dn� Y
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void wyczysc_wiersz(const short int* x, const short int* y, const HANDLE* uchwyt);

/** Funkcja s�u��ca do bezpiecznego wczytywania zmiennej typu int.
 * @note Funkcja zapobiega wczytaniu przez swcanf danej, kt�ra nie jest liczb� oraz czy�ci bufor wej�ciowy po wczytaniu danej
 * @param[in,out] zmienna zmienna, do kt�rej przypisywana b�dzie warto�� 
 * @param[in] komunikat �a�cuch znak�w zawieraj�cy tre�� komunikatu, kt�ry b�dzie wy�wietlony podczas wczytywania danej
 * @param[in] x_komunikatu wska�nik na wsp�rz�dn� X komunikatu, kt�ry b�dzie wy�wietlony podczas wczytywania danej
 * @param[in] y_komunikatu wska�nik na wsp�rz�dn� Y komunikatu, kt�ry b�dzie wy�wietlony podczas wczytywania danej
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void wczytaj_int(int* zmienna, const wchar_t* komunikat, const short int x_komunikatu, const short int y_komunikatu, const HANDLE* uchwyt);

/** Funkcja s�u��ca do wczytywania �a�cuch�w znak�w typu wchar_t o okre�lonej d�ugo�ci.
 * @warning Funkcja nie sprawdza czy tablica posiada odpowiedni� d�ugo��, aby m�c wczyta� podan� ilo�� znak�w
 * @param[in,out] lancuch �a�cuch znak�w, do kt�rego m�j� zosta� wczytane dane
 * @param[in] ilosc_znakow_do_wczytania maksymalna ilo�� znak�w, kt�ra ma zosta� wczytana do tablicy
 * @return Ilo�� odczytanych znak�w. (int)
*/
int getwline(wchar_t* lancuch, const unsigned int ilosc_znakow_do_wczytania);

/** Funkcja s�u��ca do wy�wietlania menu g��wnego.
 * @param[in] tablica_lancuchow tablica �a�cuch�w typu wchar_t przechowuj�ca opcje menu g��wnego
 * @param[in] ilosc_wierszy wska�nik na ilo�� wierszy do wyswietlenia
 * @param[in] wiersz_z_znacznikiem wska�nik na wiersz, na kt�rego ko�cu ma zosta� wy�wietlona dodatkowo strza�ka
*/
void wyswietl_menu(const wchar_t tablica_lancuchow[][MAX_ILOSC_ZNAKOW_OPCJI_MENU], const unsigned short int* ilosc_wierszy, const unsigned short int* wiersz_z_znacznikiem);

/** Funkcja ustawiaj�ca widoczno�� kursora w konsoli.
 * @param[in] czy_widoczny okre�la czy kursor konsoli ma by� widoczny dla u�ytkownika
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void ustaw_widocznosc_kursora(const bool czy_widoczny, const HANDLE* uchwyt);

/** Funkcja ustawiaj�ca kursor w konsoli.
 * @param[in] x wska�nik na wsp�rz�dn� X
 * @param[in] y wska�nik na wsp�rz�dn� Y
 * @param[in] uchwyt wska�nik na uchwyt do konsoli
*/
void ustaw_kursor(const short int* x, const short int* y, const HANDLE* uchwyt);

/** Funkcja s�u��ca do obliczania liczby cyfr podanej liczby ca�kowitej bez znaku.
 * @param[in] liczba podana liczba
 * @return Ilo�� cyfr z jakiej sk�ada si� zmienna liczba. (int)
*/
int policz_cyfry_uint(unsigned int liczba);

/** Funkcja konwertuj�ca liczbe ca�kowita bez znaku na �a�cuch znak�w typu wchar_t.
 * @attention Nale�y pamieta� o zwolnieniu pami�ci zajmowanej przez nowo utworzony �a�cuch znak�w 
 * @param[in] liczba podana liczba
 * @return Wska�nik na dynamicznie zaalokowany �a�cuch znak�w. (wchar_t*) 
*/
wchar_t* uint_na_wchar_t(unsigned int liczba);

/** Funkcja ��czaca dwa �a�cuchy znak�w typu wchar_t.
 * @attention Nale�y pamieta� o zwolnieniu pami�ci zajmowanej przez nowo utworzony �a�cuch znak�w
 * @param[in] str_1 �a�cuch znak�w, do kt�rego b�dzie doklejony �a�cuch str_2
 * @param[in] lz_1 d�ugo�� �a�cucha znak�w str_1
 * @param[in] str_2 �a�cuch znak�w kt�ry b�dzie doklejony do �a�cucha znak�w str_1
 * @param[in] lz_2 d�ugo�� �a�cucha znak�w str_2
 * @return Wska�nik na dynamicznie zaalokowany �a�cuch znak�w. (wchar_t*)
*/
wchar_t* scal_dwa_lancuchy_wchar_t(const wchar_t* str_1, unsigned int lz_1, const wchar_t* str_2, unsigned int lz_2);

#endif
