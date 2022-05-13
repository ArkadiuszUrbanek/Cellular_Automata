#include <math.h>
#include <stdio.h>
#include <wchar.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <crtdbg.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

#include "funkcje.h"
#include "struktury.h"
#include "stale.h"

int main(void) {

#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	
	SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");

	HANDLE uchwyt_konsoli = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFOEX informacja_nowego_bufora = {.cbSize = sizeof(informacja_nowego_bufora)};

	informacja_nowego_bufora.dwMaximumWindowSize.X = SZEROKOSC_WIDOCZNEJ_PLANSZY;
	informacja_nowego_bufora.dwMaximumWindowSize.Y = WYSOKOSC_WIDOCZNEJ_PLANSZY;

	informacja_nowego_bufora.dwSize.X = SZEROKOSC_WIDOCZNEJ_PLANSZY;
	informacja_nowego_bufora.dwSize.Y = WYSOKOSC_WIDOCZNEJ_PLANSZY;

	informacja_nowego_bufora.srWindow.Left = 0;
	informacja_nowego_bufora.srWindow.Top = 0;
	informacja_nowego_bufora.srWindow.Right = SZEROKOSC_WIDOCZNEJ_PLANSZY;
	informacja_nowego_bufora.srWindow.Bottom = WYSOKOSC_WIDOCZNEJ_PLANSZY;

	informacja_nowego_bufora.wAttributes = 1;
	informacja_nowego_bufora.wPopupAttributes = 1;
	informacja_nowego_bufora.ColorTable[0] = RGB(0, 0, 0);
	informacja_nowego_bufora.ColorTable[1] = RGB(255, 200, 0);
	informacja_nowego_bufora.ColorTable[2] = RGB(231, 230, 221);
	informacja_nowego_bufora.ColorTable[3] = RGB(127, 127, 127);

	CONSOLE_FONT_INFOEX informacja_rastrowej_czcionki = {.cbSize = sizeof(informacja_rastrowej_czcionki)};

	informacja_rastrowej_czcionki.dwFontSize.X = 18;
	informacja_rastrowej_czcionki.dwFontSize.Y = 18;
	informacja_rastrowej_czcionki.FontFamily = FF_DONTCARE;
	informacja_rastrowej_czcionki.FontWeight = FW_NORMAL;
	wcscpy(informacja_rastrowej_czcionki.FaceName, L"Terminal");
	
	wchar_t	menu[][MAX_ILOSC_ZNAKOW_OPCJI_MENU] = {L"Menu główne:", L"Zasady gry w życie", L"Wczytaj grę w życie", L"Zagraj w grę w życie", L"Zasady mrówki Langtona", L"Zagraj w mrówkę Langtona", L"Wyjdź"};
	unsigned short int wiersz_konsoli = 1, ilosc_wierszy_menu = (unsigned short int)sizeof(menu)/sizeof(menu[0]), ilosc_opcji_menu = ilosc_wierszy_menu - 1, kolumna = (unsigned short int)wcslen(menu[wiersz_konsoli]) + 1;
	char wybor;

	wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
	ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);

	while(!(wiersz_konsoli == ilosc_opcji_menu && wybor == ENTER)){
		wybor = _getch();
	
		switch (wybor) {
	
			case STRZALKA_W_GORE:	ustaw_kursor(&kolumna, &wiersz_konsoli, &uchwyt_konsoli);
									wprintf(L" ");
									
									wiersz_konsoli--;
									if (wiersz_konsoli == 0) {
										wiersz_konsoli = ilosc_opcji_menu;
									} 
									
									kolumna = (unsigned short int)wcslen(menu[wiersz_konsoli]) + 1;
									ustaw_kursor(&kolumna, &wiersz_konsoli, &uchwyt_konsoli);
									wprintf(L"%lc", 0x2190);
	
									break;
	
			case STRZALKA_W_DOL:	ustaw_kursor(&kolumna, &wiersz_konsoli, &uchwyt_konsoli);
									wprintf(L" ");
									
									wiersz_konsoli++;
									if (wiersz_konsoli == ilosc_opcji_menu + 1) {
										wiersz_konsoli = 1;
									}
									
									kolumna = (unsigned short int)wcslen(menu[wiersz_konsoli]) + 1;
									ustaw_kursor(&kolumna, &wiersz_konsoli, &uchwyt_konsoli);
									wprintf(L"%lc", 0x2190);
	
									break;
	
			case ENTER:				system("cls");
									switch (wiersz_konsoli) {
	
										case 1:	SetConsoleTitle(L"Gra w życie Conwaya");
												wprintf(L"Reguły gry według Conwaya:\n");
												wprintf(L"%lc martwa komórka, która ma dokładnie 3 żywych sąsiadów, staje się żywa w następnej jednostce czasu\n", 0x25CF);
												wprintf(L"%lc żywa komórka z 2 albo 3 żywymi sąsiadami pozostaje nadal żywa, natomiast przy innej liczbie sąsiadów umiera", 0x25CF);
												wprintf(L"\n\nNaciśnij dowolny klawisz, aby wrócić do menu. . . ");
												ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);
												system("pause>nul");
												system("cls");

												SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");
												wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
												ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);
												break;
	
										case 2: {	
													SetConsoleTitle(L"Gra w życie Conwaya");
													ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);

													int szerokosc, wysokosc, sekundy;
													komorka* pglowa_listy = NULL;
													wchar_t** plansza, nazwa_pliku[_MAX_FNAME + _MAX_EXT + 1] = L"";

													do {
														wprintf(L"Podaj nazwę pliku do odczytu gry (wraz z rozszerzeniem .txt): ");
														getwline(nazwa_pliku, _MAX_FNAME + _MAX_EXT);
														if (_waccess(nazwa_pliku, 0) == -1) {
															wprintf(L"Plik o takiej nazwie nie istnieje. Naciśnij dowolny klawisz, aby wprowadzić nazwę ponownie.");
															system("pause>nul");
															system("cls");
														} else {
															break;
														}
													} while (true);


													if (odczytaj_gre_w_zycie(nazwa_pliku, &pglowa_listy, &szerokosc, &wysokosc) == true) {
														wprintf(L"Pomyślnie odczytano plik. Naciśnij dowolny klawisz, aby kontynuować. . . ");
														system("pause>nul");
														system("cls");

														wczytaj_int(&sekundy, L"Czas życia pokolenia w [s]:", 0, 0, &uchwyt_konsoli);

														if (sekundy > -1) {
															CONSOLE_SCREEN_BUFFER_INFOEX informacja_pierwotnego_bufora = { .cbSize = sizeof(informacja_pierwotnego_bufora) };
															CONSOLE_FONT_INFOEX informacja_pierwotnej_czcionki = { .cbSize = sizeof(informacja_pierwotnej_czcionki) };


															wprintf(L"\n\nSterowanie w trakcie gry:");
															wprintf(L"\n\nStrzałka w lewo %lc - przesuń widok w lewo o szerokość okna", 0x2190);
															wprintf(L"\nStrzałka w prawo %lc - przesuń widok w prawo o szerokość okna", 0x2192);
															wprintf(L"\nStrzałka w górę %lc - przesuń widok w górę o wysokość okna", 0x2191);
															wprintf(L"\nStrzałka w dół %lc - przesuń widok w dół o wysokość okna", 0x2193);
															wprintf(L"\nP - pauza / koniec pauzy");
															wprintf(L"\nESC - wyjście z gry");


															wprintf(L"\n\nNaciśnij dowolny klawisz, aby rozpocząć grę w życie. . . ");
															system("pause>nul");
															system("cls");



															GetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);
															GetCurrentConsoleFontEx(uchwyt_konsoli, FALSE, &informacja_pierwotnej_czcionki);

															SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_rastrowej_czcionki);
															SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_nowego_bufora);


															plansza = (wchar_t**)malloc(wysokosc * sizeof(wchar_t*));
															for (int x = 0; x < wysokosc; x++) {
																plansza[x] = (wchar_t*)malloc((szerokosc + 1) * sizeof(wchar_t));
																plansza[x][szerokosc] = '\0';
																for (int y = 0; y < szerokosc; y++) {
																	plansza[x][y] = L'.';
																}
															}

															komorka* pom = pglowa_listy;
															while (pom != NULL) {
																plansza[pom->wspolrzedna_y][pom->wspolrzedna_x] = 0x2588;
																pom = pom->nastepna;
															}

															usun_liste_komorek(&pglowa_listy);


															pglowa_listy = gra_w_zycie(plansza, &szerokosc, &wysokosc, &sekundy, &uchwyt_konsoli);
															SetConsoleTitle(L"Gra w życie Conwaya");

															SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_pierwotnej_czcionki);
															SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);

															for (int x = 0; x < wysokosc; x++) {
																free(plansza[x]);
															}
															free(plansza);


															if (pglowa_listy != NULL) {
																if (zapisz_gre_w_zycie(nazwa_pliku, pglowa_listy, &szerokosc, &wysokosc) == true) {
																	wprintf(L"Pomyślnie nadpisano grę. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																} else {
																	wprintf(L"Wystapił błąd przy otwieraniu pliku. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																}

																usun_liste_komorek(&pglowa_listy);
															} else {
																wprintf(L"Wszystkie komórki umarły. Nie nadpisano gry. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");

															}
															
														} else {
															usun_liste_komorek(&pglowa_listy);
															wprintf(L"\nSekundy nie mogą przyjąć wartości mniejszej od 0. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
															
														}

													} else {
														wprintf(L"Wystąpił błąd przy odczytywaniu pliku. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
														
													}

													system("pause>nul");
													system("cls");

													SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");
													wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
													ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);
													break;
												}

										case 3: {	
													SetConsoleTitle(L"Gra w życie Conwaya");

													CONSOLE_SCREEN_BUFFER_INFOEX informacja_pierwotnego_bufora = { .cbSize = sizeof(informacja_pierwotnego_bufora) };
													CONSOLE_FONT_INFOEX informacja_pierwotnej_czcionki = { .cbSize = sizeof(informacja_pierwotnej_czcionki) };

													int szerokosc, wysokosc, sekundy;
													komorka* pglowa_listy = NULL;
													wchar_t** plansza;

													ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);

													wczytaj_int(&szerokosc, L"Szerokość planszy:", 0, 0, &uchwyt_konsoli);

													if (szerokosc > 0) {
														wczytaj_int(&wysokosc, L"Wysokość planszy:", 0, 1, &uchwyt_konsoli);

														if (wysokosc > 0) {
															wczytaj_int(&sekundy, L"Czas życia pokolenia w [s]:", 0, 2, &uchwyt_konsoli);

															if (sekundy > -1) {
																wprintf(L"\n\nSterowanie w trakcie ustawiania komórek:");
																wprintf(L"\n\nStrzałka w lewo %lc - przejdź do następnej lewej komórki", 0x2190);
																wprintf(L"\nStrzałka w prawo %lc - przejdź do następnej prawej komórki", 0x2192);
																wprintf(L"\nStrzałka w górę %lc - przejdź do następnej górnej komórki", 0x2191);
																wprintf(L"\nStrzałka w dół %lc - przejdź do następnej dolnej komórki", 0x2193);
																wprintf(L"\nSPACJA - ustaw komórkę jako żywą '%lc' lub martwą '.'", 0x2588);
																wprintf(L"\nENTER - rozpocznij grę w życie");

																wprintf(L"\n\nSterowanie w trakcie gry:");
																wprintf(L"\n\nStrzałka w lewo %lc - przesuń widok w lewo o szerokość okna", 0x2190);
																wprintf(L"\nStrzałka w prawo %lc - przesuń widok w prawo o szerokość okna", 0x2192);
																wprintf(L"\nStrzałka w górę %lc - przesuń widok w górę o wysokość okna", 0x2191);
																wprintf(L"\nStrzałka w dół %lc - przesuń widok w dół o wysokość okna", 0x2193);
																wprintf(L"\nP - pauza / koniec pauzy");
																wprintf(L"\nESC - wyjście z gry");

																wprintf(L"\n\nNaciśnij dowolny klawisz, aby kontynuować. . . ");
																system("pause>nul");
																system("cls");


																GetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);
																GetCurrentConsoleFontEx(uchwyt_konsoli, FALSE, &informacja_pierwotnej_czcionki);

																SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_rastrowej_czcionki);
																SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_nowego_bufora);


																plansza = (wchar_t**)malloc(wysokosc * sizeof(wchar_t*));
																for (int x = 0; x < wysokosc; x++) {
																	plansza[x] = (wchar_t*)malloc((szerokosc + 1) * sizeof(wchar_t));
																	plansza[x][szerokosc] = '\0';
																	for (int y = 0; y < szerokosc; y++) {
																		plansza[x][y] = L'.';
																	}
																}

																zaznacz_komorki_na_planszy(plansza, &szerokosc, &wysokosc, &uchwyt_konsoli);
																pglowa_listy = gra_w_zycie(plansza, &szerokosc, &wysokosc, &sekundy, &uchwyt_konsoli);

																SetConsoleTitle(L"Gra w życie Conwaya");

																SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_pierwotnej_czcionki);
																SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);

																for (int x = 0; x < wysokosc; x++) {
																	free(plansza[x]);
																}
																free(plansza);

																if (pglowa_listy != NULL) {
																	wchar_t nazwa_pliku[_MAX_FNAME + _MAX_EXT + 1] = L"";

																	do {
																		wprintf(L"Podaj nazwę pliku do zapisu gry (wraz z rozszerzeniem .txt): ");
																		getwline(nazwa_pliku, _MAX_FNAME + _MAX_EXT);
																		if (_waccess(nazwa_pliku, 0) != -1) {
																			wprintf(L"Plik o takiej nazwie już istnieje. Naciśnij dowolny klawisz, aby wprowadzić nazwę ponownie.");
																			system("pause>nul");
																			system("cls");
																		}
																		else {
																			break;
																		}
																	} while (true);


																	if (zapisz_gre_w_zycie(nazwa_pliku, pglowa_listy, &szerokosc, &wysokosc) == true) {
																		wprintf(L"Zapisano pomyślnie grę. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																	}
																	else {
																		wprintf(L"Wystapił błąd przy otwieraniu pliku. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																	}

																	usun_liste_komorek(&pglowa_listy);

																}
																else {
																	wprintf(L"Wszystkie komórki umarły :(");
																	wprintf(L"\nNaciśnij dowolny klawisz, aby wrócić do menu. . . ");
																}
															}
															else {
																system("cls");
																wprintf(L"Sekundy nie mogą przyjąć wartości mniejszej od 0. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
															}
														}
														else {
															system("cls");
															wprintf(L"Wysokość nie może być mniejsza od 1. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
														}
													}
													else {
														system("cls");
														wprintf(L"Szerokość nie może być mniejsza od 1. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
													}

													ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);
													system("pause>nul");
													system("cls");

													SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");
													wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
													ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);
													break;
												}
										
										case 4: SetConsoleTitle(L"Mrówka Langtona");
												wprintf(L"Reguły gry:\n");
												wprintf(L"%lc jeśli mrówka znajduje się na polu białym to obraca się w lewo (o kąt prosty), zmienia kolor pola na czarny i przechodzi na następną komórkę\n", 0x25CF);
												wprintf(L"%lc jeśli mrówka znajduje się na polu czarnym to obraca się w prawo (o kąt prosty), zmienia kolor pola na biały i przechodzi na następną komórkę", 0x25CF);
												wprintf(L"\n\nNaciśnij dowolny klawisz, aby wrócić do menu. . . ");
												ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);
												system("pause>nul");
												system("cls");

												SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");
												wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
												ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);
												break;

										case 5: { 
													SetConsoleTitle(L"Mrówka Langtona");

													CONSOLE_SCREEN_BUFFER_INFOEX informacja_pierwotnego_bufora = { .cbSize = sizeof(informacja_pierwotnego_bufora) };
													CONSOLE_FONT_INFOEX informacja_pierwotnej_czcionki = { .cbSize = sizeof(informacja_pierwotnej_czcionki) };

													mrowka informacja_o_mrowce = { .kierunek = GORA };
													int szerokosc, wysokosc, sekundy;
													bool** plansza;

													ustaw_widocznosc_kursora(TRUE, &uchwyt_konsoli);

													wczytaj_int(&szerokosc, L"Szerokość planszy:", 0, 0, &uchwyt_konsoli);

													if (szerokosc > 0) {
														wczytaj_int(&wysokosc, L"Wysokość planszy:", 0, 1, &uchwyt_konsoli);

														if (wysokosc > 0) {
															wczytaj_int(&informacja_o_mrowce.wspolrzedna_x, L"Położenie mrówki w osi X:", 0, 2, &uchwyt_konsoli);

															if (informacja_o_mrowce.wspolrzedna_x > -1 && informacja_o_mrowce.wspolrzedna_x < szerokosc) {
																wczytaj_int(&informacja_o_mrowce.wspolrzedna_y, L"Położenie mrówki w osi Y:", 0, 3, &uchwyt_konsoli);
																
																if (informacja_o_mrowce.wspolrzedna_y > -1 && informacja_o_mrowce.wspolrzedna_y < wysokosc) {
																	wczytaj_int(&sekundy, L"Czas po jakim mrówka wykona kolejny krok w [s]:", 0, 4, &uchwyt_konsoli);
																
																	if (sekundy > -1) {
																		wprintf(L"\n\nSterowanie w trakcie gry:");
																		wprintf(L"\n\nStrzałka w lewo %lc - przesuń widok w lewo o szerokość okna", 0x2190);
																		wprintf(L"\nStrzałka w prawo %lc - przesuń widok w prawo o szerokość okna", 0x2192);
																		wprintf(L"\nStrzałka w górę %lc - przesuń widok w górę o wysokość okna", 0x2191);
																		wprintf(L"\nStrzałka w dół %lc - przesuń widok w dół o wysokość okna", 0x2193);
																		wprintf(L"\nP - pauza / koniec pauzy");
																		wprintf(L"\nESC - wyjście z gry");

																		wprintf(L"\n\nNaciśnij dowolny klawisz, aby kontynuować. . . ");
																		system("pause>nul");
																		system("cls");


																		GetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);
																		GetCurrentConsoleFontEx(uchwyt_konsoli, FALSE, &informacja_pierwotnej_czcionki);

																		informacja_nowego_bufora.wAttributes = 0x30;

																		SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_rastrowej_czcionki);
																		SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_nowego_bufora);


																		plansza = (bool**)malloc(wysokosc * sizeof(bool*));
																		for (int x = 0; x < wysokosc; x++) {
																			plansza[x] = (bool*)malloc(szerokosc * sizeof(bool));
																			for (int y = 0; y < szerokosc; y++) {
																				plansza[x][y] = true;
																			}
																		}

																		mrowka_langtona(plansza, &szerokosc, &wysokosc, &sekundy, &informacja_o_mrowce, &uchwyt_konsoli);


																		for (int x = 0; x < wysokosc; x++) {
																			free(plansza[x]);
																		}
																		free(plansza);

																	

																		informacja_nowego_bufora.wAttributes = 1;

																		SetCurrentConsoleFontEx(uchwyt_konsoli, TRUE, &informacja_pierwotnej_czcionki);
																		SetConsoleScreenBufferInfoEx(uchwyt_konsoli, &informacja_pierwotnego_bufora);

																		system("cls");
																	
																	}
																	else {
																		system("cls");
																		wprintf(L"Sekundy nie mogą przyjąć wartości mniejszej od 0. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																		system("pause>nul");
																		system("cls");
																	}
																}
																else {
																	system("cls");
																	if(wysokosc != 1) wprintf(L"Wartość położenia mrówki w osi Y musi się mieścić w przedziale od 0 do %d. Naciśnij dowolny klawisz, aby wrócić do menu. . . ", wysokosc - 1);
																	else  wprintf(L"Wartość położenia mrówki w osi Y może być tylko 0. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																	system("pause>nul");
																	system("cls");
																}

															}
															else {
																system("cls");
																if(szerokosc != 1) wprintf(L"Wartość położenia mrówki w osi X musi się mieścić w przedziale od 0 do %d. Naciśnij dowolny klawisz, aby wrócić do menu. . . ", szerokosc - 1);
																else wprintf(L"Wartość położenia mrówki w osi X może być tylko 0. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
																system("pause>nul");
																system("cls");
															}

														}
														else {
															system("cls");
															wprintf(L"Wysokość nie może być mniejsza od 1. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
															system("pause>nul");
															system("cls");
														}
													
													}
													else {
														system("cls");
														wprintf(L"Szerokość nie może być mniejsza od 1. Naciśnij dowolny klawisz, aby wrócić do menu. . . ");
														system("pause>nul");
														system("cls");
													}


													
													SetConsoleTitle(L"Gra w życie Conwaya i Mrówka Langtona");
													wyswietl_menu(menu, &ilosc_wierszy_menu, &wiersz_konsoli);
													ustaw_widocznosc_kursora(FALSE, &uchwyt_konsoli);
													break;
												}

										default: break;
									}
			default:				break;
		}
	}

	CloseHandle(uchwyt_konsoli);
	return EXIT_SUCCESS;
}
