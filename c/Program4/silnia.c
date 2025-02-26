#include <stdio.h>

unsigned int silnia_r1(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return silnia_r1(n-1) * n;
}

unsigned int silnia_i1(unsigned int n) {
    unsigned int out = 1;
    for (unsigned int i = 1; i<=n; i++) {
        out *= i;
    }
    return out;
}

int main() {
    unsigned int n;

    printf("n! rekurencyjnie, n = ");
    scanf("%u", &n);
    printf("wynik = %u", silnia_r1(n));

    printf("\n\nn! iteracyjnie, n = ");
    scanf("%u", &n);
    printf("wynik = %u\n", silnia_i1(n));

    return 0;
}
