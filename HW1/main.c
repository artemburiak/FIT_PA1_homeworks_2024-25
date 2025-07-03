#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y;
} Bod;

int nacti_bod(Bod* bod) {
    char end;
    double x, y;
    int res = scanf(" [ %lf , %lf %c", &x, &y, &end);
    if (res != 3 || end != ']') {
        printf("Nespravny vstup.\n");
        return 1;
    }
    bod->x = x;
    bod->y = y;
    return 0;
}


int jsou_kolinearni(Bod a, Bod b, Bod c) {
    return fabs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 100 * __DBL_EPSILON__ * fabs((b.x - a.x) * (c.y - a.y));
}

int jsou_jeden_bod(Bod a, Bod b) {
    return (a.x==b.x && a.y==b.y);
}

double vzdalenost(Bod a, Bod b) {
    double delta_x = b.x - a.x;
    double delta_y = b.y - a.y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

const char* typ_rovnobezniku(Bod a, Bod b, Bod c, Bod d) {

    double ab = vzdalenost(a, b);
    double bc = vzdalenost(b, c);
    double cd = vzdalenost(c, d);
    double da = vzdalenost(d, a);
    
    double ac = vzdalenost(a, c);

    int je_obdelnik = fabs(ab * ab + bc * bc - ac * ac) < 100 * __DBL_EPSILON__ * fabs(ab * ab + bc * bc);
    int je_kosoctverec = fabs(ab - da) < 100 * __DBL_EPSILON__ * fabs(ab) && fabs(bc - cd) < 100 * __DBL_EPSILON__ * fabs(bc);
    
    if (je_obdelnik && je_kosoctverec) return "ctverec";
    if (je_obdelnik) return "obdelnik";
    if (je_kosoctverec) return "kosoctverec";
    return "rovnobeznik";
}

int main() {
    Bod A, B, C;

    printf("Bod A:\n");
    int res1 = nacti_bod(&A);
    if (res1) return 1;

    printf("Bod B:\n");
    int res2 = nacti_bod(&B);
    if (res2) return 1;

    printf("Bod C:\n");
    int res3 = nacti_bod(&C);
    if (res3) return 1;

    if (jsou_kolinearni(A, B, C) || jsou_jeden_bod(A, B) || jsou_jeden_bod(A, C) || jsou_jeden_bod(B, C)) {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 0;
    }

    Bod A_prime = {B.x + C.x - A.x, B.y + C.y - A.y};
    Bod B_prime = {A.x + C.x - B.x, A.y + C.y - B.y};
    Bod C_prime = {A.x + B.x - C.x, A.y + B.y - C.y};

    printf("A': [%.8g,%.8g], %s\n", A_prime.x, A_prime.y, typ_rovnobezniku(A, B, A_prime, C));
    printf("B': [%.8g,%.8g], %s\n", B_prime.x, B_prime.y, typ_rovnobezniku(A, B, C, B_prime));
    printf("C': [%.8g,%.8g], %s\n", C_prime.x, C_prime.y, typ_rovnobezniku(A, C_prime, B, C));

    return 0;
}
