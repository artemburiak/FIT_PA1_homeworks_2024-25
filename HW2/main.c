#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

void find_triangles(int lo, int hi, int type) {
    int pocet = 0;

    for (int m = 2; m * m <= hi; ++m) {
        for (int n = 1; n < m; ++n) {
            if ((m - n) % 2 == 1 && gcd(m, n) == 1) {
                int a = m * m - n * n;
                int b = 2 * m * n;
                int c = m * m + n * n;

                if (a > b) {
                    int tmp = a;
                    a = b;
                    b = tmp;
                }

                int k = 1;
                while (k * a <= hi && k * b <= hi && k * c <= hi) {
                    if (k * a >= lo && k * b >= lo && k * c >= lo) {
                        if (type) {
                            printf("* %d %d %d\n", k * a, k * b, k * c);
                        }
                        pocet++;
                    }
                    k++;
                }
            }
        }
    }

    printf("Celkem: %d\n", pocet);
}

int main(void) {
    char prikaz, zbytek;
    int lo, hi;

    printf("Problemy:\n");

    while (scanf(" %c < %d ; %d %c", &prikaz, &lo, &hi, &zbytek) != EOF) {
        if ((prikaz != '?' && prikaz != '#') || lo <= 0 || hi <= 0 || lo > hi || zbytek != '>') {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if (prikaz == '?') find_triangles(lo, hi, 1);
        else find_triangles(lo, hi, 0);
    }

    return 0;
}
