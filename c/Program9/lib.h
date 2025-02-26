#ifndef LIB_H
#define LIB_H

#include <stdio.h>

int czytajMacierz(FILE *wp, char *nazwa, int n, double M[n][n]);

int wypiszMacierz(FILE *wp, char *nazwa, int n, double M[n][n]);

int czytajWektor(FILE *wp, char *nazwa, int n, double V[n]);

int wypiszWektor(FILE *wp, char *nazwa, int n, double V[n]);

int czytajLiczbe(FILE *wp, char *nazwa, double *c);

int wypiszLiczbe(FILE *wp, char *nazwa, double c);

void transponujMacierz(int n, double M[n][n], double MT[n][n]);

void dodajMacierze(int n, double A[n][n], double B[n][n], double C[n][n]);

void odejmijMacierze(int n, double A[n][n], double B[n][n], double C[n][n]);

void mnozLiczbaMacierz(int n, double c, double A[n][n], double B[n][n]);

void mnozMacierzWektor(int n, double A[n][n], double V[n], double W[n]);

void mnozMacierze(int n, double A[n][n], double B[n][n], double C[n][n]);

#endif
