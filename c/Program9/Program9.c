#include "lib.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
	if (argc > 3 || argc == 1) {
		printf("Nieoprawna ilość argumentów!\n");
		return 1;
	}

	char* inName = argv[1];
	char* outName = argv[2];
	FILE* in = fopen(inName, "r");
	FILE* out = fopen(outName, "w");
	assert(in != NULL);
	assert(out != NULL);

	const int n = 4;
	double A[n][n];
	double B[n][n];
	double V[n];
	double c;

	double AT[n][n];
	double C[n][n];
	double W[n];

	assert(czytajMacierz(in, "A", n, A) == 1);
	assert(wypiszMacierz(stdout, "A", n, A) == 1);
	assert(wypiszMacierz(out, "A", n, A) == 1);

	assert(czytajMacierz(in, "B", n, B) == 1);
	assert(wypiszMacierz(stdout, "B", n, B) == 1);
	assert(wypiszMacierz(out, "B", n, B) == 1);

	assert(czytajWektor(in, "V", n, V) == 1);
	assert(wypiszWektor(stdout, "V", n, V) == 1);
	assert(wypiszWektor(out, "V", n, V) == 1);

	assert(czytajLiczbe(in, "c", &c) == 1);
	assert(wypiszLiczbe(stdout, "c", c) == 1);
	assert(wypiszLiczbe(out, "c", c) == 1);

	transponujMacierz(n, A, AT);
	assert(wypiszMacierz(stdout, "AT", n, AT) == 1);
	assert(wypiszMacierz(out, "AT", n, AT) == 1);

	dodajMacierze(n, A, B, C);
	assert(wypiszMacierz(stdout, "A+B", n, C) == 1);
	assert(wypiszMacierz(out, "A+B", n, C) == 1);

	odejmijMacierze(n, A, B, C);
	assert(wypiszMacierz(stdout, "A-B", n, C) == 1);
	assert(wypiszMacierz(out, "A-B", n, C) == 1);

	mnozLiczbaMacierz(n, c, A, C);
	assert(wypiszMacierz(stdout, "c*A", n, C) == 1);
	assert(wypiszMacierz(out, "c*A", n, C) == 1);

	mnozMacierzWektor(n, A, V, W);
	assert(wypiszWektor(stdout, "A*V", n, W) == 1);
	assert(wypiszWektor(out, "A*V", n, W) == 1);

	mnozMacierze(n, A, B, C);
	assert(wypiszMacierz(stdout, "A*B", n, C) == 1);
	assert(wypiszMacierz(out, "A*B", n, C) == 1);

	fclose(in);
	fclose(out);
    return 0;
}
