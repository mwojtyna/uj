#include <stdio.h>
#include "lib.h"

void analizujTekst(char tekst[], FILE* plik) {
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

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // Analizuj predefiniowany tekst
        char tekst[] = "linia pierwsza\nlinia druga\n";
        analizujTekst(tekst, stdout);
    } else if (argc == 2) {
        // Analizuj tekst wprowadzony z klawiatury
        char* tekst = argv[1];
        analizujTekst(tekst, stdout);
    } else {
        printf("Niepoprawna ilość argumentów!\n");
        return 1;
    }

    return 0;
}
