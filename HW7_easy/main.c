#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SPLIT_LENGTH 1024

int compare_numeric_strings(char *a, int len_a, char *b, int len_b) {
    while (len_a > 0 && *a == '0') {
        a += 1;
        len_a -= 1;
    }

    while (len_b > 0 && *b == '0') {
        b += 1;
        len_b -= 1;
    }
    
    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;

    for (int i = 0; i < len_a; i++) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }

    return 0;
}

int is_even(char *str, int len) {
    if (len == 0) return 0;
    char last = str[len - 1];
    return (last - '0') % 2 == 0;
}

long long count_splits(char *s, int n, int pos, char *prev, int prev_len) {
    if (pos == n) return 1;
    
    long long total = 0;
    for (int end = pos + 1; end <= n; end++) {
        int curr_len = end - pos;
        char *curr = s + pos;
        if (prev != NULL && is_even(prev, prev_len)) {
            int cmp = compare_numeric_strings(prev, prev_len, curr, curr_len);
            if (cmp > 0) {
                continue;
            }
        }
        total += count_splits(s, n, end, curr, curr_len);
    }
    return total;
}

void find_splits(char *s, int n, int pos, char *prev, int prev_len, char *current_split, int split_len, long long *count) {

    if (pos == n) {
        current_split[split_len] = '\0';
        printf("* %s\n", current_split);
        (*count)++;
    }

    for (int end = pos + 1; end <= n; end++) {
        int curr_len = end - pos;
        char *curr = s + pos;

        if (prev != NULL && is_even(prev, prev_len)) {
            int cmp = compare_numeric_strings(prev, prev_len, curr, curr_len);

            if (cmp > 0) {
                continue;
            }
        }

        int new_split_len = split_len;

        if (pos != 0) {
            current_split[new_split_len++] = ',';
        }

        memcpy(current_split + new_split_len, curr, curr_len);
        new_split_len += curr_len;
        find_splits(s, n, end, curr, curr_len, current_split, new_split_len, count);
    }
}

int main() {
    printf("Posloupnost:\n");
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);

        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        int i = 0;

        while (i < len && isspace(line[i])) i++;
        if (i >= len) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        char type = line[i];

        if (type != '?' && type != '#') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        i++;

        while (i < len && isspace(line[i])) i++;
        if (i >= len) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        int start = i;

        while (i < len && isdigit(line[i])) i++;

        int digit_len = i - start;

        if (digit_len == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        while (i < len) {
            if (!isspace(line[i])) {
                printf("Nespravny vstup.\n");
                return 0;
            }
            i++;
        }

        char *digits = line + start;

        if (type == '#') {
            long long total = count_splits(digits, digit_len, 0, NULL, 0);
            printf("Celkem: %lld\n", total);
        }
        else if (type == '?') {
            char *current_split = (char *)malloc((digit_len * 2 + 1) * sizeof(char));

            if (current_split == NULL) {
                printf("Nespravny vstup.\n");
                return 0;
            }

            long long count = 0;
            find_splits(digits, digit_len, 0, NULL, 0, current_split, 0, &count);
            free(current_split);
            printf("Celkem: %lld\n", count);
        }
    }

    return 0;
}
