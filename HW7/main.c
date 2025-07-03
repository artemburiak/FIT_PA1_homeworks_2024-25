#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char x;
    int y;
} Coords;

typedef struct {
    Coords* data;
    size_t size;
    size_t capacity;
} CoordsArray;

void initCoordsArray(CoordsArray* arr, size_t initialCapacity) {
    arr->data = (Coords*)malloc(initialCapacity * sizeof(Coords));
    arr->size = 0;
    arr->capacity = initialCapacity;
}

void freeCoordsArray(CoordsArray* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void appendCoords(CoordsArray* arr, Coords coord) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Coords*)realloc(arr->data, arr->capacity * sizeof(Coords));
    }
    arr->data[arr->size] = coord;
    arr->size++;
}

void popCoords(CoordsArray* arr) {
    if (arr->size > 0) {
        arr->size--;
    } else {
        printf("Array is already empty. Cannot pop.\n");
    }
}

int printCoordsArray(const CoordsArray* arr) {
    if (arr->size > 1) {
        printf("%c%d", arr->data[0].x, arr->data[0].y);
        for (size_t i = 1; i < arr->size; i++) {
            printf(" -> %c%d", arr->data[i].x, arr->data[i].y);
        }
        printf(" +%zu\n", arr->size-1);
        return 1;
    }
    return 0;
}

int getLetterNumber(char letter) {
    char abc[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; abc[i] != '\0'; i++) {
        if (abc[i] == letter) {
            return i + 1;
        }
    }
    return -1;
}

char getLetterFromNumber(int number) {
    char abc[] = "abcdefghijklmnopqrstuvwxyz";

    if (number >= 1 && number <= 26) return abc[number-1];
    else return '?';
}

int validInput(int size, char type, char posChar, int posInt) {
    if (type != 'w' && type != 'W' && type != 'b' && type != 'B') return 0;

    int posCharNumber = getLetterNumber(posChar);

    if (posCharNumber == -1) return 0;
    if (posInt > size || posCharNumber > size || posInt < 1 || posCharNumber < 1) return 0;
    if ((posInt % 2 == 0 && posCharNumber % 2 != 0) || (posInt % 2 != 0 && posCharNumber % 2 == 0)) return 0;
    return 1;
}

char** create2DBoard(int size, char initial) {
    char** array = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        array[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            array[i][j] = initial;
        }
    }
    return array;
}

void printBoard(int size, char** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void freeBoard(int size, char** board) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

int isCellExists(char** board, int size, int i, int j) {
    if (i < 0 || i >= size || j < 0 || j >= size) return 0;
    return 1;
}

int isCellFree(char** board, int size, int i, int j) {
    if (board[i][j] == '-') return 1;
    return 0;
}

int isCellBlack(char** board, int size, int i, int j) {
    if (board[i][j] == 'B' || board[i][j] == 'b') return 1;
    return 0;
}

void checkWhitePieceMoves(char** board, int size, int pos_i, int pos_j, int* count) {
    int new_i = pos_i + 1;
    int new_j = pos_j + 1;
    if (isCellExists(board, size, new_i, new_j) && isCellFree(board, size, new_i, new_j)) {
        printf("%c%d -> %c%d\n", getLetterFromNumber(pos_j+1), pos_i+1, getLetterFromNumber(new_j+1), new_i+1);
        *count += 1;
    }
    new_i = pos_i + 1;
    new_j = pos_j - 1;
    if (isCellExists(board, size, new_i, new_j) && isCellFree(board, size, new_i, new_j)) {
        printf("%c%d -> %c%d\n", getLetterFromNumber(pos_j+1), pos_i+1, getLetterFromNumber(new_j+1), new_i+1);
        *count += 1;
    }
}

void checkWhitePieceCaptures(char** board, int size, int i_from, int j_from, int i_to, int j_to, CoordsArray* buffer, int* count) {
    if (j_to < j_from && !(isCellExists(board, size, i_to, j_to) && isCellExists(board, size, i_to-1, j_to+1) && isCellBlack(board, size, i_to-1, j_to+1) && isCellFree(board, size, i_to, j_to))) {
        return;
    }
    if (j_to > j_from && !(isCellExists(board, size, i_to, j_to) && isCellExists(board, size, i_to-1, j_to-1) && isCellBlack(board, size, i_to-1, j_to-1) && isCellFree(board, size, i_to, j_to))) {
        return;
    }

    Coords c = {getLetterFromNumber(j_to+1), i_to+1};
    appendCoords(buffer, c);
    int res = printCoordsArray(buffer);
    if (res) *count += 1;
    
    checkWhitePieceCaptures(board, size, i_to, j_to, i_to+2, j_to+2, buffer, count);
    checkWhitePieceCaptures(board, size, i_to, j_to, i_to+2, j_to-2, buffer, count);

    popCoords(buffer);
}

int main() {
    int size;
    char type, posChar;
    int posInt;

    printf("Velikost hraci plochy:\n");

    if ((scanf(" %d", &size) != 1) || (size < 3 || size > 26)) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    char** board = create2DBoard(size, '-');

    printf("Pozice kamenu:\n");

    while (scanf(" %c %c%2d", &type, &posChar, &posInt) != EOF) {
        if (validInput(size, type, posChar, posInt) == 0) {
            printf("Nespravny vstup.\n");
            freeBoard(size, board);
            return 1;
        }
        int posCharIndex = getLetterNumber(posChar) - 1;
        int posIntIndex = posInt - 1;
        board[posIntIndex][posCharIndex] = type;
    }

    printBoard(size, board);

    int count = 0;
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (board[i][j] == 'w') {
                int count1 = 0;
                checkWhitePieceMoves(board, size, i, j, &count1);

                int count2 = 0;
                CoordsArray coordsArray;
                initCoordsArray(&coordsArray, 2);
                checkWhitePieceCaptures(board, size, i, j, i, j, &coordsArray, &count2);
                freeCoordsArray(&coordsArray);

                count += count1;
                count += count2;
            }
            else if (board[i][j] == 'W') {

            }
        }
    }
    printf("Celkem: %d\n", count);

    freeBoard(size, board);
    return 0;
}
