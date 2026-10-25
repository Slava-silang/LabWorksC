#include <stdio.h>
#include <stdlib.h>
/*
int main() {
    unsigned int order;
    printf("Enter matrix order: ");
    scanf("%u", &order);
    int *matrix = (int *)malloc((order*order) * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    const unsigned int pointer_size = (order - 1) * 2;
    int *pointer = (int *)malloc(pointer_size * sizeof(int));
    if (pointer == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter matrix elements: ");
    for (int i = 0; i < order*order; i++) {
        scanf("%d", &matrix[i]);
    }
    for (int i = 0; i < order - 1; ++i) {
        pointer[i] = i + 2;
        pointer[pointer_size - i - 1] = i + 2;
    }
    int row = 0, column = 0;
    for (int i = 0; i < order; ++i) {
        row += i;
        column = 0;
        printf("%-3d ", matrix[row]);
        for (int j = 0; j < order - 1; ++j) {
            column += pointer[j + i];
            printf("%-3d ", matrix[row + column]);
        }
        printf("\n");
    }
    return 0;
}
*/

int main() {
    unsigned int order;
    printf("Enter order: ");
    scanf("%u", &order);
    int *matrix = (int *)malloc(order * order * sizeof(int));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter matrix: \n");
    for (int i = 0; i < order*order; i++) {
        scanf("%d", &matrix[i]);
    }
    unsigned int index = 0;

    printf("%d ", matrix[index]);
    for (int i = 0; i < order - 1; i++) {
        index = index + order + i * (order - 1);
        for (int j = 0; j <= i + 1; j++) {
            index = j == 0 ? index : index - (order - 1);
            printf("%d ", matrix[index]);
        }
    }
    for (int i = (int)order - 2; i >= 0; i--) {
        index = index + order + i * (order - 1);
        for (int j = 0; j <= i; j++) {
            index = j == 0 ? index : index - (order - 1);
            printf("%d ", matrix[index]);
        }
    }
}