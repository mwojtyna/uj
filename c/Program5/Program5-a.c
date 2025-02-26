#include <stdio.h>

unsigned fib(unsigned n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned tab[n];
    tab[0] = 0;
    tab[1] = 1;

    for (unsigned i = 2; i <= n; i++) {
        tab[i] = tab[i-1] + tab[i-2];
    }

    return tab[n];
}

int main() {
    unsigned n;
    printf("n = ");
    scanf("%u", &n);

    printf("%u\n", fib(n));

    return 0;
}
