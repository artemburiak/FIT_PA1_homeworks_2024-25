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

void printCoordsArray(const CoordsArray* arr) {
    if (arr->size > 1) {
        printf("%c%d", arr->data[0].x, arr->data[0].y);
        for (size_t i = 1; i < arr->size; i++) {
            printf(" -> %c%d", arr->data[i].x, arr->data[i].y);
        }
        printf(" +%zu\n", arr->size-1);
    }
}

int main() {
    CoordsArray coordsArray;
    initCoordsArray(&coordsArray, 2);

    Coords c1 = {'a', 2};
    appendCoords(&coordsArray, c1);
    Coords c2 = {'b', 4};
    appendCoords(&coordsArray, c2);
    Coords c3 = {'c', 6};
    appendCoords(&coordsArray, c3);

    printCoordsArray(&coordsArray);

    popCoords(&coordsArray);

    printCoordsArray(&coordsArray);

    freeCoordsArray(&coordsArray);

    return 0;
}
