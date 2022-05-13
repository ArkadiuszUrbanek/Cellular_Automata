/** @file */
#ifndef struktury_h
#define struktury_h

#include "stale.h"

/** Struktura komórka s³u¿¹ca do tworzenia listy jednokierunkowej ¿ywych komórek */
typedef struct komorka {
	int wspolrzedna_x;        /**< indeks kolumny planszy, w której znajduje siê ¿ywa komórka */
	int wspolrzedna_y;        /**< indeks wiersza planszy, w której znajduje siê ¿ywa komórka */
	struct komorka* nastepna; /**< wskaŸnik na nastêpn¹ komórkê w liœcie jednokierunkowej komórek */
} komorka;

/** Struktura mrowka przechowuj¹ca informacje o jej po³o¿eniu na planszy i kierunek, w którym jest zwrócona */
typedef struct mrowka {
	int wspolrzedna_x;        /**< indeks kolumny planszy, w której znajduje siê mrówka */
	int wspolrzedna_y;        /**< indeks wiersza planszy, w której znajduje siê mrówka */
	enum kierunek kierunek;   /**< typ wyliczeniowy przechowuj¹cy informacjê o orientacji mrówki */
} mrowka;

/** Struktura prostok¹t s³u¿¹ca do przechowywania informacji o aktualnie widocznym kawa³ku planszy */
typedef struct prostokat {
	int wspolrzedna_x_lewego_gornego_rogu;  /**< indeks kolumny planszy, w której znajduje siê lewy górny róg widocznego kawa³ka planszy */
	int wspolrzedna_y_lewego_gornego_rogu;  /**< indeks wiersza planszy, w której znajduje siê lewy górny róg widocznego kawa³ka planszy */
	int wspolrzedna_x_prawego_dolnego_rogu; /**< indeks kolumny planszy, w której znajduje siê prawy dolny róg widocznego kawa³ka planszy */
	int wspolrzedna_y_prawego_dolnego_rogu; /**< indeks wiersza planszy, w której znajduje siê prawy dolny róg widocznego kawa³ka planszy */
} prostokat;

#endif