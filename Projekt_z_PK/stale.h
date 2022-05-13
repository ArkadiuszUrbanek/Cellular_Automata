/** @file */
#ifndef stale_h
#define stale_h

/** Typ wyliczeniowy kierunek s³u¿¹cy do okreœlania orientacji mrówki */
enum kierunek { 
	PRAWO, /**< kierunek PRAWO o wartoœci 0 */
	LEWO,  /**< kierunek LEWO o wartoœci 1 */
	GORA,  /**< kierunek GORA o wartoœci 2 */
	DOL    /**< kierunek DOL o wartoœci 3 */
};

/** Typ wyliczeniowy stale */
enum stale { 
	MAX_ILOSC_ZNAKOW_OPCJI_MENU = 25, /**< okreœla rozmiar najd³u¿szego s³owa w tablicy ³añcuchów znaków */
	SZEROKOSC_WIDOCZNEJ_PLANSZY = 50, /**< okreœla maksymaln¹ szerokoœæ planszy, któr¹ mo¿na zobaczyæ */
	WYSOKOSC_WIDOCZNEJ_PLANSZY = 50   /**< okreœla maksymaln¹ wysokoœæ planszy, któr¹ mo¿na zobaczyæ  */
};

/** Typ wyliczeniowy kody_klawiszy */
enum kody_klawiszy { 
	ENTER = 13,           /**< kod powrotu karetki */
	ESC = 27,             /**< kod klawisza ESC */
	SPACJA = 32,          /**< kod spacji */
	STRZALKA_W_GORE = 72, /**< kod strza³ki w górê */
	STRZALKA_W_DOL = 80,  /**< kod strza³ki w dó³ */
	STRZALKA_W_LEWO = 75, /**< kod strza³ki w lewo */
	STRZALKA_W_PRAWO = 77 /**< kod strza³ki w prawo */
};

#endif