#include <stdio.h>
#include <stdlib.h>

int append(int** arr, int index, int price) {
    int* temp = (int*)realloc(*arr, sizeof(int) * (index + 1));
    if (temp == NULL) {
        free(arr);
        free(temp);
        return 1;
    }
    *arr = temp;
    (*arr)[index] = price;
    return 0;
}

int processQuery2(int* prices, int from, int to) {

    if (from == to) {
        printf("Nejvyssi zisk: N/A\n");
        printf("Nejvyssi ztrata: N/A\n");
        return 1;
    }

    int maxProfit = -1, maxLoss = -1;
    int buyMomentProfit = -1, sellMomentProfit = -1;
    int buyMomentLoss = -1, sellMomentLoss = -1;

    for (int i=from; i<to; i++) {
        for (int j=i+1; j<=to; j++) {
            int differece = prices[j] - prices[i];
            if (differece > 0) {
                if (maxProfit < differece) {
                    maxProfit = differece;
                    buyMomentProfit = i;
                    sellMomentProfit = j;
                }
            }
            else if (differece < 0) {
                differece = -differece;
                if (maxLoss < differece) {
                    maxLoss = differece;
                    buyMomentLoss = i;
                    sellMomentLoss = j;
                }
            }
        }
    }

    if (maxProfit > 0) {
        printf("Nejvyssi zisk: %d (%d - %d)\n", maxProfit, buyMomentProfit, sellMomentProfit);
    } else {
        printf("Nejvyssi zisk: N/A\n");
    }

    if (maxLoss > 0) {
        printf("Nejvyssi ztrata: %d (%d - %d)\n", maxLoss, buyMomentLoss, sellMomentLoss);
    } else {
        printf("Nejvyssi ztrata: N/A\n");
    }
    return 0;
}

int main(void) {
    int* prices = (int*)malloc(sizeof(int));
    
    if (prices == NULL) {
        printf("Error in memory allocation.\n");
        free(prices);
        return 2;
    }

    int index = 0;

    printf("Ceny, hledani:\n");
    while (1) {

        char sign = getchar();
        if (sign == EOF) {
            break;
        }

        else if (sign != '?' && sign != '+') {
            printf("Nespravny vstup.\n");
            free(prices);
            return 1;
        }

        if (sign == '+') {
            int price;
            char end;
            int res = scanf(" %d%c", &price, &end);
            if (res != 2 || price < 0 || end != '\n') {
                printf("Nespravny vstup.\n");
                free(prices);
                return 1;
            }
            res = append(&prices, index, price);
            if (res) {
                printf("Error in memory allocation.\n");
                free(prices);
                return 2;
            }
            index++;
        }

        else {
            char end;
            int from, to;
            int res = scanf(" %d %d%c", &from, &to, &end);
            if (res != 3 || from < 0 || to < 0 || from > to || end != '\n' || to > index-1) {
                printf("Nespravny vstup.\n");
                free(prices);
                return 1;
            }
            res = processQuery2(prices, from, to);
        }
    }

    free(prices);
    return 0;
}
