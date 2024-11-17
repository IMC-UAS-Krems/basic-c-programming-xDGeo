#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


void print_usage(int argc) {
    printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
}

void print_invalid_params() {
    printf("Incorrect usage. The parameters you provided are not positive integers\n");
}

void print_invalid_dimensions() {
    printf("Incorrect usage. The dimensions provided must be greater than 1x1\n");
}

int is_positive_integer(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    if (argc != 3) {
        print_usage(argc);
        return 1;
    }

    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        print_invalid_params();
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    if (rows <= 0 || cols <= 0) {
        print_invalid_params();
        return 1;
    }

    if (rows == 1 && cols == 1) {
        print_invalid_dimensions();
        return 1;
    }

    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (maxrand - minrand + 1) + minrand;
        }
    }

    FILE *f = fopen("matrix.txt", "w");
    if (!f) {
        fprintf(stderr, "Failed to open the file for writing\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(f, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(f, " ");
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}