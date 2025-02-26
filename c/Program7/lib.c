#include "lib.h"
#include <stdbool.h>

int wypiszTekst(FILE *plik, char tekst[]) {
  int count = 0;
  // Wypisz tekst do pliku dopóki nie dotrzemy do znaku końca tekstu
  for (unsigned i = 0; tekst[i] != '\0'; i++, count++) {
    if (fputc(tekst[i], plik) == EOF) {
      return -1;
    }
    count++;
  }
  return count;
}

int czytajTekst(FILE *plik, char tekst[], int max) {
  int count = 0;
  // Wczytaj tekst z pliku
  for (unsigned i = 0; i < max - 1; i++, count++) {
    int c = fgetc(plik);
    if (c == EOF) {
      return -1;
    }
    tekst[i] = c;
  }

  // Zakończ tekst
  tekst[count] = '\0';

  return count;
}

int kopiujTekst(char skad[], char dokad[], int max) {
  int count = 0;
  // Kopiuj znak po znaku do tablicy docelowej
  // Ogranicz maksymalną liczbę skopiowanych znaków
  for (unsigned i = 0; skad[i] != '\0' && i < max; i++, count++) {
    dokad[i] = skad[i];
  }

  // Zakończ tekst
  dokad[count] = '\0';

  return count;
}

int wszystkieZnaki(char tekst[]) {
  int count = 0;
  while (tekst[count] != '\0') {
    count++;
  }
  return count;
}

int czarneZnaki(char tekst[]) {
  int count = 0;
  // Zlicz wszystkie znaki, które nie są białymi znakami
  for (unsigned i = 0; tekst[i] != '\0'; i++) {
    if (tekst[i] != ' ' && tekst[i] != '\t' && tekst[i] != '\n') {
      count++;
    }
  }
  return count;
}

int linie(char tekst[]) {
  unsigned i = 0;
  int count = 0;
  for (; tekst[i] != '\0'; i++) {
    if (tekst[i] == '\n') {
      count++;
    }
  }

  // Dodatkowo zlicz ostatnią linię, jeśli się nie kończy znakiem nowej linii
  if (tekst[i - 1] != '\n') {
    count++;
  }

  return count;
}

int slowa(char tekst[]) {
  int count = 0;
  bool isWord = false;
  for (unsigned i = 0; tekst[i] != '\0'; i++) {
    bool isWhite = tekst[i] == ' ' || tekst[i] == '\t' || tekst[i] == '\n';
    if (!isWord && !isWhite) {
      isWord = true;
    } else if (isWord && isWhite) {
      isWord = false;
      count++;
    }
  }

  // Dodatkowo zlicz ostatnie słowo, po którym nie występuje biały znak
  if (isWord) {
    count++;
  }

  return count;
}
