#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int czytajMacierz(FILE* wp, char* nazwa, int n, double M[n][n]) {
    char row[256];
    bool foundName = false;
    int rowNum = 0;
	char* token;

    while (fgets(row, sizeof(row), wp)) {
        // Czy wiersz zawiera nazwę macierzy?
        if (!foundName && strstr(row, nazwa)) {
            foundName = true;
            continue;
        }

        // Jeśli nazwa macierzy została znaleziona, wczytujemy wartości
        if (foundName) {
            if (rowNum < n) {
				// Używamy strtok do podziału wiersza na stringi pomiędzy spacjami
				token = strtok(row, " ");
				int colNum = 0;

				// Wczytujemy wartości kolumna po kolumnie
				while (token != NULL && colNum < n) {
					if (sscanf(token, "%lf", &M[rowNum][colNum]) != 1) {
						rewind(wp);
						return 0;
					}
					colNum++;
					token = strtok(NULL, " \t\n");
				}

				// Sprawdzamy czy wczytano odpowiednią liczbę kolumn
				if (colNum != n) {
					rewind(wp);
					return 0;
				}
				rowNum++;
            } else break;
        }
    }

	rewind(wp);
    // Jeśli wczytano wszystkie wiersze to zwracamy suckes
    return (rowNum == n) ? 1 : 0;
}

int wypiszMacierz(FILE* wp, char* nazwa, int n, double M[n][n]) {
	if (fprintf(wp, "%s:\n", nazwa) < 0) return 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (fprintf(wp, "%lf ", M[y][x]) < 0) return 0;
		}
		if(fprintf(wp, "\n") < 0) return 0;
	}
	
	return 1;
}

int czytajWektor(FILE* wp, char* nazwa, int n, double V[n]) {
    char row[256];
    bool foundName = false;
    int rowNum = 0;

    while (fgets(row, sizeof(row), wp)) {
        // Czy wiersz zawiera nazwę wektora?
        if (!foundName && strstr(row, nazwa)) {
            foundName = true;
            continue;
        }

        // Jeśli nazwa wektora została znaleziona, wczytujemy wartości
        if (foundName) {
			if (rowNum < n) {
				if(sscanf(row, "%lf", &V[rowNum]) != 1) { 
					rewind(wp);
					return 0;
				}
				rowNum++;
			} else break;
        }
    }

	rewind(wp);
    // Jeśli wczytano wszystkie wiersze to zwracamy suckes
    return (rowNum == n) ? 1 : 0;
}


int wypiszWektor(FILE* wp, char* nazwa, int n, double V[n]) {
	if (fprintf(wp, "%s:\n", nazwa) < 0) return 0;
	for (int i = 0; i < n; i++) {
		if (fprintf(wp, "%lf\n", V[i]) < 0) return 0;
	}

	return 1;
}

int czytajLiczbe(FILE* wp, char* nazwa, double* c) {
    char row[256];
    bool foundName = false;

    while (fgets(row, sizeof(row), wp)) {
        // Czy wiersz zawiera nazwę liczby?
        if (!foundName && strstr(row, nazwa)) {
            foundName = true;
            continue;
        }

        // Jeśli nazwa liczby została znaleziona, wczytujemy wartość
        if (foundName) {
			if (sscanf(row, "%lf", c) != 1) {
				rewind(wp);
				return 0;
			} else break;
        }
    }

	rewind(wp);
	return 1;
}

int wypiszLiczbe(FILE* wp, char* nazwa, double c) {
	if (fprintf(wp, "%s:\n", nazwa) < 0) return 0;
	if (fprintf(wp, "%lf\n", c) < 0) return 0;

	return 1;
}

void transponujMacierz(int n, double M[n][n], double MT[n][n]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			MT[x][y] = M[y][x];
		}
	}
}

void dodajMacierze(int n, double A[n][n], double B[n][n], double C[n][n]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			C[y][x] = A[y][x] + B[y][x];
		}
	}
}

void odejmijMacierze(int n, double A[n][n], double B[n][n], double C[n][n]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			C[y][x] = A[y][x] - B[y][x];
		}
	}
}

void mnozLiczbaMacierz(int n, double c, double A[n][n], double B[n][n]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			B[y][x] = c * A[y][x];
		}
	}
}

void mnozMacierzWektor(int n, double A[n][n], double V[n], double W[n]) {
	// Zerujemy wektor W na wszelki wypadek
	for (int y = 0; y < n; y++) {
		W[y] = 0;
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			W[y] += A[y][x] * V[x];
		}
	}
}

void mnozMacierze(int n, double A[n][n], double B[n][n], double C[n][n]) {
	double sum;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j){
			sum = 0;
			for (int k = 0; k < n; ++k) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}
}
