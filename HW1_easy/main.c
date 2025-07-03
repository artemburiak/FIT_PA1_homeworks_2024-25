#include <stdio.h>
#include <math.h>

int main (void) {
    double a, b, c, d;
    char end;

    printf("Obdelnik #1:\n");
    int res1 = scanf(" %lf %lf%c", &a, &b, &end);
    if (res1 != 3 || a < 0 || b < 0 || end != '\n') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Obdelnik #2:\n");
    int res2 = scanf(" %lf %lf", &c, &d);
    if (res2 != 2 || c < 0 || d < 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    long double square1 = a * b;
    long double square2 = c * d;

    if (fabs(square1 - square2) <= 100 * __DBL_EPSILON__ * fabs(square2)) printf("Obdelniky maji stejny obsah.\n");
    else if (square1 < square2) printf("Obdelnik #1 ma mensi obsah.\n");
    else printf("Obdelnik #2 ma mensi obsah.\n");

    return 0;
}
