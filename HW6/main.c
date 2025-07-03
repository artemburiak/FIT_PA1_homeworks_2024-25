#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

int pairs[8][2] = {
    {0, 1}, 
    {0, -1}, 
    {1, 0}, 
    {-1, 0}, 
    {1, 1}, 
    {1, -1}, 
    {-1, 1}, 
    {-1, -1}
};

void freeGrid(char **grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

char **loadGrid(int *rows, int *cols) {
    char **grid = NULL;
    char line[MAX_LINE_LEN];
    int colsCount = -1;

    *rows = 0;
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n') break;

        int len = strlen(line);
        if (line[len - 1] == '\n') line[--len] = '\0';

        if (colsCount == -1) {
            colsCount = len;
        } else if (len != colsCount || (int)strspn(line, "abcdefghijklmnopqrstuvwxyz.") != len) {
            freeGrid(grid, *rows);
            return NULL;
        }

        grid = (char **)realloc(grid, (*rows + 1) * sizeof(char *));
        grid[*rows] = strdup(line);
        (*rows)++;
    }

    if (*rows == 0 || colsCount == -1) return NULL;

    *cols = colsCount;
    return grid;
}

int isWordMatch(char **grid, int rows, int cols, const char *word, int row, int col, int dirRow, int dirCol) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int r = row + i * dirRow;
        int c = col + i * dirCol;
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != word[i]) return 0;
    }
    return 1;
}

void markWord(char **marked, int row, int col, int dirRow, int dirCol, int len) {
    for (int i = 0; i < len; i++) {
        marked[row + i * dirRow][col + i * dirCol] = 1;
    }
}

int findWord(char **grid, char **marked, int rows, int cols, const char *word, int mark) {
    int count = 0;
    int len = strlen(word);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            for (int d = 0; d < 8; d++) {
                int dirRow = pairs[d][0], dirCol = pairs[d][1];
                if (isWordMatch(grid, rows, cols, word, r, c, dirRow, dirCol)) {
                    count++;
                    if (mark) markWord(marked, r, c, dirRow, dirCol, len);
                }
            }
        }
    }
    return count;
}

void printTajenka(char **grid, char **marked, int rows, int cols) {
    int index = 0, maxSize = rows * cols;
    char *tajenka = (char *)malloc(maxSize + 1);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!marked[r][c] && grid[r][c] != '.') {
                tajenka[index++] = grid[r][c];
            }
        }
    }
    tajenka[index] = '\0';

    printf("Tajenka:\n");
    for (int i = 0; i < index; i += 60) {
        printf("%.*s\n", 60, &tajenka[i]);
    }

    free(tajenka);
}

int isValidWord(const char *word) {
    if (strlen(word) < 2) return 0;
    for (const char *p = word; *p; p++) {
        if (!islower(*p)) return 0;
    }
    return 1;
}

int processCommand(char **grid, char **marked, int rows, int cols, const char *cmd) {
    while (isspace(*cmd)) cmd++;

    if (*cmd == '?') {
        cmd++;
        while (isspace(*cmd)) cmd++;
        if (*cmd != '\0') return 0;

        printTajenka(grid, marked, rows, cols);
    } else if (*cmd == '-' || *cmd == '#') {
        int mark = (*cmd == '-') ? 1 : 0;
        cmd++;
        while (isspace(*cmd)) cmd++;
        const char *word = cmd;
        while (*cmd && !isspace(*cmd)) cmd++;
        char temp[MAX_LINE_LEN];
        strncpy(temp, word, cmd - word);
        temp[cmd - word] = '\0';

        if (!isValidWord(temp)) return 0;

        int count = findWord(grid, marked, rows, cols, temp, mark);
        printf("%s: %dx\n", temp, count);
    } else {
        return 0;
    }

    return 1;
}

int main(void) {
    printf("Osmismerka:\n");

    int rows, cols;
    char **grid = loadGrid(&rows, &cols);
    if (!grid) {
        printf("Nespravny vstup.\n");
        return -1;
    }

    char **marked = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        marked[i] = (char *)calloc(cols, sizeof(char));
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        if (!processCommand(grid, marked, rows, cols, line)) {
            printf("Nespravny vstup.\n");
            freeGrid(grid, rows);
            freeGrid(marked, rows);
            return -1;
        }
    }

    freeGrid(grid, rows);
    // freeGrid(marked, rows);
    return 0;
}
