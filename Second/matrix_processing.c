//
// Created by slava on 26.10.2026.
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./matrix_processing <input-file>\n");
        return 1;
    }

    int matrix[64] = {};
    int ch;
    int length = 0;
    int min[2] = {0};
    int max[2] = {0};

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }
    while ((fscanf(file, "%d", &ch) == 1)) {
        if (length == 64) {
            fprintf(stderr, "Matrix too large\n");
            return 1;
        }
        matrix[length++] = ch;
    }
    fclose(file);

    const int order = (int)sqrt((double)length);

    if (order * order != length) {
        fprintf(stderr, "Matrix is not square\n");
        return 1;
    }

    int temp_mul = 1;

    for (int i = 0; i < order; i++) {
        temp_mul = 1;

        for (int j = 0; j < order; j++) {
            temp_mul *= matrix[i * order + j];
        }

        if (i == 0 || temp_mul < min[0]) {
            min[0] = temp_mul;
            min[1] = i;
        }

        if (i == 0 || temp_mul > max[0]) {
            max[0] = temp_mul;
            max[1] = i;
        }
    }

    const int min_row = min[1] * order;
    const int max_row = max[1] * order;

    for (int i = 0; i < order; i++) {
        const int temp = matrix[min_row + i];
        matrix[min_row + i] = matrix[max_row + i];
        matrix[max_row + i] = temp;
    }
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            printf("%-3d", matrix[i * order + j]);
        }
        printf("\n");
    }
}