#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "funkcje.h"
#include "struktury.h"
#include "stale.h"

#define ROZMIAR_BUFORA 30


static int zbadaj_przedzial_dla_kolumny(int indeks_kolumny) {
	int zakres = 0;
	while (true) {
		if (zakres <= indeks_kolumny && indeks_kolumny < zakres + SZEROKOSC_WIDOCZNEJ_PLANSZY) {
			break;
		}
		zakres += SZEROKOSC_WIDOCZNEJ_PLANSZY;
	}
	return zakres;
}

static int zbadaj_przedzial_dla_wiersza(int indeks_wiersza) {
	int zakres = 0;
	while (true) {
		if (zakres <= indeks_wiersza && indeks_wiersza < zakres + WYSOKOSC_WIDOCZNEJ_PLANSZY) {
			break;
		}
		zakres += WYSOKOSC_WIDOCZNEJ_PLANSZY;
	}
	return zakres;
}

static void wyswietl_plansze_od_indeksow(wchar_t** plansza, int szerokosc_planszy, int wysokosc_planszy, int wskazany_wiersz, int wskazana_kolumna) {
	system("cls");

	int zakres_x = (szerokosc_planszy <= SZEROKOSC_WIDOCZNEJ_PLANSZY) ? szerokosc_planszy : (szerokosc_planszy - wskazana_kolumna >= SZEROKOSC_WIDOCZNEJ_PLANSZY) ? wskazana_kolumna + SZEROKOSC_WIDOCZNEJ_PLANSZY : szerokosc_planszy;
	int zakres_y = (wysokosc_planszy <= WYSOKOSC_WIDOCZNEJ_PLANSZY) ? wysokosc_planszy : (wysokosc_planszy - wskazany_wiersz >= WYSOKOSC_WIDOCZNEJ_PLANSZY) ? wskazany_wiersz + WYSOKOSC_WIDOCZNEJ_PLANSZY : wysokosc_planszy;

	for (int w = wskazany_wiersz; w < zakres_y; w++) {
		for (int k = wskazana_kolumna; k < zakres_x; k++) {
			wprintf(L"%lc", plansza[w][k]);

		}
		if(w != zakres_y-1) wprintf(L"\n");

	}
}

void zaznacz_komorki_na_planszy(wchar_t** plansza, const int *szerokosc, const int *wysokosc, const HANDLE *uchwyt) {
	COORD pozycja_kursora = { 0, 0 };
	int aktualny_indeks_wiersza = 0, aktualny_indeks_kolumny = 0;
	char odczytany_znak;

	wchar_t str1[] = L"Aktualny indeks X: ", str2[] = L" Y: ";
	wchar_t *pstr_poz_x, *pstr_poz_y, *pstr_scalony1, *pstr_scalony2, *pstr_scalony3;

	wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
	ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);

	do {

		pstr_poz_x = uint_na_wchar_t(aktualny_indeks_kolumny);
		pstr_poz_y = uint_na_wchar_t(aktualny_indeks_wiersza);
		
		pstr_scalony1 = scal_dwa_lancuchy_wchar_t(str1, wcslen(str1), pstr_poz_x, policz_cyfry_uint(aktualny_indeks_kolumny));
		pstr_scalony2 = scal_dwa_lancuchy_wchar_t(str2, wcslen(str2), pstr_poz_y, policz_cyfry_uint(aktualny_indeks_wiersza));
		pstr_scalony3 = scal_dwa_lancuchy_wchar_t(pstr_scalony1, wcslen(str1) + policz_cyfry_uint(aktualny_indeks_kolumny), pstr_scalony2, wcslen(str2) + policz_cyfry_uint(aktualny_indeks_wiersza));


		SetConsoleTitle(pstr_scalony3);

		free(pstr_poz_x);
		free(pstr_poz_y);
		free(pstr_scalony1);
		free(pstr_scalony2);
		free(pstr_scalony3);

		odczytany_znak = _getch();

		switch (odczytany_znak) {
			case STRZALKA_W_GORE:	aktualny_indeks_wiersza--;
									if (aktualny_indeks_wiersza == -1) {
										aktualny_indeks_wiersza = *wysokosc - 1;
										if (*wysokosc % WYSOKOSC_WIDOCZNEJ_PLANSZY != 0 && *wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza - aktualny_indeks_wiersza % WYSOKOSC_WIDOCZNEJ_PLANSZY, zbadaj_przedzial_dla_kolumny(aktualny_indeks_kolumny));
										}
									}


									pozycja_kursora.Y = aktualny_indeks_wiersza % WYSOKOSC_WIDOCZNEJ_PLANSZY;

									if (pozycja_kursora.Y == WYSOKOSC_WIDOCZNEJ_PLANSZY - 1 && *wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
										wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza - WYSOKOSC_WIDOCZNEJ_PLANSZY + 1, zbadaj_przedzial_dla_kolumny(aktualny_indeks_kolumny));
									}

									ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);
									
									break;

			case STRZALKA_W_PRAWO:	aktualny_indeks_kolumny++;
									if (aktualny_indeks_kolumny == *szerokosc) {
										aktualny_indeks_kolumny = 0;
									}

									pozycja_kursora.X = aktualny_indeks_kolumny % SZEROKOSC_WIDOCZNEJ_PLANSZY;

									if (pozycja_kursora.X == 0 && *szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
										wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, zbadaj_przedzial_dla_wiersza(aktualny_indeks_wiersza), aktualny_indeks_kolumny);
									}

									ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);

									break;
									
			case STRZALKA_W_LEWO:	aktualny_indeks_kolumny--;
									if (aktualny_indeks_kolumny == -1) {
										aktualny_indeks_kolumny = *szerokosc - 1;
										if (*szerokosc % SZEROKOSC_WIDOCZNEJ_PLANSZY != 0 && *szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, zbadaj_przedzial_dla_wiersza(aktualny_indeks_wiersza), aktualny_indeks_kolumny - aktualny_indeks_kolumny % SZEROKOSC_WIDOCZNEJ_PLANSZY);
										}
									}

									pozycja_kursora.X = aktualny_indeks_kolumny % SZEROKOSC_WIDOCZNEJ_PLANSZY;

									if (pozycja_kursora.X == SZEROKOSC_WIDOCZNEJ_PLANSZY - 1 && *szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
										wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, zbadaj_przedzial_dla_wiersza(aktualny_indeks_wiersza), aktualny_indeks_kolumny - SZEROKOSC_WIDOCZNEJ_PLANSZY + 1);
									}

									ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);

									break;

			case STRZALKA_W_DOL:	aktualny_indeks_wiersza++;
									if (aktualny_indeks_wiersza == *wysokosc) {
										aktualny_indeks_wiersza = 0;
									}

									pozycja_kursora.Y = aktualny_indeks_wiersza % WYSOKOSC_WIDOCZNEJ_PLANSZY;

									if (pozycja_kursora.Y == 0 && *wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
										wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, zbadaj_przedzial_dla_kolumny(aktualny_indeks_kolumny));
									}

									ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);

									break;

			case SPACJA:			if (plansza[aktualny_indeks_wiersza][aktualny_indeks_kolumny] == 0x2588) {
										plansza[aktualny_indeks_wiersza][aktualny_indeks_kolumny] = L'.';
										wprintf(L"%lc", '.');

									} else if (plansza[aktualny_indeks_wiersza][aktualny_indeks_kolumny] == L'.'){
										plansza[aktualny_indeks_wiersza][aktualny_indeks_kolumny] = 0x2588;
										wprintf(L"%lc", 0x2588);
									}

									ustaw_kursor(&pozycja_kursora.X, &pozycja_kursora.Y, uchwyt);
									break;

			default:				break;

		}

	} while (odczytany_znak != ENTER);
}

void wstaw_komorke_do_listy(komorka** ppglowa, const int* x, const int* y) {
	if (*ppglowa == NULL) {
		if (*ppglowa = (komorka*)malloc(sizeof(komorka))) {
			(*ppglowa)->wspolrzedna_x = *x;
			(*ppglowa)->wspolrzedna_y = *y;
			(*ppglowa)->nastepna = NULL;
		}
	}
	else {
		komorka* pom = *ppglowa;
		while (pom->nastepna != NULL) {
			pom = pom->nastepna;
		}
		if (pom->nastepna = (komorka*)malloc(sizeof(komorka))) {
			pom->nastepna->wspolrzedna_x = *x;
			pom->nastepna->wspolrzedna_y = *y;
			pom->nastepna->nastepna = NULL;
		}
	}
}

void usun_liste_komorek(komorka** ppglowa) {
	while (*ppglowa != NULL) {
		komorka* pom = (*ppglowa)->nastepna;
		free(*ppglowa);
		*ppglowa = pom;
	}
}

void usun_komorke_z_konca_listy(komorka** ppglowa) {
	if (*ppglowa != NULL) {
		if ((*ppglowa)->nastepna == NULL) {
			free(*ppglowa);
			*ppglowa = NULL;
		}
		else {
			komorka* pom = *ppglowa;
			while (pom->nastepna->nastepna != NULL)
				pom = pom->nastepna;

			free(pom->nastepna);
			pom->nastepna = NULL;
		}
	}
}

void zmien_wspolrzedne_komorki(komorka *pglowa, const int *x, const int *y, const int* wybrana_komorka) {
	if (pglowa != NULL){
		int licznik = 1;

		for (licznik; licznik < *wybrana_komorka; licznik++) {
			if (pglowa->nastepna == NULL) break;
			pglowa = pglowa->nastepna;
		}
		
		if (licznik == *wybrana_komorka) pglowa->wspolrzedna_x = *x, pglowa->wspolrzedna_y = *y;
	}
}

static void nowe_pokolenie(wchar_t** plansza, const int* szerokosc, const int* wysokosc, komorka** ppglowa, int* poprzednia_dlugosc_listy) {
	int y_sasiada = 0, x_sasiada = 0, aktualna_dlugosc_listy = 0;


	for (int y_komorki = 0; y_komorki < *wysokosc; y_komorki++) {
		for (int x_komorki = 0; x_komorki < *szerokosc; x_komorki++) {
			int ilosc_zywych_sasiadow = 0;
			for (int y = -1; y < 2; y++) {
				if (y_komorki + y < 0) {
					y_sasiada = *wysokosc - 1;
				} else if (y_komorki + y > *wysokosc - 1) {
					y_sasiada = 0;
				} else {
					y_sasiada = y + y_komorki;
				}
				for (int x = -1; x < 2; x++) {
					if (x_komorki + x < 0) {
						x_sasiada = *szerokosc - 1;
					} else if (x_komorki + x > *szerokosc - 1) {
						x_sasiada = 0;
					} else {
						x_sasiada = x + x_komorki;
					}
					
					if (!(y == 0 && x == 0) && plansza[y_sasiada][x_sasiada] == 0x2588) ilosc_zywych_sasiadow++;

				}

			}

			if ((ilosc_zywych_sasiadow == 3 && plansza[y_komorki][x_komorki] == L'.') || ((ilosc_zywych_sasiadow == 2 || ilosc_zywych_sasiadow == 3) && plansza[y_komorki][x_komorki] == 0x2588)) {
				aktualna_dlugosc_listy++;
				if (aktualna_dlugosc_listy <= *poprzednia_dlugosc_listy) {
					zmien_wspolrzedne_komorki(*ppglowa, &x_komorki, &y_komorki, &aktualna_dlugosc_listy);
				} else {
					wstaw_komorke_do_listy(ppglowa, &x_komorki, &y_komorki);
				}
			}

		}
	}

	

		if (aktualna_dlugosc_listy < *poprzednia_dlugosc_listy) {
			int ilosc_iteracji = *poprzednia_dlugosc_listy - aktualna_dlugosc_listy;
			while (ilosc_iteracji != 0) {
				usun_komorke_z_konca_listy(ppglowa);
				ilosc_iteracji--;
			}
		}


		*poprzednia_dlugosc_listy = aktualna_dlugosc_listy;


		if (aktualna_dlugosc_listy != 0) {
			komorka* pom = *ppglowa;
			for (int y_komorki = 0; y_komorki < *wysokosc; y_komorki++) {
				for (int x_komorki = 0; x_komorki < *szerokosc; x_komorki++) {
					if (y_komorki == pom->wspolrzedna_y && x_komorki == pom->wspolrzedna_x) {
						plansza[y_komorki][x_komorki] = 0x2588;
						if (pom->nastepna != NULL) pom = pom->nastepna;
					} else {
						plansza[y_komorki][x_komorki] = L'.';
					}
				}
			}

		} else {
			for (int y_komorki = 0; y_komorki < *wysokosc; y_komorki++) {
				for (int x_komorki = 0; x_komorki < *szerokosc; x_komorki++) {
					if (plansza[y_komorki][x_komorki] == 0x2588) plansza[y_komorki][x_komorki] = L'.';
				}
			}
		
		}
	
}

komorka* gra_w_zycie(wchar_t** plansza, const int *szerokosc, const int *wysokosc, const int *sekundy, const HANDLE* uchwyt) {
	int aktualny_indeks_wiersza = 0, aktualny_indeks_kolumny = 0, poprzednia_dlugosc_listy = 0;
	unsigned int generacja = 0;
	komorka* pglowa = NULL;
	char odczytany_znak;
	wchar_t str[] = L"Gra w życie Conwaya - Generacja: ", *pstr_generacja = NULL, *pstr_tytul = NULL;
	
	SetConsoleTitle(L"Gra w życie Conwaya - Generacja: 0");
	wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
	ustaw_widocznosc_kursora(FALSE, uchwyt);
	
	clock_t czas_zycia_pokolenia = *sekundy * CLOCKS_PER_SEC, czas_rozpoczecia = clock();
	
	while (true) {
	
		if (czas_rozpoczecia + czas_zycia_pokolenia < clock()) {
			nowe_pokolenie(plansza, szerokosc, wysokosc, &pglowa, &poprzednia_dlugosc_listy);
			wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
		
			generacja++;
			pstr_generacja = uint_na_wchar_t(generacja);
			pstr_tytul = scal_dwa_lancuchy_wchar_t(str, wcslen(str), pstr_generacja, policz_cyfry_uint(generacja));
		
			SetConsoleTitle(pstr_tytul);
		
			free(pstr_generacja);
			free(pstr_tytul);
		
			czas_rozpoczecia = clock();
		}
	
		if(_kbhit() !=  0) {
			odczytany_znak = _getch();
	
			switch (odczytany_znak) {
				case STRZALKA_W_GORE:	if (*wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
										aktualny_indeks_wiersza -= WYSOKOSC_WIDOCZNEJ_PLANSZY;
											
											if (aktualny_indeks_wiersza < 0) {
												if (*wysokosc % WYSOKOSC_WIDOCZNEJ_PLANSZY != 0) {
													aktualny_indeks_wiersza = *wysokosc - *wysokosc % WYSOKOSC_WIDOCZNEJ_PLANSZY;
												} else {
													aktualny_indeks_wiersza = *wysokosc - WYSOKOSC_WIDOCZNEJ_PLANSZY;
												}
											}
	
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
	
										}
	
										break;
	
				case STRZALKA_W_PRAWO:	if (*szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_indeks_kolumny += SZEROKOSC_WIDOCZNEJ_PLANSZY;
	
											if (aktualny_indeks_kolumny >= *szerokosc) {
												aktualny_indeks_kolumny = 0;
											}
	
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
											
										}
	
										break;
	
				case STRZALKA_W_LEWO:	if (*szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
										aktualny_indeks_kolumny -= SZEROKOSC_WIDOCZNEJ_PLANSZY;
	
											if (aktualny_indeks_kolumny < 0) {
												if (*szerokosc % SZEROKOSC_WIDOCZNEJ_PLANSZY != 0) {
													aktualny_indeks_kolumny = *szerokosc - *szerokosc % SZEROKOSC_WIDOCZNEJ_PLANSZY;
												} else {
													aktualny_indeks_kolumny = *szerokosc - SZEROKOSC_WIDOCZNEJ_PLANSZY;
												}
											}
	
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
											
										}
										
										break;
	
				case STRZALKA_W_DOL:	if (*wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_indeks_wiersza += WYSOKOSC_WIDOCZNEJ_PLANSZY;
	
											if (aktualny_indeks_wiersza >= *wysokosc) {
												aktualny_indeks_wiersza = 0;
											}
	
											wyswietl_plansze_od_indeksow(plansza, *szerokosc, *wysokosc, aktualny_indeks_wiersza, aktualny_indeks_kolumny);
											
										}
										
										break;
	
				case 'p':				{
										
										clock_t czas_do_odswiezenia = czas_rozpoczecia + czas_zycia_pokolenia - clock();
										while (_getch() != 'p') continue;
										czas_rozpoczecia = clock() + czas_do_odswiezenia - czas_zycia_pokolenia;
	
										break;
	
										}
										
				case ESC:				ustaw_widocznosc_kursora(TRUE, uchwyt);
										system("cls");
										return pglowa;
	
				default:				break;
				
			}
	
		}
	
	}
	
}

bool zapisz_gre_w_zycie(const wchar_t nazwa_pliku[], komorka* pglowa, const int* szerokosc, const int* wysokosc) {
	FILE* wsk_plik;
	int linia = 1;

	if ((wsk_plik = _wfopen(nazwa_pliku, L"wt, ccs=UTF-8")) != NULL) {
		while (pglowa != NULL) {
			switch (linia) {
				case 1: fwprintf(wsk_plik, L"PLANSZA:\n");
						break;

				case 2: fwprintf(wsk_plik, L"szerokość = ");
						fwprintf(wsk_plik, L"%d\n", *szerokosc);
						break;

				case 3: fwprintf(wsk_plik, L"wysokość = ");
						fwprintf(wsk_plik, L"%d\n", *wysokosc);
						break;

				case 4: fwprintf(wsk_plik, L"\n");
						break;

				case 5: fwprintf(wsk_plik, L"ŻYWE KOMÓRKI:\n");
						break;

				default: fwprintf(wsk_plik, L"x = %d y = %d\n", pglowa->wspolrzedna_x, pglowa->wspolrzedna_y);
						 pglowa = pglowa->nastepna;
						 break;
			}
			linia++;
		}

		fclose(wsk_plik);
		return true;
	} else {
		return false;
	}

}

bool odczytaj_gre_w_zycie(const wchar_t nazwa_pliku[], komorka** ppglowa, int* szerokosc, int* wysokosc) {
	FILE* wsk_plik;
	wchar_t bufor[ROZMIAR_BUFORA] = L"";
	wint_t znak_nl;
	int wartosc_zwrocona_fwscanf, linia = 1;
	bool ciaglosc_danych = true;

	if ((wsk_plik = _wfopen(nazwa_pliku, L"rt, ccs=UTF-8")) != NULL) {
		while ((wartosc_zwrocona_fwscanf = fwscanf(wsk_plik, L"%[^\n]ls", bufor)) != EOF) {
			znak_nl = getwc(wsk_plik);

			switch (linia) {
				case 1: if (wartosc_zwrocona_fwscanf == 1 && wcscmp(L"PLANSZA:", bufor) == 0) {
							linia++;
							break;
						} else {
							return false;
						}
						
				case 2: if (wartosc_zwrocona_fwscanf == 1 && wcsncmp(L"szerokość = ", bufor, 12) == 0) {
							if (swscanf(bufor, L"%*ls %*lc %d", szerokosc) == 1 && *szerokosc > 0 && wcslen(bufor) == 12 + policz_cyfry_uint(*szerokosc)) {
								linia++;
								break;
							} else {
								return false;
							}
						} else {
							return false;
						}

				case 3: if (wartosc_zwrocona_fwscanf == 1 && wcsncmp(L"wysokość = ", bufor, 11) == 0) {
							if (swscanf(bufor, L"%*ls %*lc %d", wysokosc) == 1 && *wysokosc > 0 && wcslen(bufor) == 11 + policz_cyfry_uint(*wysokosc)) {
								linia++;
								break;
							} else {
								return false;
							}
						} else {
							return false;
						}

				case 4: if (wartosc_zwrocona_fwscanf == 0) {
							linia++;
							break;
						} else {
							return false;
						}

				case 5: if (wartosc_zwrocona_fwscanf == 1 && wcscmp(L"ŻYWE KOMÓRKI:", bufor) == 0) {
							linia++;
							break;
						} else {
							return false;
						}

				default: if (linia == 6 && wartosc_zwrocona_fwscanf == 0) return false;
						 
						 if (wartosc_zwrocona_fwscanf == 1 && ciaglosc_danych == true) {
							 wchar_t str_x[5] = L"", str_y[6] = L"";
							 int x, y;

							 if (swscanf(bufor, L"%4[^0-9]%d%5[^0-9]%d", str_x, &x, str_y, &y) == 4 && wcscmp(L"x = ", str_x) == 0 && wcscmp(L" y = ", str_y) == 0 && x > -1 && x < *szerokosc && y > -1 && y < *wysokosc && wcslen(bufor) == 9 + policz_cyfry_uint(x) + policz_cyfry_uint(y)) {
								 wstaw_komorke_do_listy(ppglowa, &x, &y);

							 } else {
								 usun_liste_komorek(ppglowa);
								 return false;

							 }

						 } else if (wartosc_zwrocona_fwscanf == 1 && ciaglosc_danych == false) {
							 usun_liste_komorek(ppglowa);
							 return false;

						 } else if (wartosc_zwrocona_fwscanf == 0) {
							 ciaglosc_danych = false;

						 }

						 linia++;
						 break;
			}
			
		}
		fclose(wsk_plik);

		if (linia < 7) return false;
		else return true;
	} else {
		return false;
	}
}

static void odswiez_plansze_dla_mrowki_langtona(const bool** plansza, const prostokat* kawalek_planszy, const mrowka* pozycja_mrowki, const HANDLE* uchwyt) {
	SetConsoleTextAttribute(*uchwyt, 0x30);
	system("cls");

	for (int y = kawalek_planszy->wspolrzedna_y_lewego_gornego_rogu; y <= kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu; y++) {
		for (int x = kawalek_planszy->wspolrzedna_x_lewego_gornego_rogu; x <= kawalek_planszy->wspolrzedna_x_prawego_dolnego_rogu; x++) {
			if (plansza[y][x] == false) {
				SetConsoleTextAttribute(*uchwyt, 0x20);
			} else {
				SetConsoleTextAttribute(*uchwyt, 0x02);
			}

			wprintf(L"%lc", 0x2588);

		}
		if (y != kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu) wprintf(L"\n");

	}

	if (pozycja_mrowki->wspolrzedna_x >= kawalek_planszy->wspolrzedna_x_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_x <= kawalek_planszy->wspolrzedna_x_prawego_dolnego_rogu && pozycja_mrowki->wspolrzedna_y >= kawalek_planszy->wspolrzedna_y_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_y <= kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu) {
		short x_kursora = pozycja_mrowki->wspolrzedna_x % SZEROKOSC_WIDOCZNEJ_PLANSZY, y_kursora = pozycja_mrowki->wspolrzedna_y % WYSOKOSC_WIDOCZNEJ_PLANSZY;

		ustaw_kursor(&x_kursora, &y_kursora, uchwyt);
		

		if (plansza[pozycja_mrowki->wspolrzedna_y][pozycja_mrowki->wspolrzedna_x] == false) {
			SetConsoleTextAttribute(*uchwyt, 0x02);
		} else {
			SetConsoleTextAttribute(*uchwyt, 0x20);
		}

		switch (pozycja_mrowki->kierunek) {
			case PRAWO: wprintf(L"%lc", 0x2192);
						break;

			case LEWO: wprintf(L"%lc", 0x2190);
					   break;

			case GORA: wprintf(L"%lc", 0x2191);
					   break;

			case DOL: wprintf(L"%lc", 0x2193);
					  break;

		}
	}
}

static void kolejny_krok_mrowki(bool** plansza, const int* szerokosc, const int* wysokosc, const prostokat* kawalek_planszy, mrowka* pozycja_mrowki, const HANDLE* uchwyt) {
	if (plansza[pozycja_mrowki->wspolrzedna_y][pozycja_mrowki->wspolrzedna_x] == false) {
		plansza[pozycja_mrowki->wspolrzedna_y][pozycja_mrowki->wspolrzedna_x] = true;
		
		if (pozycja_mrowki->wspolrzedna_x >= kawalek_planszy->wspolrzedna_x_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_x <= kawalek_planszy->wspolrzedna_x_prawego_dolnego_rogu && pozycja_mrowki->wspolrzedna_y >= kawalek_planszy->wspolrzedna_y_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_y <= kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu) {
			short x_kursora = pozycja_mrowki->wspolrzedna_x % SZEROKOSC_WIDOCZNEJ_PLANSZY, y_kursora = pozycja_mrowki->wspolrzedna_y % WYSOKOSC_WIDOCZNEJ_PLANSZY;

			ustaw_kursor(&x_kursora, &y_kursora, uchwyt);
			SetConsoleTextAttribute(*uchwyt, 0x02);
			wprintf(L"%lc", 0x2588);
		}

		switch (pozycja_mrowki->kierunek) {
			case PRAWO: pozycja_mrowki->kierunek = DOL;
						pozycja_mrowki->wspolrzedna_y += 1;
						if (pozycja_mrowki->wspolrzedna_y >= *wysokosc) pozycja_mrowki->wspolrzedna_y = 0;
						break;

			case LEWO: pozycja_mrowki->kierunek = GORA;
					   pozycja_mrowki->wspolrzedna_y -= 1;
					   if (pozycja_mrowki->wspolrzedna_y < 0) pozycja_mrowki->wspolrzedna_y = *wysokosc - 1;
					   break;

			case GORA: pozycja_mrowki->kierunek = PRAWO;
					   pozycja_mrowki->wspolrzedna_x += 1;
					   if (pozycja_mrowki->wspolrzedna_x >= *szerokosc) pozycja_mrowki->wspolrzedna_x = 0;
					   break;

			case DOL: pozycja_mrowki->kierunek = LEWO;
					  pozycja_mrowki->wspolrzedna_x -= 1;
					  if (pozycja_mrowki->wspolrzedna_x < 0) pozycja_mrowki->wspolrzedna_x = *szerokosc - 1;
					  break;
			
		}

	} else {
		plansza[pozycja_mrowki->wspolrzedna_y][pozycja_mrowki->wspolrzedna_x] = false;
		
		if (pozycja_mrowki->wspolrzedna_x >= kawalek_planszy->wspolrzedna_x_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_x <= kawalek_planszy->wspolrzedna_x_prawego_dolnego_rogu && pozycja_mrowki->wspolrzedna_y >= kawalek_planszy->wspolrzedna_y_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_y <= kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu) {
			short x_kursora = pozycja_mrowki->wspolrzedna_x % SZEROKOSC_WIDOCZNEJ_PLANSZY, y_kursora = pozycja_mrowki->wspolrzedna_y % WYSOKOSC_WIDOCZNEJ_PLANSZY;

			ustaw_kursor(&x_kursora, &y_kursora, uchwyt);
			SetConsoleTextAttribute(*uchwyt, 0x20);
			wprintf(L"%lc", 0x2588);
		}

		switch (pozycja_mrowki->kierunek) {
		case PRAWO: pozycja_mrowki->kierunek = GORA;
				    pozycja_mrowki->wspolrzedna_y -= 1;
				    if (pozycja_mrowki->wspolrzedna_y < 0) pozycja_mrowki->wspolrzedna_y = *wysokosc - 1;
				    break;

		case LEWO: pozycja_mrowki->kierunek = DOL;
				   pozycja_mrowki->wspolrzedna_y += 1;
				   if (pozycja_mrowki->wspolrzedna_y >= *wysokosc) pozycja_mrowki->wspolrzedna_y = 0;
				   break;

		case GORA: pozycja_mrowki->kierunek = LEWO;
				   pozycja_mrowki->wspolrzedna_x -= 1;
				   if (pozycja_mrowki->wspolrzedna_x < 0) pozycja_mrowki->wspolrzedna_x = *szerokosc - 1;
				   break;

		case DOL: pozycja_mrowki->kierunek = PRAWO;
				  pozycja_mrowki->wspolrzedna_x += 1;
				  if (pozycja_mrowki->wspolrzedna_x >= *szerokosc) pozycja_mrowki->wspolrzedna_x = 0;
				  break;

		}

	}


	if (pozycja_mrowki->wspolrzedna_x >= kawalek_planszy->wspolrzedna_x_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_x <= kawalek_planszy->wspolrzedna_x_prawego_dolnego_rogu && pozycja_mrowki->wspolrzedna_y >= kawalek_planszy->wspolrzedna_y_lewego_gornego_rogu && pozycja_mrowki->wspolrzedna_y <= kawalek_planszy->wspolrzedna_y_prawego_dolnego_rogu) {
		short x_kursora = pozycja_mrowki->wspolrzedna_x % SZEROKOSC_WIDOCZNEJ_PLANSZY, y_kursora = pozycja_mrowki->wspolrzedna_y % WYSOKOSC_WIDOCZNEJ_PLANSZY;

		ustaw_kursor(&x_kursora, &y_kursora, uchwyt);


		if (plansza[pozycja_mrowki->wspolrzedna_y][pozycja_mrowki->wspolrzedna_x] == false) {
			SetConsoleTextAttribute(*uchwyt, 0x02);
		}
		else {
			SetConsoleTextAttribute(*uchwyt, 0x20);
		}

		switch (pozycja_mrowki->kierunek) {
		case PRAWO: wprintf(L"%lc", 0x2192);
			break;

		case LEWO: wprintf(L"%lc", 0x2190);
			break;

		case GORA: wprintf(L"%lc", 0x2191);
			break;

		case DOL: wprintf(L"%lc", 0x2193);
			break;

		}
	}


}

void mrowka_langtona(bool** plansza, const int* szerokosc, const int* wysokosc, const int* sekundy, mrowka* informacja_o_mrowce, const HANDLE* uchwyt) {
	prostokat aktualny_zakres_planszy;
	
	aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu = 0;
	aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu = 0;

	aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu = (*szerokosc <= SZEROKOSC_WIDOCZNEJ_PLANSZY) ? *szerokosc - 1 : SZEROKOSC_WIDOCZNEJ_PLANSZY - 1;
	aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu = (*wysokosc <= WYSOKOSC_WIDOCZNEJ_PLANSZY) ? *wysokosc - 1 : WYSOKOSC_WIDOCZNEJ_PLANSZY - 1;


	char odczytany_znak;
	odswiez_plansze_dla_mrowki_langtona(plansza, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);
	ustaw_widocznosc_kursora(FALSE, uchwyt);

	clock_t czas_do_nastepnego_kroku = *sekundy * CLOCKS_PER_SEC, czas_rozpoczecia = clock();

	while (true) {

		if (czas_rozpoczecia + czas_do_nastepnego_kroku < clock()) {
			kolejny_krok_mrowki(plansza, szerokosc, wysokosc, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);

			czas_rozpoczecia = clock();
		}

		if (_kbhit() != 0) {
			odczytany_znak = _getch();

			switch (odczytany_znak) {
				case STRZALKA_W_GORE:	if (*wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu = aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu - 1;
											aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu -= WYSOKOSC_WIDOCZNEJ_PLANSZY;

											if (aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu < 0) {
												if (*wysokosc % WYSOKOSC_WIDOCZNEJ_PLANSZY != 0) {
													aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu = *wysokosc - *wysokosc % WYSOKOSC_WIDOCZNEJ_PLANSZY;

												} else {
													aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu = *wysokosc - WYSOKOSC_WIDOCZNEJ_PLANSZY;

												}

												aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu = *wysokosc - 1;
											}

											odswiez_plansze_dla_mrowki_langtona(plansza, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);

										}

										break;

				case STRZALKA_W_PRAWO:	if (*szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu += SZEROKOSC_WIDOCZNEJ_PLANSZY;
											aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu += SZEROKOSC_WIDOCZNEJ_PLANSZY;

											if (aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu >= *szerokosc) {
												aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu = 0;
												aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu = SZEROKOSC_WIDOCZNEJ_PLANSZY - 1;

											} else if (aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu >= *szerokosc) {
												aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu = *szerokosc - 1;

											}

											odswiez_plansze_dla_mrowki_langtona(plansza, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);

										}

										break;

				case STRZALKA_W_LEWO:	if (*szerokosc > SZEROKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu = aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu - 1;
											aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu -= SZEROKOSC_WIDOCZNEJ_PLANSZY;

											if (aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu < 0) {
												if (*szerokosc % SZEROKOSC_WIDOCZNEJ_PLANSZY != 0) {
													aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu = *szerokosc - *szerokosc % SZEROKOSC_WIDOCZNEJ_PLANSZY;

												} else {
													aktualny_zakres_planszy.wspolrzedna_x_lewego_gornego_rogu = *szerokosc - SZEROKOSC_WIDOCZNEJ_PLANSZY;

												}

												aktualny_zakres_planszy.wspolrzedna_x_prawego_dolnego_rogu = *szerokosc - 1;
											}

											odswiez_plansze_dla_mrowki_langtona(plansza, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);

										}

										break;

				case STRZALKA_W_DOL:	if (*wysokosc > WYSOKOSC_WIDOCZNEJ_PLANSZY) {
											aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu += WYSOKOSC_WIDOCZNEJ_PLANSZY;
											aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu += WYSOKOSC_WIDOCZNEJ_PLANSZY;

											if (aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu >= *wysokosc) {
												aktualny_zakres_planszy.wspolrzedna_y_lewego_gornego_rogu = 0;
												aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu = WYSOKOSC_WIDOCZNEJ_PLANSZY - 1;

											} else if (aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu >= *wysokosc) {
												aktualny_zakres_planszy.wspolrzedna_y_prawego_dolnego_rogu = *wysokosc - 1;

											}

											odswiez_plansze_dla_mrowki_langtona(plansza, &aktualny_zakres_planszy, informacja_o_mrowce, uchwyt);

										}

										break;

				case 'p':				{

										clock_t czas_do_odswiezenia = czas_rozpoczecia + czas_do_nastepnego_kroku - clock();
										while (_getch() != 'p') continue;
										czas_rozpoczecia = clock() + czas_do_odswiezenia - czas_do_nastepnego_kroku;

										break;

										}

				case ESC:				ustaw_widocznosc_kursora(TRUE, uchwyt);
										system("cls");
										return;

				default:				break;
				
			}

		}

	}

}

void wyczysc_wiersz(const short int *x, const short int* y, const HANDLE* uchwyt) {
	COORD koordynaty = {*x, *y};    
	DWORD ilosc_wpisanych_znakow;
	CONSOLE_SCREEN_BUFFER_INFO informacja;

	GetConsoleScreenBufferInfo(*uchwyt, &informacja);

	FillConsoleOutputCharacter(*uchwyt, (TCHAR)' ', (DWORD)informacja.dwSize.X, koordynaty, &ilosc_wpisanych_znakow);
	
	GetConsoleScreenBufferInfo(*uchwyt, &informacja);

	FillConsoleOutputAttribute(*uchwyt, informacja.wAttributes, (DWORD)informacja.dwSize.X, koordynaty, &ilosc_wpisanych_znakow);

	ustaw_kursor(x, y, uchwyt);
}

void wczytaj_int(int* zmienna, const wchar_t *komunikat, const short int x_komunikatu, const short int y_komunikatu, const HANDLE* uchwyt) {
	int wartosc_zwrocona;

	ustaw_kursor(&x_komunikatu, &y_komunikatu, uchwyt);
	wprintf(L"%ls ", komunikat);

	do {
		wartosc_zwrocona = wscanf(L"%d", zmienna);
		if (wartosc_zwrocona < 1) {
			wint_t znak_z_bufora;
			wscanf(L"%lc", &znak_z_bufora);
		}
	} while (wartosc_zwrocona != 1);

	wyczysc_wiersz(&x_komunikatu, &y_komunikatu, uchwyt);
	wprintf(L"%ls %d", komunikat, *zmienna);

	while (getwchar() != '\n');
}

int getwline(wchar_t* lancuch, const unsigned int ilosc_znakow_do_wczytania) {
	wint_t odczytany_znak;
	unsigned int licznik;
	for (licznik = 0; licznik < ilosc_znakow_do_wczytania - 1 && (odczytany_znak = getwchar()) != WEOF && odczytany_znak != '\n'; ++licznik) lancuch[licznik] = odczytany_znak;
	lancuch[licznik] = '\0';

	return licznik;
}

void wyswietl_menu(const wchar_t tablica_lancuchow[][MAX_ILOSC_ZNAKOW_OPCJI_MENU], const unsigned short int *ilosc_wierszy, const unsigned short int* wiersz_z_znacznikiem) {
	for (int licznik = 0; licznik < *ilosc_wierszy; licznik++) {
		wprintf(L"%ls", tablica_lancuchow[licznik]);
		if(licznik == *wiersz_z_znacznikiem) wprintf(L" %lc", 0x2190);
		wprintf(L"\n");
	}

	wprintf(L"\n\n\nStrzałka w górę %lc - przejdź do poprzedniej opcji z menu", 0x2191);
	wprintf(L"\nStrzałka w dół %lc - przejdź do następnej opcji z menu", 0x2193);
	wprintf(L"\nENTER - zatwierdź wybraną opcję");
}

void ustaw_widocznosc_kursora(const bool czy_widoczny, const HANDLE *uchwyt) {
	CONSOLE_CURSOR_INFO informacja = {1, czy_widoczny};
	SetConsoleCursorInfo(*uchwyt, &informacja);
}

void ustaw_kursor(const short int *x, const short int *y, const HANDLE *uchwyt) {
	COORD pozycja = { *x, *y };
	SetConsoleCursorPosition(*uchwyt, pozycja);
}

int policz_cyfry_uint(unsigned int liczba) {
	int licznik = 0;
	do
	{
		licznik++;
		liczba /= 10;
	} while (liczba != 0);
	return licznik;
}

wchar_t* uint_na_wchar_t(unsigned int liczba) {
	unsigned int liczba_znakow = (liczba == 0) ? 1 : (unsigned int)log10(liczba) + 1, licznik = 0;
	wchar_t* tablica_znakow = NULL;
	if (tablica_znakow = (wchar_t*)malloc((liczba_znakow + 1) * sizeof(wchar_t))) {
		tablica_znakow[liczba_znakow] = '\0';
		do {
			tablica_znakow[liczba_znakow - licznik - 1] = liczba % 10 + '0';
			licznik++;
			liczba /= 10;
		} while (liczba != 0);
	}
	return tablica_znakow;
}

wchar_t* scal_dwa_lancuchy_wchar_t(const wchar_t* str_1, unsigned int lz_1, const wchar_t* str_2, unsigned int lz_2) {
	if (str_1 != NULL && lz_1 != 0 && str_2 != NULL && lz_2 != 0) {
		wchar_t* scalony = NULL;
		if (scalony = (wchar_t*)malloc((lz_1 + lz_2 + 1) * sizeof(wchar_t))) {
			scalony[lz_1 + lz_2] = '\0';
			unsigned int indeks_scalonego = 0, indeks_str_2 = 0;

			for (indeks_scalonego; indeks_scalonego < lz_1; indeks_scalonego++) {
				scalony[indeks_scalonego] = str_1[indeks_scalonego];
			}

			for (indeks_scalonego, indeks_str_2; indeks_scalonego < lz_1 + lz_2; indeks_scalonego++, indeks_str_2++) {
				scalony[indeks_scalonego] = str_2[indeks_str_2];
			}

		}
		return scalony;
	}
	else {
		return NULL;
	}
}
