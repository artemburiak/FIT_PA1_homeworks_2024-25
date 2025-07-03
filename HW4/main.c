#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TRANSPORTS 100000

typedef struct {
    int from;
    int to;
    int capacity;
    int price;
} Transport;

Transport transports[MAX_TRANSPORTS];
int transport_count = 0;

void skip_whitespace() {
    char c;
    while (1) {
        c = getchar();
        if ( !isspace(c)) {
            break;
        }
    }
    ungetc(c, stdin);
}


int read_transport_options() {
    char c;
    skip_whitespace();
    c = getchar();
    if (c != '{') {
        printf("Nespravny vstup.\n");
        return 0;
    }

    while (1) {
        if (transport_count >= MAX_TRANSPORTS) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        skip_whitespace();
        c = getchar();
        if (c != '[') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        int from, to, capacity, price;
        skip_whitespace();
        int res = scanf("%d - %d , %d , %d", &from, &to, &capacity, &price);
        if (res != 4 || from < 0 || to < 0 || from > to || capacity <= 0 || price <= 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        skip_whitespace();
        c = getchar();
        if (c != ']') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        skip_whitespace();
        c = getchar();

        if (c == ',' || c == '}') {
            transports[transport_count].from = from;
            transports[transport_count].to = to;
            transports[transport_count].capacity = capacity;
            transports[transport_count].price = price;
            transport_count++;

            if (c == '}') break;
        }
        else {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    return 1;
}

// Function to handle each cargo request
void solve_request(int start_day, int load) {
    int current_load = 0;
    int end_day = start_day;
    long long total_cost = 0;

    // Calculate maximum possible load from `start_day` onward
    int max_possible_load = 0;
    for (int i = 0; i < transport_count; i++) {
        if (transports[i].to >= start_day) {
            int effective_from = (transports[i].from < start_day) ? start_day : transports[i].from;
            max_possible_load += transports[i].capacity * (transports[i].to - effective_from + 1);
        }
    }

    // Early exit if `max_possible_load` is less than the required `load`
    if (max_possible_load < load) {
        printf("Prilis velky naklad, nelze odvezt.\n");
        return;
    }

    // Process days from `start_day` onward to fulfill the required load
    while (current_load < load) {
        int day_capacity = 0;
        int day_cost = 0;

        // Check each transport option for availability on `end_day`
        for (int i = 0; i < transport_count; i++) {
            if (transports[i].from <= end_day && transports[i].to >= end_day) {
                day_capacity += transports[i].capacity;
                day_cost += transports[i].price;
            }
        }

        // If no capacity available on this day, skip to the next day
        if (day_capacity == 0) {
            end_day++;
            continue;
        }

        // Add the day's capacity to the total load moved and accumulate the cost
        current_load += day_capacity;
        total_cost += day_cost;

        // Move to the next day if load is not yet fully transported
        if (current_load < load) {
            end_day++;
        }
    }

    printf("Konec: %d, cena: %lld\n", end_day, total_cost);
}

// Function to read and validate requests
void read_requests() {
    int start_day, load;
    while (1) {
        int res = scanf("%d %d", &start_day, &load);
        if (res != 2) {
            break;
        }
        if (start_day < 0 || load <= 0) {
            printf("Nespravny vstup.\n");
            return;
        }
        solve_request(start_day, load);
    }
}

int main() {
    printf("Moznosti dopravy:\n");

    // Read and validate transport options
    if (!read_transport_options()) {
        return 0;
    }

    printf("Naklad:\n");

    // Read and process requests
    read_requests();

    return 0;
}
