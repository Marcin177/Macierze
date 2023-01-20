#include <iostream>
#include <time.h>
#include <cstring>

using namespace std;

class Macierz
{
private:
	int n;
	int **tab = new int*[n];
	long long int **tablica_dopelnien = new long long int*[n];
	long double **tablica_odwrotna = new long double*[n];
	long long int wyznacz;
	int stop;

public:
	Macierz(int a) : n(a), wyznacz(0), stop(a) {
		losowe();
	}
	~Macierz() {};
	Macierz& operator+(Macierz& a);
	Macierz& operator-(Macierz& a);
	void losowe();
	void wypisz();
	void transpozycja();
	void odwracanie();
	void wyznacznik();
	void stopien();
	void dopelnienie();
	void menu();
};

void Macierz::losowe(){
	unsigned int seed = time(NULL);
	srand(seed);
    for (int i = 0; i < n; i++) {
        tab[i] = new int[n];
        for (int j = 0; j < n; j++) {
            tab[i][j] = rand() % 100;
        }
    }
    wypisz();
}

void Macierz::transpozycja(){
    wypisz();
    int **tab_transp = new int*[n];
    cout << "Macierz transponowana:\n\n";
	for (int i = 0; i < n; i++) {
        tab_transp[i] = new int[n];
		for (int j = 0; j < n; j++) {
			tab_transp[i][j] = tab[j][i];
			cout << tab_transp[i][j] << " ";
		}
        cout << endl << endl;
	}
	for (int i = 0; i < n; i++) {
        delete[] tab_transp[i];
    }
    delete[] tab_transp;
    cin.get();
}

int licz_wyznacznik(int **tab, int n) {
	long long int det = 1;
    long long int temp;
    int **tempTab = new int*[n];
    for (int i = 0; i < n; i++) {
        tempTab[i] = new int[n];
        memcpy(tempTab[i], tab[i], sizeof(int) * n);
    }
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(tempTab[j][i]) > abs(tempTab[k][i])) {
                k = j;
            }
        }
        if (k != i) {
            for (int j = 0; j < n; j++) {
                swap(tempTab[i][j], tempTab[k][j]);
            }
            det = -det;
        }
        if (abs(tempTab[i][i]) < 1e-9) {
            return 0;
        }
        det *= tempTab[i][i];
        temp = 1 / tempTab[i][i];
        for (int j = 0; j < n; j++) {
            tempTab[i][j] *= temp;
        }
        for (int j = i + 1; j < n; j++) {
            temp = tempTab[j][i];
            for (int k = 0; k < n; k++) {
                tempTab[j][k] -= tempTab[i][k] * temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        delete[] tempTab[i];
    }
    delete[] tempTab;
    return det;
}

void Macierz::wyznacznik() {
	system("cls");
	wyznacz = licz_wyznacznik(tab, n);
	cout << "Wyznacznik macierzy wynosi:\n" << wyznacz;
	cin.get();
}

void Macierz::stopien() {
	system("cls");
	cout << "Stopieñ macierzy wynosi: " << stop;
	cin.get();
}

void Macierz::dopelnienie() {
    system("cls");
    int **tablica_dop = new int*[n];
    for (int i = 0; i < n; i++) {
        tablica_dopelnien[i] = new long long int[n];
        tablica_dop[i] = new int[n];
    }
    int znak = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int **temp = new int*[n - 1];
            for (int k = 0; k < n - 1; k++) {
                temp[k] = new int[n - 1];
            }
            int l = 0, m = 0;
            for (int l = 0; l < n; l++) {
                for (int m = 0; m < n; m++) {
                    if (l != i && m != j) {
                        temp[l < i ? l : l - 1][m < j ? m : m - 1] = tab[l][m];
                    }
                }
            }
            tablica_dopelnien[i][j] = znak * licz_wyznacznik(temp, n - 1);
            znak = -znak;
            for (int k = 0; k < n - 1; k++) {
                delete[] temp[k];
            }
            delete[] temp;
        }
    }
    cout << "Macierz dopelnien:\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tablica_dopelnien[i][j] << " ";
		}
        cout << endl << endl;
	}
	for (int i = 0; i < n; i++) {
        delete[] tablica_dopelnien[i];
    }
    delete[] tablica_dopelnien;
    cin.get();
}

void Macierz::odwracanie(){
    if (wyznacz == 0){
        return;
    }
    system("cls");
    wypisz();
    for (int i = 0; i < n; i++) {
        tablica_odwrotna[i] = new long double[n];
    }
    cout << "Macierz odwrotna:\n\n";
    long double det = 1;
    for (int i = 0; i < n; i++) {
        det *= tab[i][i];
    }
    det = 1 / det;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tablica_odwrotna[i][j] = tablica_dopelnien[i][j] * det;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tablica_odwrotna[j][i] << " ";
        }
        cout << endl;
    }
    cin.get();
}

void Macierz::wypisz() {
	system("cls");
	cout << "Macierz pierwotna\n\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl << endl;
	}
	cin.get();
	return;
}

void podaj_wielkosc(int *n){
cout << "Podaj rozmiar macierzy NxN\n";
cin >> *n;
}

int main()
{
	int n = 0;
	podaj_wielkosc(&n);
	Macierz M(n);
	M.transpozycja();
	M.wyznacznik();
	M.stopien();
	M.dopelnienie();
	M.odwracanie(); // Czasem dzia³a, a czasem nie. Problem z iloœci¹ bajtów liczby :(
    Macierz K(n);
    K.wypisz();
    return 0;
}
