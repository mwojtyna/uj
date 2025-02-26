#include <stdio.h>

unsigned fib(unsigned n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    return fib(n-1) + fib(n-2);
}

int main() {
    unsigned n;
    printf("n = ");
    scanf("%u", &n);

    printf("%u\n", fib(n));

    return 0;
}
