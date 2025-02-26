#include <stdbool.h>
#include "lib.h"

int wypiszTekst(FILE* const plik, const char* tekst) {
    int count = 0;
    // Wypisz tekst do pliku dopóki nie dotrzemy do znaku końca tekstu
    while (*tekst != '\0') {
        if (fputc(*tekst, plik) == EOF) {
            return -1;
        }
        count++;
        tekst++;
    }
    return count;
}

int czytajTekst(FILE* const plik, char* tekst, int max) {
    int count = 0;
    // Wczytaj tekst z pliku
    int i = 0;
    while (i < max - 1) {
        int c = fgetc(plik); 
        if (c == EOF) {
            return -1;
        }
        *tekst++ = c;
        i++;
    }

    // Zakończ tekst
    *tekst = '\0';

    return count;
}

int kopiujTekst(const char* restrict skad, char* restrict dokad, int max) {
    int count = 0;
    // Kopiuj znak po znaku do tablicy docelowej
    // Ogranicz maksymalną liczbę skopiowanych znaków
    while ((*dokad++ = *skad++) != '\0') { }

    // Zakończ tekst
    *dokad = '\0';

    return count;
}

int wszystkieZnaki(const char* tekst) {
    int count = 0;
    while (*tekst++ != '\0') {
        count++;
    }
    return count;
}

int czarneZnaki(const char* tekst) {
    int count = 0;
    // Zlicz wszystkie znaki, które nie są białymi znakami
    while (*tekst++ != '\0') {
        if (*tekst != ' ' && *tekst != '\t' && *tekst != '\n') {
            count++;
        }
    }
    return count;
}


int linie(const char* tekst) {
    unsigned i = 0;
    int count = 0;
    while (*tekst++ != '\0') {
        if (*tekst == '\n') {
            count++;
        } 
    }

    // Dodatkowo zlicz ostatnią linię, jeśli się nie kończy znakiem nowej linii
    // (normalnie tekst-1, ale w pętli while po ostatniej iteracji jeszcze jeden raz pointer zostaje zwiększony)
    if (*(tekst-2) != '\n') {
        count++;
    }

    return count;
}

int slowa(const char* tekst) {
    int count = 0;
    bool isWord = false;
    while (*tekst != '\0') {
        if (!isWord && *tekst != ' ' && *tekst != '\t' && *tekst != '\n') {
            isWord = true;
        } else if (isWord && (*tekst == ' ' || *tekst == '\t' || *tekst == '\n')) {
            isWord = false;
            count++;
        }
        tekst++;
    }

    // Dodatkowo zlicz ostatnie słowo, po którym nie występuje biały znak
    if (isWord) {
        count++;
    }

    return count;
}
