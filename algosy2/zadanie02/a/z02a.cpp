#include <cassert>
#include <iostream>

using num = int;

// n, n+1, n+2, ..., m => 1,2,...,n
num assignFunction1(num i, num n) {
    return i - n + 1;
}

// n, n+2, n+4, ..., m => 1,2,...,n
num assignFunction2(num i, num n) {
    return (i - n) / 2 + 1;
}

// a, b, c, ..., z => 1,2,...,26
num assignFunction3(char c) {
    return c - 'a' + 1;
}

// aa, ab, ..., az, ba, ..., zz => 1,2,...,26*26
num assignFunction4(char c1, char c2) {
    return (c1 - 'a') * 26 + (c2 - 'a') + 1;
}

int main() {
    constexpr num n = 10;

    // test assignFunction1 (m=2*n)
    std::cout << "Test assignFunction1:";
    for (num i = n; i < 2 * n; i++) {
        std::cout << "\nassignFunction1(" << i << ") = " << assignFunction1(i, n);
    }

    // test assignFunction2 (m=2*n)
    std::cout << "\n\nTest assignFunction2:";
    for (num i = n; i < 2 * n; i += 2) {
        std::cout << "\nassignFunction2(" << i << ") = " << assignFunction2(i, n);
    }

    // test assignFunction3
    std::cout << "\n\nTest assignFunction3:";
    for (char c = 'a'; c <= 'z'; c++) {
        std::cout << "\nassignFunction3(" << c << ") = " << assignFunction3(c);
    }

    // test assignFunction4
    std::cout << "\n\nTest assignFunction4:";
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            std::cout << "\nassignFunction4(" << c1 << c2 << ") = " << assignFunction4(c1, c2);
        }
    }

    std::cout << "\n\nTests passed.\n";

    return 0;
}
