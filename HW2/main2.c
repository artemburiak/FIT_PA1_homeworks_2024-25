#include <stdio.h>
#include <math.h>


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortThreeNums(int* x, int* y, int* z) {
    if (*x > *z) {
        swap(x, z);
    }
    if (*y > *z) {
        swap(y, z);
    }
    if (*x > *y) {
        swap(x, y);
    }
}

void findTraingles(int a, int b, int type) {
    int pocet = 0;

    for (int x=a; x<=b; x++) {
        for (int y=a; y<=b; y++) {
            for (int z=a; z<=b; z++) {
                if (x > y) {
                    continue;
                }
                if (z * z == x * x + y * y) {
                    if (type) printf("* %d %d %d\n", x, y, z);
                    pocet ++;
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

        if (prikaz == '?') findTraingles(lo, hi, 1);
        else findTraingles(lo, hi, 0);
    }

    return 0;
}
