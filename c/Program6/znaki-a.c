#include <stdio.h>

#define NC 10

int main() {
    int c;
    int digits[NC] = {0};
    int whitespace = 0;
    int other = 0;

    while((c = getchar()) != EOF) {
        switch(c) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
            digits[c - '0']++;
            break;
        }
        case ' ': case '\t': case '\n': {
            whitespace++; 
            break;
        }
        default: {
            other++;
            break;
        }
        }
    }


    printf("Cyfry:\n");
    for (unsigned i = 0; i < NC; i++) {
        printf("\t%c: %d\n", '0'+i , digits[i]);
    }
    printf("Biale znaki: %d\nInne znaki: %d\n", whitespace, other);

    return 0;
}
