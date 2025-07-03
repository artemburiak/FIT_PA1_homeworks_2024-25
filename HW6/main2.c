#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define LINE_WRAP_LIMIT 60

void freeCharArray(char** arr, int size) {
    for (int i=0; i<size; i++) {
        free(arr[i]);
    }
    free(arr);
}

void freeIntArray(int** arr, int size) {
    for (int i=0; i<size; i++) {
        free(arr[i]);
    }
    free(arr);
}

void fillArrayZeros(int** arr, int size, int length) {
    for (int i=0; i<size; i++) {
        for (int j=0; j<length; j++) {
            arr[i][j] = 0;
        }
    }
}

int ifLineCorrect(char* line) {
    int length = (int)strlen(line);
    for (int i=0; i<length; i++) {
        if (!(islower(line[i]) || line[i] == '.')) return 0;
    }
    return 1;
}

void printTajenka(char** osmismerka, int** marked_list, int length, int size) {
    printf("Tajenka:\n");
    int iteration = 0;
    for (int i=0; i<size; i++) {
        for (int j=0; j<length; j++) {
            if (marked_list[i][j] == 0 && osmismerka[i][j] != '.') {
                if (iteration == LINE_WRAP_LIMIT) {
                    printf("\n");
                    iteration = 0;
                }
                printf("%c", osmismerka[i][j]);
                iteration++;
            }
        }
    }
    if (iteration > 0) printf("\n");
}

int posExist(int x, int y, int max_x, int max_y) {
    if (x < 0 || x >= max_x || y < 0 || y >= max_y) return 0;
    return 1;
}

void processQuery(char** osmismerka, int** marked_list, int length, int size, char* word, int shouldCross) {
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < length; j++) {
            if (osmismerka[i][j] == word[0]) {
                for (int k = 0; k < 8; k++) {
                    int l;
                    for (l = 1; l < (int)strlen(word); l++) {
                        int new_i = i + l * directions[k][0];
                        int new_j = j + l * directions[k][1];

                        if (!posExist(new_i, new_j, size, length)) break;
                        if (osmismerka[new_i][new_j] != word[l]) break;
                    }

                    if (l == (int)strlen(word)) {
                        count++;

                        if (shouldCross) {
                            for (int m = 0; m < (int)strlen(word); m++) {
                                int mark_i = i + m * directions[k][0];
                                int mark_j = j + m * directions[k][1];
                                marked_list[mark_i][mark_j] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%s: %dx\n", word, count);
}

int main(void) {
    char line[MAX_LINE_LENGTH];

    printf("Osmismerka:\n");
    char* res = fgets(line, sizeof(line), stdin);

    if (!res || line[strlen(line)-1] != '\n') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    line[strlen(line)-1] = '\0';
    int max_line_length = strlen(line);

    if (max_line_length == 0 || !ifLineCorrect(line)) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    char** osmismerka = (char**)malloc(1*sizeof(char*));
    char* osmismerka0 = (char*)malloc(max_line_length*sizeof(char));
    if (osmismerka == NULL || osmismerka0 == NULL) {
        printf("Allocation error.\n");
        free(osmismerka);
        free(osmismerka0);
        return 2;
    }

    osmismerka[0] = osmismerka0;
    strcpy(osmismerka[0], line);

    int index = 1;
    while (1) {
        res = fgets(line, sizeof(line), stdin);
        if (strlen(line) <= 1) {
            break;
        }
        if (!res || line[strlen(line)-1] != '\n') {
            printf("Nespravny vstup.\n");
            freeCharArray(osmismerka, index);
            return 1;
        }
        line[strlen(line)-1] = '\0';
        if ((int)strlen(line) != max_line_length || !ifLineCorrect(line)) {
            printf("Nespravny vstup.\n");
            freeCharArray(osmismerka, index);
            return 1;
        }

        char **temp = (char **)realloc(osmismerka, (index + 1) * sizeof(char *));
        if (!temp) {
            printf("Allocation error.\n");
            freeCharArray(osmismerka, index);
            return 2;
        }
        osmismerka = temp;

        osmismerka[index] = (char *)malloc(max_line_length * sizeof(char));
        if (!osmismerka[index]) {
            printf("Allocation error.\n");
            freeCharArray(osmismerka, index);
            return 2;
        }
        strncpy(osmismerka[index], line, max_line_length);
        index++;
    }

    int** array_marked = (int**)malloc(index*sizeof(int*));
    if (!array_marked) {
        printf("Allocation error.\n");
        freeCharArray(osmismerka, index);
        return 2;
    }

    for (int i = 0; i < index; i++) {
        array_marked[i] = (int *)malloc(max_line_length * sizeof(int));
        if (!array_marked[i]) {
            printf("Allocation error.\n");
            freeCharArray(osmismerka, index);
            freeIntArray(array_marked, i);
            return 2;
        }
    }

    fillArrayZeros(array_marked, index, max_line_length);

    int iteration = 0;
    while (1) {
        char sign = getchar();
        
        if (sign == EOF && iteration != 0) break;
        else if (sign == '?') {
            char endsign = getchar();
            if (endsign != '\n') {
            printf("Nespravny vstup.\n");
            freeCharArray(osmismerka, index);
            freeIntArray(array_marked, index);
            return 1;
            }

            printTajenka(osmismerka, array_marked, max_line_length, index);
            
        }
        else if (sign == '#' || sign == '-') {
            char word[MAX_LINE_LENGTH];
            char end;
            int res = scanf("%s%c", word, &end);
            if (res != 2 || end != '\n' || strlen(word) <= 1) {
                printf("Nespravny vstup.\n");
                freeCharArray(osmismerka, index);
                freeIntArray(array_marked, index);
                return 1;
            }

            if (sign == '#') processQuery(osmismerka, array_marked, max_line_length, index, word, 0);
            else processQuery(osmismerka, array_marked, max_line_length, index, word, 1);
        }
        
        else {
            printf("Nespravny vstup.\n");
            freeCharArray(osmismerka, index);
            freeIntArray(array_marked, index);
            return 1;
        }
        iteration++;
    }

    return 0;
}
