#include <stdio.h>
#include <stdlib.h>

#define NC 10
#define INPUT_FILE "dane.txt"
#define OUTPUT_FILE "wyniki.txt"

int main() {
    int c;
    int digits[NC] = {0};
    int whitespace = 0;
    int other = 0;

    FILE* inFile = fopen(INPUT_FILE, "r");
    if (inFile == NULL) {
        printf("Błąd otwierania pliku wejściowego\n");
        exit(1);
    }

    FILE* outFile = fopen(OUTPUT_FILE, "w");
    if (outFile == NULL) {
        printf("Błąd otwierania pliku wyjściowego\n");
        exit(1);
    }

    while((c = fgetc(inFile)) != EOF) {
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

        if (fputc(c, outFile) == EOF) {
            printf("Błąd pisania znaku '%c' do pliku wyjściowego\n", c);
            exit(1);
        }
    }

    if(fprintf(outFile, "\nCyfry:\n") < 0) {
        printf("Błąd pisania do pliku wyjściowego\n");
        exit(1);
    }
    for (unsigned i = 0; i < NC; i++) {
        if(fprintf(outFile, "\t%c: %d\n", '0'+i , digits[i]) < 0) {
            printf("Błąd pisania do pliku wyjściowego\n");
            exit(1);
        }
    }
    if(fprintf(outFile, "Biale znaki: %d\nInne znaki: %d\n", whitespace, other) < 0) {
        printf("Błąd pisania do pliku wyjściowego\n");
        exit(1);
    }

    return 0;
}
