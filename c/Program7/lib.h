#pragma once

#include <stdio.h>

// Zwraca ilość znaków wpisanych do pliku, -1 gdy błąd
int wypiszTekst(FILE* plik, char tekst[]); 

// Zwraca ilość znaków wczytanych z pliku, -1 gdy błąd
int czytajTekst(FILE* plik, char tekst[], int max); 

// Zwraca liczbę skopiowanych znaków
int kopiujTekst(char skad[], char dokad[], int max); 

// Liczy wszystkie znaki
int wszystkieZnaki(char tekst[]); 

// Liczy czarne znaki
int czarneZnaki(char tekst[]); 

// Liczy linie
int linie(char tekst[]); 

// Liczy słowa
int slowa(char tekst[]); 
