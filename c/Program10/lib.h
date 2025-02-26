#ifndef LIB_H
#define LIB_H

#include <stdio.h>

typedef struct Zespolona {
	double re; // część rzeczywista
	double im; // część urojona
} zesp;

zesp czytajZ(FILE *wp);
int piszZ(FILE *wp, zesp z);

zesp sprzezenieZ(zesp z);
double modulZ(zesp z);
double fazaZ(zesp z);
zesp sumaZ(zesp z1, zesp z2);
zesp roznicaZ(zesp z1, zesp z2);
zesp iloczynZ(zesp z1, zesp z2);
zesp ilorazZ(zesp z1, zesp z2);

#endif
