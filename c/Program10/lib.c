#include "lib.h"
#include <math.h>
#include <assert.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

zesp czytajZ(FILE *wp) {
	zesp z;
	assert(fscanf(wp, "(%lg,%lg) ", &z.re, &z.im) != EOF);
	return z;
}

int piszZ(FILE* wp, zesp z) {
	if (fprintf(wp, "(%lg,%lg)\n", z.re, z.im) < 0) {
		return 0;
	}
	return 1;
}

zesp sprzezenieZ(zesp z) {
	zesp new = {.re=z.re, .im=-z.im};
	return new;
}

double modulZ(zesp z) {
	return sqrt(z.re*z.re + z.im*z.im);
}

double fazaZ(zesp z) {
	double modul = modulZ(z);
	assert(modul != 0);

	double faza;
	if (z.im >= 0) {
		faza = acos(z.re / modul);
	} else {
		faza = 2*M_PI - acos(z.re / modul);
	}
	return faza;
}

zesp sumaZ(zesp z1, zesp z2) {
	zesp out = {.re=z1.re+z2.re, .im=z1.im+z2.im};
	return out;
}

zesp roznicaZ(zesp z1, zesp z2) {
	zesp out = {.re=z1.re-z2.re, .im=z1.im-z2.im};
	return out;
}

zesp iloczynZ(zesp z1, zesp z2) {
	zesp out = {.re=z1.re*z2.re - z1.im*z2.im, .im=z1.re*z2.im + z1.im*z2.re};
	return out;
}

zesp ilorazZ(zesp z1, zesp z2) {
	double mianownik = z2.re*z2.re + z2.im*z2.im;
	assert(mianownik != 0);
	zesp out = {.re=((z1.re*z2.re + z1.im*z2.im) / mianownik), (z1.im*z2.re - z1.re*z2.im) / mianownik};
	return out;
}
