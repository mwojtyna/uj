#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);

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
    printf("\n");

    return 0;
}

