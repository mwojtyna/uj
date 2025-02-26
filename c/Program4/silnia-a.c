#include <stdio.h>
#include <limits.h>
#include <float.h>

unsigned int silnia_r1(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return silnia_r1(n-1) * n;
}

unsigned long silnia_i2(unsigned int n) {
    unsigned long out = 1;
    for (unsigned int i = 1; i<=n; i++) {
        out *= i;
    }
    return out;
}

double silnia_i3(unsigned int n) {
    double out = 1.0;
    for (unsigned int i = 1; i<=n; i++) {
        out *= i;
    }
    return out;
}

int main() {
    unsigned int n;

    printf("n! rekurencyjnie (unsigned int, max = %u), n = ", UINT_MAX);
    scanf("%u", &n);
    printf("wynik = %u", silnia_r1(n));

    printf("\n\nn! iteracyjnie (unsigned long, max = %lu), n = ", ULONG_MAX);
    scanf("%u", &n);
    printf("wynik = %lu", silnia_i2(n));

    printf("\n\nn! iteracyjnie (double, max = %g), n = ", DBL_MAX);
    scanf("%u", &n);
    printf("wynik = %g\n", silnia_i3(n));

    return 0;
}
