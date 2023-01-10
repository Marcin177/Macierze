#include <iostream>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include "Macierze.h"
using namespace std;

void slowo_macierze();
void pierwsze_menu(int* a, int* b, int* c);
void Wybor(int a, int b, int c);

template <class T>
class Macierz
{
private:
	int n;
	vector<std::vector<T>> tab;
public:
	Macierz(int a) : n(a) { 
		tab.resize(n, std::vector<T>(n));
		klawiatura(); 
	}
	Macierz(int a, int b) : n(a) { 
		tab.resize(n, std::vector<T>(n)); 
		losowe();
	}
	Macierz(int a, T b, T c) : n(a) { 
		tab.resize(n, std::vector<T>(n));
		losowazakres(b, c); 
	}
	~Macierz() {};
	Macierz& operator+(Macierz& a);				
	Macierz operator++();						
	Macierz operator++(int);					
	Macierz operator+(double a);				
	Macierz& operator-(Macierz& a);				
	Macierz operator--();						
	Macierz operator--(int);					
	Macierz operator-(double a);	
	void klawiatura();
	void losowe();
	void losowazakres(int p, int q);
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
}

template <class T>
void Macierz<T>::losowe() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tab[i][j] = rand() % 10;
		}
	}
}

template <class T>
void Macierz<T>::losowazakres(int p, int q) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tab[i][j] = p + rand() % (q - p + 1);
		}
	}
}

int main()
{
	int a = 0, b = 0, c = 0;
	pierwsze_menu(&a, &b, &c);
	Wybor(a, b, c);
	system("cls");
	return 0;
}

void error() {
	system("cls");
	cout << "\n\tEEEEE   RRRRRR   RRRRRR     OOO     OOO   RRRRRR\n\tE       R     R  R     R   O   O   O   O  R     R\n\tEEEEE   RRRRRR   RRRRRR    O   O   O   O  RRRRRR\n\tE       R   R    R   R     O   O   O   O  R   R\n\tEEEEE   R    R   R    R     OOO     OOO   R    R";
	Sleep(4000);
	system("cls");
	main();
}

template <class T>
void zakres(int a) {
	int d = 0, e = 0;
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
	}else if (b == 2) {
		if (c == 1) Macierz<double> m(a);
		else if (c == 2) Macierz<double> m(a, 0);
		else if (c == 3) zakres<double>(a);
		else error();
	}else if (b == 3) {
		if (c == 1)	Macierz<float> m(a);
		else if (c == 2) Macierz<float> m(a, 0);
		else if (c == 3) zakres<float>(a);
		else error();
	}else error();
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