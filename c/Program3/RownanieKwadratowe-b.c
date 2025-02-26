#include <stdio.h>
#include <math.h>

int main() {
    char next;
    do {
        double a, b, c;
        scanf("%lf%lf%lf", &a, &b, &c);

        // Dopisz + lub - przed b i c
        char signB = b >= 0 ? '+' : '-';
        char signC = c >= 0 ? '+' : '-';
        printf("%.2lf*x^2 %c %.2lf*x %c %.2lf = 0\n", a, signB, fabs(b), signC, fabs(c));

        double delta = b*b - 4*a*c;
        if (delta > 0) {
            double sqrtDelta = sqrt(delta);
            double x1 = (-b + sqrtDelta) / 2*a;
            double x2 = (-b - sqrtDelta) / 2*a;
            printf("x1=%lf\nx2=%lf", x1, x2);
        } else if (delta == 0) {
            double x0 = -b / 2*a;
            printf("x=%lf", x0);
        } else {
            printf("Brak pierwiastków rzeczywistych");
        }

        printf("\nCzy chcesz kontynuowac? [t/n]: ");
        scanf(" %c", &next); // spacja przed %c żeby nie przypisało zmiennej '\n' do "next"
    } while(next == 't');

    return 0;
}

