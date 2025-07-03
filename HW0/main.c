#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int digit;
    char newline;

    printf("ml' nob:\n");

    if (scanf("%d%c", &digit, &newline) != 2 || newline != '\n') {
        printf("Neh mi'\n");
        return 0;
    }

    if (digit < 0 || digit > 8) {
        printf("Qih mi' %d\n", digit);
        return 0;
    }

    const char *quotes[] = {
        "Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n",
        "Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n",
        "Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n",
        "Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n",
        "Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n",
        "Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n",
        "Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n",
        "Qapla'\nHeghlu'meH QaQ jajvam.\n",
        "Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n"
    };

    printf("%s", quotes[digit]);

    return 0;
}
