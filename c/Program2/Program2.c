#include <stdio.h>

#define LOWER_F 0
#define UPPER_F 300
#define LOWER_C -100
#define UPPER_C 100
#define STEP_C 10
#define STEP_F 20

int main() {
    printf("Kalkulator °C do °F \n");
    printf("UJ FAIS Mateusz Wojtyna 24.10.2024\n\n");

    printf("Konwersja F do C rosnąco:\n");
    for (int fahr = LOWER_F; fahr <= UPPER_F; fahr += STEP_F) {
        const float cels = (5.0/9) * (fahr - 32);
        printf("%d°F = %.2f°C\n", fahr, cels);
    }
    printf("\n");

    printf("Konwersja F do C malejąco:\n");
    for (int fahr = UPPER_F; fahr >= LOWER_F; fahr -= STEP_F) {
        const float cels = (5.0/9) * (fahr - 32);
        printf("%d°F = %.2f°C\n", fahr, cels);
    }

    printf("\n");

    printf("Konwersja C do F rosnąco:\n");
    for (int cels = LOWER_C; cels <= UPPER_C; cels += STEP_C) {
        const float fahr = cels * (9.0/5) + 32;
        printf("%d°C = %.2f°F\n", cels, fahr);
    }

    printf("\n");

    printf("Konwersja C do F malejąco:\n");
    for (int cels = UPPER_C; cels >= LOWER_C; cels -= STEP_C) {
        const float fahr = cels * (9.0/5) + 32;
        printf("%d°C = %.2f°F\n", cels, fahr);
    }

    return 0;
}
