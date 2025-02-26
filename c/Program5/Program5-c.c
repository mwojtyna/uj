#include <stdio.h>

void fib(unsigned n, double tab[]) {
    tab[0] = 0;
    tab[1] = 1;
    for (unsigned i = 2; i <= n; i++) {
        tab[i] = tab[i-1] + tab[i-2];
    }
}

int main() {
    unsigned n, i_min, i_max;

    printf("rozmiar tablicy = ");
    scanf("%u", &n);

    double tab[n];

    do {
        printf("Indeks początkowy (włącznie) = ");
        scanf("%u", &i_min);
    } while(i_min < 0 || i_min >= n);

    do {
        printf("Indeks końcowy (włącznie) = ");
        scanf("%u", &i_max);
    } while(i_max < i_min || i_max >= n);

    fib(n, tab);

    for (unsigned i = i_min; i <= i_max; i++) {
        printf("%g\n", tab[i]);
    }
    printf("\n");

    return 0;
}
