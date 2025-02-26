#include <stdio.h>
#include "lib.h"

void analizujTekst(const char* const tekst, FILE* const plik) {
    int len = wszystkieZnaki(tekst);
    fprintf(plik, "TEKST: '");
    wypiszTekst(plik, tekst);
    fprintf(plik, "'\n");
    fprintf(plik, "Ilość wszystkich znaków: %d\n", len);
    fprintf(plik, "Ilość czarnych znaków: %d\n", czarneZnaki(tekst));
    fprintf(plik, "Ilość słów: %d\n", slowa(tekst));
    fprintf(plik, "Ilość linii: %d\n", linie(tekst));
    
    // Skopiuj tekst i zrób to samo
    char tekst2[len];
    kopiujTekst(tekst, tekst2, len);
    fprintf(plik, "\nKOPIA: '");
    wypiszTekst(plik, tekst);
    fprintf(plik, "'\n");
    fprintf(plik, "Ilość wszystkich znaków: %d\n", len);
    fprintf(plik, "Ilość czarnych znaków: %d\n", czarneZnaki(tekst2));
    fprintf(plik, "Ilość słów: %d\n", slowa(tekst2));
    fprintf(plik, "Ilość linii: %d\n", linie(tekst2));
}

int main(int argc, char** argv) {
    if (argc == 3) {
        // Analizuj tekst z pliku
        const char* const wejscieNazwa = *(argv + 1);
        const char* const wyjscieNazwa = *(argv + 2);
        FILE* const wejscie = fopen(wejscieNazwa, "r");
        FILE* const wyjscie = fopen(wyjscieNazwa, "w");

        if (wejscie == NULL) {
            printf("Błąd przy otwieraniu pliku wejściowego '%s'\n", wejscieNazwa);
            return 1;
        }
        if (wyjscie == NULL) {
            printf("Błąd przy otwieraniu pliku wyjściowego '%s'\n", wyjscieNazwa);
            return 1;
        }

        const unsigned size = 1024 * 1024; // 1MB
        char tekst[size];
        czytajTekst(wejscie, tekst, size);
        analizujTekst(tekst, wyjscie);

        printf("Wykonano analizę tekstu z pliku %s, wyniki zapisano w pliku %s\n", wejscieNazwa, wyjscieNazwa);
    } else {
        printf("Niepoprawna ilość argumentów!\n");
        return 1;
    }

    return 0;
}
