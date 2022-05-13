/** @file */
#ifndef struktury_h
#define struktury_h

#include "stale.h"

/** Struktura kom�rka s�u��ca do tworzenia listy jednokierunkowej �ywych kom�rek */
typedef struct komorka {
	int wspolrzedna_x;        /**< indeks kolumny planszy, w kt�rej znajduje si� �ywa kom�rka */
	int wspolrzedna_y;        /**< indeks wiersza planszy, w kt�rej znajduje si� �ywa kom�rka */
	struct komorka* nastepna; /**< wska�nik na nast�pn� kom�rk� w li�cie jednokierunkowej kom�rek */
} komorka;

/** Struktura mrowka przechowuj�ca informacje o jej po�o�eniu na planszy i kierunek, w kt�rym jest zwr�cona */
typedef struct mrowka {
	int wspolrzedna_x;        /**< indeks kolumny planszy, w kt�rej znajduje si� mr�wka */
	int wspolrzedna_y;        /**< indeks wiersza planszy, w kt�rej znajduje si� mr�wka */
	enum kierunek kierunek;   /**< typ wyliczeniowy przechowuj�cy informacj� o orientacji mr�wki */
} mrowka;

/** Struktura prostok�t s�u��ca do przechowywania informacji o aktualnie widocznym kawa�ku planszy */
typedef struct prostokat {
	int wspolrzedna_x_lewego_gornego_rogu;  /**< indeks kolumny planszy, w kt�rej znajduje si� lewy g�rny r�g widocznego kawa�ka planszy */
	int wspolrzedna_y_lewego_gornego_rogu;  /**< indeks wiersza planszy, w kt�rej znajduje si� lewy g�rny r�g widocznego kawa�ka planszy */
	int wspolrzedna_x_prawego_dolnego_rogu; /**< indeks kolumny planszy, w kt�rej znajduje si� prawy dolny r�g widocznego kawa�ka planszy */
	int wspolrzedna_y_prawego_dolnego_rogu; /**< indeks wiersza planszy, w kt�rej znajduje si� prawy dolny r�g widocznego kawa�ka planszy */
} prostokat;

#endif