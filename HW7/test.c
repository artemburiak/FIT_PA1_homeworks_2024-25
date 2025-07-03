#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла бинарного дерева
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для добавления элемента в стек
void push(int* stack, int* top, int value) {
    stack[++(*top)] = value;
}

// Функция для удаления элемента из стека
void pop(int* top) {
    if (*top >= 0) {
        (*top)--;
    }
}

// Функция для печати текущего состояния стека
void printStack(int* stack, int top) {
    printf("[");
    for (int i = 0; i <= top; i++) {
        printf("%d", stack[i]);
        if (i < top) {
            printf(", ");
        }
    }
    printf("]\n");
}

void traverseWithStack(Node* root, int* stack, int* top) {
    if (root == NULL) {
        return;
    }

    push(stack, top, root->data);
    printStack(stack, *top);

    traverseWithStack(root->left, stack, top);

    traverseWithStack(root->right, stack, top);

    pop(top);
}

// Очистка памяти дерева
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Создание дерева
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Инициализация стека
    int stack[100]; // Достаточно большой массив для хранения значений
    int top = -1;   // Указатель на вершину стека

    // Обход дерева с управлением стеком
    printf("Traversal with stack management:\n");
    traverseWithStack(root, stack, &top);

    // Освобождение памяти
    freeTree(root);

    int lst[4] = {10, 20, 30, 40};
    printStack(lst, 3);

    return 0;
}
