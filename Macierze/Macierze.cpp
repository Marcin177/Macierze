#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <time.h>
#include "Macierze.h"
using namespace std;

void slowo_macierze();
void pierwsze_menu(int* a, int* b, int* c);
void Wybor(int a, int b, int c);
int main();

template <class T>
class Macierz
{
private:
	int n;
	vector<vector<T>> tab;
	vector<vector<T>> tab_transp;
	vector<vector<T>> tab_odwr;
	vector<vector<T>> tab_dopeln;
	T wyznacz;
	int stop;

public:
	Macierz(int a) : n(a) {
		tab.resize(n, vector<T>(n));
		tab_transp.resize(n, vector<T>(n));
		tab_odwr.resize(n, vector<T>(n));
		//tab_dopeln.resize(n, vector<T>(n));
		klawiatura();
	}
	Macierz(int a, int b) : n(a) {
		tab.resize(n, vector<T>(n));
		tab_transp.resize(n, vector<T>(n));
		tab_odwr.resize(n, vector<T>(n));
		//tab_dopeln.resize(n, vector<T>(n));
		losowe();
	}
	Macierz(int a, T b, T c) : n(a) {
		tab.resize(n, vector<T>(n));
		tab_transp.resize(n, vector<T>(n));
		tab_odwr.resize(n, vector<T>(n));
		//tab_dopeln.resize(n, vector<T>(n));
		losowazakres(b, c);
	}
	~Macierz() {};
	Macierz& operator+(Macierz& a);
	Macierz& operator-(Macierz& a);
	void klawiatura();
	void losowe();
	void losowazakres(int p, int q);
	void wypisz();
	void transpozycja();
	void odwracanie();
	void licz_wyznacznik();
	void wyznacznik();
	void stopien();
	void dopelnienie() {}
	void menu();
};

template <class T>
void Macierz<T>::klawiatura() {
	system("cls");
	slowo_macierze();
	cout << "Przypisywanie wartości z klawiatury\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Element [" << i << "][" << j << "]: ";
			cin >> tab[i][j];
		}
	}
	wypisz();
}

template <class T>
void Macierz<T>::losowe() {
	unsigned int seed = time(NULL);
	srand(seed);
	if constexpr (is_same<T, int>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = rand() % 100;
			}
		}
	}
	else if constexpr (is_same<T, double>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = (double)rand() / (double)RAND_MAX * (double)rand();
			}
		}
	}
	else if constexpr (is_same<T, float>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = (float)rand() / (float)RAND_MAX * (float)rand();
			}
		}
	}
	wypisz();
}

template <class T>
void Macierz<T>::losowazakres(int p, int q) {
	unsigned int seed = time(NULL);
	srand(seed);
	if constexpr (is_same<T, int>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = p + (q - p) * rand() % 100;
			}
		}
	}
	else if constexpr (is_same<T, double>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = p + (q - p) * (double)rand() / (double)RAND_MAX * (double)rand();
			}
		}
	}
	else if constexpr (is_same<T, float>::value) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tab[i][j] = p + (q - p) * (float)rand() / (float)RAND_MAX * (float)rand();
			}
		}
	}
	wypisz();
}

template <class T>
void Macierz<T>::wypisz() {
	system("cls");
	cout << "Macierz pierwotna\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	Sleep(4000);
	system("cls");
	menu();
}

template <class T>
void Macierz<T>::menu() {
	slowo_macierze();
	cout << "Wybierz dzailanie\n1 - wypisz macierz\n2 - transpozycja\n3 - odwracanie\n4 - wyznacznik(max 5x5)\n5 - stopien\n6 - dopelnienie\n7 - dodanie macierzy\n8 - odjecie macierzy\n\n";
	int* a = new int;
	cin >> *a;
	switch (*a) {
	case 1:
		wypisz();
		break;
	case 2:
		transpozycja();
		break;
	case 3:
		odwracanie();
		break;
	case 4:
		wyznacznik();
		break;
	case 5:
		stopien();
		break;
	case 6:
		dopelnienie();
		break;
	case 7:
		break;
	case 8:
		break;
	default:
		menu();
	}
	delete a;
}

template <class T>
void Macierz<T>::stopien() {
	stop = n;
	system("cls");
	cout << "Stopień macierzy wynosi: " << stop;
	Sleep(4000);
	menu();
}

template <class T>
void Macierz<T>::transpozycja() {
	system("cls");
	cout << "Macierz pierwotna:\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Macierz transponowana:\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tab_transp[i][j] = tab[j][i];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tab_transp[i][j] << " ";
		}
		cout << endl;
	}
	Sleep(4000);
	menu();
}

template <class T>
void Macierz<T>::odwracanie() {
	system("cls");
	cout << "Macierz pierwotna:\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Macierz odwrocona:\n\n";
}

template <class T>
void Macierz<T>::wyznacznik() {
	system("cls");
	licz_wyznacznik();
	cout << "Wyznacznik macierzy wynosi:\n" << wyznacz;
	Sleep(4000);
	system("cls");
	menu();
}

template <class T>
void Macierz<T>::licz_wyznacznik() {
	switch (n) {
	case 1:
		wyznacz = tab[0][0];
		break;
	case 2:
		wyznacz = tab[0][0] * tab[1][1] - tab[0][1] * tab[1][0];
		break;
	case 3:
		wyznacz = tab[0][0] * tab[1][1] * tab[2][2] + tab[1][0] * tab[2][1] * tab[0][2] + tab[2][0] * tab[0][1] * tab[1][2] - tab[0][1] * tab[1][0] * tab[2][2] - tab[2][0] * tab[1][1] * tab[0][2] - tab[0][0] * tab[2][1] * tab[1][2];
		break;
	case 4:
		wyznacz = tab[0][0] * tab[1][1] * tab[2][2] * tab[3][3] + tab[1][0] * tab[2][1] * tab[0][3] * tab[3][2] + tab[2][0] * tab[0][2] * tab[1][3] * tab[3][1] + tab[3][0] * tab[0][1] * tab[1][2] * tab[2][3] - tab[3][0] * tab[2][1] * tab[1][2] * tab[0][3] - tab[2][0] * tab[1][1] * tab[0][2] * tab[3][3] - tab[1][0] * tab[0][1] * tab[3][2] * tab[2][3] - tab[3][1] * tab[0][0] * tab[2][2] * tab[1][3];
		break;
	case 5:
		wyznacz = tab[0][0] * tab[1][1] * tab[2][2] * tab[3][3] * tab[4][4] + tab[1][0] * tab[2][1] * tab[3][2] * tab[4][3] * tab[0][4] + tab[2][0] * tab[3][1] * tab[4][2] * tab[0][3] * tab[1][4] + tab[3][0] * tab[4][1] * tab[0][2] * tab[1][3] * tab[2][4] + tab[4][0] * tab[0][1] * tab[1][2] * tab[2][3] * tab[3][4] - tab[0][4] * tab[1][3] * tab[2][2] * tab[3][1] * tab[4][0] - tab[0][3] * tab[1][2] * tab[2][1] * tab[3][0] * tab[4][4] - tab[0][2] * tab[1][1] * tab[2][0] * tab[3][4] * tab[4][3] - tab[0][1] * tab[1][0] * tab[2][4] * tab[3][3] * tab[4][2] - tab[0][0] * tab[1][4] * tab[2][3] * tab[3][2] * tab[4][1];
		break;
	}
}

class Fasada {

};

class Adapter {

};




void error() {
	system("cls");
	cout << "\n\tEEEEE   RRRRRR   RRRRRR     OOO    RRRRRR\n\tE       R     R  R     R   O   O   R     R\n\tEEEEE   RRRRRR   RRRRRR    O   O   RRRRRR\n\tE       R   R    R   R     O   O   R   R\n\tEEEEE   R    R   R    R     OOO    R    R";
	Sleep(4000);
	system("cls");
	main();
}

template <class T>
void zakres(int a) {
	T d = 0, e = 0;
	slowo_macierze();
	cout << "Wprowadz zakres:\n";
	cin >> d >> e;
	Macierz<T> m(a, d, e);
}

void Wybor(int a, int b, int c) {
	if (b == 1) {
		if (c == 1) Macierz<int> m(a);
		else if (c == 2) Macierz<int> m(a, 0);
		else if (c == 3) zakres<int>(a);
		else error();
	}
	else if (b == 2) {
		if (c == 1) Macierz<double> m(a);
		else if (c == 2) Macierz<double> m(a, 0);
		else if (c == 3) zakres<double>(a);
		else error();
	}
	else if (b == 3) {
		if (c == 1)	Macierz<float> m(a);
		else if (c == 2) Macierz<float> m(a, 0);
		else if (c == 3) zakres<float>(a);
		else error();
	}
	else error();
}

void slowo_macierze() {
	cout << "-----> MACIERZE <-----\n\n";
}

void pierwsze_menu(int* a, int* b, int* c) {
	slowo_macierze();
	cout << "PODAJ WIELKOSC MAIERZY: ";
	cin >> *a;
	cout << "\nJaki rodzaj liczb bedzie uzywany w macierzy ? \n1 - Calkowite\n2 - Rzeczywiste <double>\n3 - Rzeczywiste <float>\n";
	cin >> *b;
	system("cls");
	slowo_macierze();
	cout << "Wprowadzenie macierzy\n1 - Wpisywanie z klawiatury\n2 - Losowe uzupelnienie macierzy\n3 - Losowe uzupelnienie macierzy z zakresem\n";
	cin >> *c;
}

int main()
{
	int a = 0, b = 0, c = 0;
	pierwsze_menu(&a, &b, &c);
	Wybor(a, b, c);
	return 0;
}
