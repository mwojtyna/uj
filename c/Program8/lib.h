#pragma once

#include <stdio.h>

// Zwraca ilość znaków wpisanych do pliku, -1 gdy błąd
int wypiszTekst(FILE* const plik, const char* tekst); 

// Zwraca ilość znaków wczytanych z pliku, -1 gdy błąd
int czytajTekst(FILE* const plik, char* tekst, int max); 

// Zwraca liczbę skopiowanych znaków
int kopiujTekst(const char* restrict skad, char* restrict dokad, int max); 

// Liczy wszystkie znaki
int wszystkieZnaki(const char* tekst); 

// Liczy czarne znaki
int czarneZnaki(const char* tekst); 

// Liczy linie
int linie(const char* tekst); 

// Liczy słowa
int slowa(const char* tekst); 
