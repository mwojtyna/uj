#include <stdio.h>
#include <assert.h>
#include <complex.h>
#include "lib.h"

int piszNazwaZ(FILE* file, char* nazwa, zesp z) {
	if (fprintf(file, "%s:\n", nazwa) < 0) return 0;
	if (piszZ(file, z) == 0) return 0;

	if (fprintf(stdout, "%s:\n", nazwa) < 0) return 0;
	if (piszZ(stdout, z) == 0) return 0;

	return 1;
}

int piszC(FILE* file, double complex z) {
	if (fprintf(file, "(%lg,%lg)\n", creal(z), cimag(z)) < 0) {
		return 0;
	}
	return 1;
}
int piszNazwaC(FILE* file, char* nazwa, double complex z) {
	if (fprintf(file, "%s:\n", nazwa) < 0) return 0;
	if (!piszC(file, z)) return 0;

	if (fprintf(stdout, "%s:\n", nazwa) < 0) return 0;
	if (!piszC(stdout, z)) return 0;

	return 1;
}

int main() {
	FILE* in = fopen("dane.txt", "r");
	FILE* out = fopen("wyniki.txt", "w");
	assert(in != NULL);
	assert(out != NULL);

	// wypisanie używając typu 'zesp'
	zesp z1 = czytajZ(in);
	zesp z2 = czytajZ(in);

	assert(fprintf(out, "---------- TYP ZESP ----------\n") >= 0);
	assert(fprintf(stdout, "---------- TYP ZESP ----------\n") >= 0);
	assert(piszNazwaZ(out, "z1", z1) == 1);
	assert(piszNazwaZ(out, "z2", z2) == 1);

	assert(piszNazwaZ(out, "z1 - sprzężenie", sprzezenieZ(z1)) == 1);
	assert(piszNazwaZ(out, "z2 - sprzężenie", sprzezenieZ(z2)) == 1);

	assert(fprintf(out, "z1 - moduł:\n%lg\n", modulZ(z1)) >= 0);
	assert(fprintf(stdout, "z1 - moduł:\n%lg\n", modulZ(z1)) >= 0);
	assert(fprintf(out, "z2 - moduł:\n%lg\n", modulZ(z2)) >= 0);
	assert(fprintf(stdout, "z2 - moduł:\n%lg\n", modulZ(z2)) >= 0);

	assert(fprintf(out, "z1 - faza:\n%lg\n", fazaZ(z1)) >= 0);
	assert(fprintf(stdout, "z1 - faza:\n%lg\n", fazaZ(z1)) >= 0);
	assert(fprintf(out, "z2 - faza:\n%lg\n", fazaZ(z2)) >= 0);
	assert(fprintf(stdout, "z2 - faza:\n%lg\n", fazaZ(z2)) >= 0);

	assert(piszNazwaZ(out, "suma", sumaZ(z1, z2)) == 1);
	assert(piszNazwaZ(out, "różnica", roznicaZ(z1, z2)) == 1);
	assert(piszNazwaZ(out, "iloczyn", iloczynZ(z1, z2)) == 1);
	assert(piszNazwaZ(out, "iloraz", ilorazZ(z1, z2)) == 1);

	// wypisanie używając typu 'double complex'
	double complex c1 = z1.re + z1.im*I;
	double complex c2 = z2.re + z2.im*I;

	assert(fprintf(out, "\n---------- TYP COMPLEX ----------\n") >= 0);
	assert(fprintf(stdout, "\n---------- TYP COMPLEX ----------\n") >=0);
	assert(piszNazwaC(out, "z1", c1) == 1);
	assert(piszNazwaC(out, "z2", c2) == 1);

	assert(piszNazwaC(out, "z1 - sprzężenie", conj(c1)) == 1);
	assert(piszNazwaC(out, "z2 - sprzężenie", conj(c2)) == 1);

	assert(fprintf(out, "z1 - moduł:\n%lg\n", cabs(c1)) >= 0);
	assert(fprintf(stdout, "z1 - moduł:\n%lg\n", cabs(c1)) >= 0);
	assert(fprintf(out, "z2 - moduł:\n%lg\n", cabs(c2)) >= 0);
	assert(fprintf(stdout, "z2 - moduł:\n%lg\n", cabs(c2)) >= 0);

	assert(fprintf(out, "z1 - faza:\n%lg\n", carg(c1)) >= 0);
	assert(fprintf(stdout, "z1 - faza:\n%lg\n", carg(c1)) >= 0);
	assert(fprintf(out, "z2 - faza:\n%lg\n", carg(c2)) >= 0);
	assert(fprintf(stdout, "z2 - faza:\n%lg\n", carg(c2)) >= 0);

	assert(piszNazwaC(out, "suma", c1 + c2) == 1);
	assert(piszNazwaC(out, "różnica", c1 - c2) == 1);
	assert(piszNazwaC(out, "iloczyn", c1 * c2) == 1);
	assert(piszNazwaC(out, "iloraz", c1 / c2) == 1);

	return 0;
}
