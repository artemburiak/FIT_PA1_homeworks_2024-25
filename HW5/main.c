#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

// Function to initialize the price list
void initPriceList(int **prices, int *size, int *capacity) {
    *size = 0; // Initial size of the price list
    *capacity = 10; // Initial capacity of the array
    *prices = (int *)malloc(sizeof(int) * (*capacity)); // Allocating memory for the price list

    // If memory allocation fails: 
    if (*prices == NULL) exit(1);
}

// Function to add a new price to the list
void addPrice(int **prices, int *size, int *capacity, int price) {

    // Check if sizes are correct and if we need to change it:
    if (*size == *capacity) {
        *capacity *= 2;
        *prices = (int *)realloc(*prices, sizeof(int) * (*capacity)); // Reallocating memory

        // If memory allocation fails:
        if (*prices == NULL) exit(1);
    }
    (*prices)[*size] = price; // Adding the new price to the array
    (*size)++;
}

// Function to process a query to find maximum profit and loss in a given range
void processQuery(int *prices, int size, int from, int to) {

    // Validating the input range: 
    if (from < 0 || to >= size || from > to) {
        printf("Nespravny vstup.\n");
        exit(0);
    }

    int maxProfit = INT_MIN, maxLoss = INT_MIN;
    int buyTimeProfit = -1, sellTimeProfit = -1;
    int buyTimeLoss = -1, sellTimeLoss = -1;

    int minPrice = prices[from], minPriceIndex = from;
    int maxPrice = prices[from], maxPriceIndex = from;

    // Calculating max. Profit, Loss: 
    for (int i = from + 1; i <= to; i++) {

        // If new max. Profit: 
        if (prices[i] - minPrice > maxProfit) {
            maxProfit = prices[i] - minPrice;
            buyTimeProfit = minPriceIndex;
            sellTimeProfit = i;
        }

        // If new max. Loss:
        if (maxPrice - prices[i] > maxLoss) {
            maxLoss = maxPrice - prices[i];
            buyTimeLoss = maxPriceIndex;
            sellTimeLoss = i;
        }

        // Updating max. price if a higher price is found:
        if (prices[i] > maxPrice) {
            maxPrice = prices[i];
            maxPriceIndex = i;
        }

        // Updating min. price if a lower price is found: 
        if (prices[i] < minPrice) {
            minPrice = prices[i];
            minPriceIndex = i;
        }
    }

    // Printing results:

    // Max. Profit:
    if (maxProfit > 0) printf("Nejvyssi zisk: %d (%d - %d)\n", maxProfit, buyTimeProfit, sellTimeProfit);
    else printf("Nejvyssi zisk: N/A\n");

    // Max. Loss:
    if (maxLoss > 0) printf("Nejvyssi ztrata: %d (%d - %d)\n", maxLoss, buyTimeLoss, sellTimeLoss);
    else printf("Nejvyssi ztrata: N/A\n");
}

int main() {
    int *prices; // To store dynamic array of prices
    int size, capacity;
    initPriceList(&prices, &size, &capacity);

    printf("Ceny, hledani:\n");

    char input[256]; // To store user input

    // Main function logic:
    while (fgets(input, sizeof(input), stdin)) {

        // If user types '+' on the beginning: 
        if (input[0] == '+') {
            int price;
            char extra;

            // Validating user input: 
            if (sscanf(input + 1, "%d %c", &price, &extra) != 1 || price < 0) {
                printf("Nespravny vstup.\n");
                free(prices);
                return 0;
            }
            addPrice(&prices, &size, &capacity, price);
        } 
        
        // If user types '?' on the beginning: 
        else if (input[0] == '?') {
            int from, to;
            char extra;

            // Validating user input: 
            if (sscanf(input + 1, "%d %d %c", &from, &to, &extra) != 2) {
                printf("Nespravny vstup.\n");
                free(prices);
                return 0;
            }
            processQuery(prices, size, from, to);
        } 
        
        // If user types anything else: (Wrong input)
        else {
            printf("Nespravny vstup.\n");
            free(prices);
            return 0;
        }
    }


    #ifndef __PROGTEST__

    assert(prices != NULL); //Prices array should not be NULL.
    assert(size >= 0); //Size should be non-negative.
    assert(capacity >= size); //Capacity should be at least equal to size.
    for (int i = 0; i < size; ++i) {
        assert(prices[i] >= 0); //Each price should be non-negative.
    }

    #endif /* __PROGTEST__ */

    free(prices); 
    return 0;
}
