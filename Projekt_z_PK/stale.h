/** @file */
#ifndef stale_h
#define stale_h

/** Typ wyliczeniowy kierunek s�u��cy do okre�lania orientacji mr�wki */
enum kierunek { 
	PRAWO, /**< kierunek PRAWO o warto�ci 0 */
	LEWO,  /**< kierunek LEWO o warto�ci 1 */
	GORA,  /**< kierunek GORA o warto�ci 2 */
	DOL    /**< kierunek DOL o warto�ci 3 */
};

/** Typ wyliczeniowy stale */
enum stale { 
	MAX_ILOSC_ZNAKOW_OPCJI_MENU = 25, /**< okre�la rozmiar najd�u�szego s�owa w tablicy �a�cuch�w znak�w */
	SZEROKOSC_WIDOCZNEJ_PLANSZY = 50, /**< okre�la maksymaln� szeroko�� planszy, kt�r� mo�na zobaczy� */
	WYSOKOSC_WIDOCZNEJ_PLANSZY = 50   /**< okre�la maksymaln� wysoko�� planszy, kt�r� mo�na zobaczy�  */
};

/** Typ wyliczeniowy kody_klawiszy */
enum kody_klawiszy { 
	ENTER = 13,           /**< kod powrotu karetki */
	ESC = 27,             /**< kod klawisza ESC */
	SPACJA = 32,          /**< kod spacji */
	STRZALKA_W_GORE = 72, /**< kod strza�ki w g�r� */
	STRZALKA_W_DOL = 80,  /**< kod strza�ki w d� */
	STRZALKA_W_LEWO = 75, /**< kod strza�ki w lewo */
	STRZALKA_W_PRAWO = 77 /**< kod strza�ki w prawo */
};

#endif