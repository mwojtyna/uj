#include <stdio.h>

double silnia_r1(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return silnia_r1(n-1) * n;
    }
}

double silnia_r2(unsigned int n) {
    return n == 0 || n == 1 ? 1 : silnia_r2(n-1) * n;
}

int main() {
    unsigned int n;

    printf("n! rekurencyjnie, n = ");
    scanf("%u", &n);
    printf("wynik = %g", silnia_r1(n));

    printf("\n\nn! rekurencyjnie, n = ");
    scanf("%u", &n);
    printf("wynik = %g\n", silnia_r2(n));

    return 0;
}
