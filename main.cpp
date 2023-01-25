// Programowanie zaawansowane - Projekt
// Macierze
// Grupa P1
// Marcin Gonciarz
// Antoni Garczyñski
#include <iostream>
#include <time.h>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const double eps = 1e-12;

class Macierz
{
private:
    int n;
    long long int wyznacz;
    int stop;
    int** tab = new int* [n];
public:
    Macierz(int a) : n(a), wyznacz(0), stop(a) {
        losowe();
    }
    ~Macierz() {
        for (int i = 0; i < n; i++) {
            delete[] tab[i];
        }
        delete[] tab;
    };
    Macierz& operator+=(Macierz& a);
    Macierz& operator-=(Macierz& a);
    void losowe();
    void wypisz();
    void transpozycja();
    void odwracanie();
    void wyznacznik();
    void stopien();
    void dopelnienie();
    void wypiszdod();
    void wypiszodej();
    void zamien(int a, int b);
    void adapter();
    void import_file();
    void export_file();
    void wypisz_z_pliku(int **tab_z_pliku);

};

Macierz& Macierz::operator+=(Macierz& a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            this->tab[i][j] += a.tab[i][j];
        }
    }
    return *this;
}

Macierz& Macierz::operator-=(Macierz& a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            this->tab[i][j] -= a.tab[i][j];
        }
    }
    return *this;
}

void Macierz::losowe() {
    unsigned int seed = time(NULL);
    srand(seed);
    for (int i = 0; i < n; i++) {
        tab[i] = new int[n];
        for (int j = 0; j < n; j++) {
            tab[i][j] = rand();
        }
    }
    wypisz();
}

void Macierz::transpozycja() {
    wypisz();
    int** tab_transp = new int* [n];
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

int licz_wyznacznik(int** tab, int n) {
    long long int det = 1;
    long long int temp;
    int** tempTab = new int* [n];
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
    cout << "Stopien macierzy wynosi: " << stop;
    cin.get();
}

void Macierz::dopelnienie() {
    system("cls");
    long long int** tablica_dopelnien = new long long int* [n];
    for (int i = 0; i < n; i++) {
        tablica_dopelnien[i] = new long long int[n];
    }
    int znak = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int** temp = new int* [n - 1];
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

bool ludist(int n, int** A)
{
    int i, j, k;

    for (k = 0; k < n - 1; k++)
    {
        if (fabs(A[k][k]) < eps) return false;

        for (i = k + 1; i < n; i++)
            A[i][k] /= A[k][k];

        for (i = k + 1; i < n; i++)
            for (j = k + 1; j < n; j++)
                A[i][j] -= A[i][k] * A[k][j];
    }

    return true;
}

bool lusolve(int k, int n, int** A, double** X)
{
    int    i, j;
    double s;

    for (i = 1; i < n; i++)
    {
        s = 0;

        for (j = 0; j < i; j++) s += A[i][j] * X[j][k];

        X[i][k] -= s;
    }

    if (fabs(A[n - 1][n - 1]) < eps) return false;

    X[n - 1][k] /= A[n - 1][n - 1];

    for (i = n - 2; i >= 0; i--)
    {
        s = 0;

        for (j = i + 1; j < n; j++) s += A[i][j] * X[j][k];

        if (fabs(A[i][i]) < eps) return false;

        X[i][k] = (X[i][k] - s) / A[i][i];
    }

    return true;
}

void Macierz::odwracanie() {
    system("cls");
    wypisz();
    double** tablica_odwrotna = new double* [n];
    int** tab_temp = new int* [n];
    cout << "Macierz odwrotna: \n\n";
    bool ok;
    for (int i = 0; i < n; i++) {
        tablica_odwrotna[i] = new double[n];
        tab_temp[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) tab_temp[i][j] = tab[i][j];
    }
    if (ludist(n, tab_temp))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) tablica_odwrotna[i][j] = 0;
            tablica_odwrotna[i][i] = 1;
        }
        ok = true;
        for (int i = 0; i < n; i++)
            if (!lusolve(i, n, tab_temp, tablica_odwrotna))
            {
                ok = false;
                break;
            }
    }
    else ok = false;
    if (ok)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << setw(10) << tablica_odwrotna[i][j] << " ";
            cout << endl;
        }
    }
    else cout << "DZIELNIK ZERO\n";
    for (int i = 0; i < n; i++) {
        delete[] tab_temp[i];
        delete[] tablica_odwrotna[i];
    }
    delete[] tab_temp;
    delete[] tablica_odwrotna;
    cin.get();
}

void Macierz::zamien(int a, int b) {
    system("cls");
    wypisz();
    int i = 0;
    cout << "Podaj liczbe aby zmienic warosc tab[" << a << "][" << b << "] = ";
    cin >> i;
    tab[a][b] = i;
    wypisz();
    cin.get();
}

void Macierz::adapter() {
    system("cls");
    int a;
    do {
        cout << "Podaj numer liczby od 1 - " << n * n << " : ";
        cin >> a;
    } while (a < 1 || a > n * n);
    int b = (a - 1) / n;
    int c = (a - 1) % n;
    cout << "W podanym numerze zapisana jest wartosc: " << tab[b][c];
    cin.get();
    cin.get();
}

void Macierz::export_file() {
    system("cls");
    cout << "Eksportowanie macierzy\n\n";
    ofstream file;
    file.open("macierz.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << tab[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
    cout << "Macierz zaeksportowana\n\n";
    cout << "Zawartosc pliku macierz.txt\n";
    system("type macierz.txt");
    system("macierz.txt");
    cin.get();
}

void Macierz::import_file() {
    system("cls");
    int** tab_z_pliku = new int* [n];
    cout << "Importowanie macierzy\n\n";
    for (int i = 0; i < n; i++) {
        tab_z_pliku[i] = new int[n];
    }
    ifstream file;
    file.open("macierz.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> tab_z_pliku[i][j];
        }
    }
    file.close();
    cout << "Macierz zaimportowana\n\n";
    wypisz_z_pliku(tab_z_pliku);
    for (int i = 0; i < n; i++) {
        delete[] tab_z_pliku[i];
    }
    delete[] tab_z_pliku;
    cin.get();
}

void Macierz::wypisz_z_pliku(int **tab_z_pliku) {

    cout << "Macierz importowanana\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tab_z_pliku[i][j] << " ";
        }
        cout << endl << endl;
    }
    cin.get();
    return;
}

void Macierz::wypiszdod() {
    system("cls");
    cout << "Macierz dodana\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl << endl;
    }
    cin.get();
}

void Macierz::wypiszodej() {
    system("cls");
    cout << "Macierz odjeta\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl << endl;
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

void podaj_wielkosc(int* n) {
    cout << "Podaj rozmiar macierzy NxN\n";
    cin >> *n;
}

int main()
{
    unsigned int seed = time(NULL);
    srand(seed);
    int n = 0;
    podaj_wielkosc(&n);
    Macierz M(n);
    M.transpozycja();
    M.wyznacznik();
    M.stopien();
    M.dopelnienie();
    M.odwracanie();
    M.zamien(rand() % n, rand() % n);
    M.adapter();
    system("cls");
    cout << "Tworzenie drugiego obiektu";
    cin.get();
    Macierz K(n);
    K += M;
    K.wypiszdod();
    K -= M;
    K.wypiszodej();
    M.export_file();
    K.import_file();
    system("cls");
    cout << "\t\t------------------------------\n\t\t| Programowanie zaawansowane |\n\t\t------------------------------\n\t\t|    Projekt   |   Grupa P1  |\n\t\t------------------------------\n\t\t|           Macierze         |\n\t\t------------------------------\n\t\t|    Antoni    |    Marcin   |\n\t\t|  Garczyñski  |   Gonciarz  |\n\t\t------------------------------\n";
    return 0;
}
