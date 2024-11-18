#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4 // Matrix size (should be a power of 2 for Strassen's)

void traditionalMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Allocate a matrix of given size
int** allocateMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Free allocated matrix
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void add(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize), **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize), **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize), **M2 = allocateMatrix(newSize), **M3 = allocateMatrix(newSize), **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize), **M6 = allocateMatrix(newSize), **M7 = allocateMatrix(newSize);
    int **temp1 = allocateMatrix(newSize), **temp2 = allocateMatrix(newSize);

    // Divide matrices into quarters
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, M1, newSize);

    // M2 = (A21 + A22) * B11
    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp2, newSize);
    strassen(A11, temp2, M3, newSize);

    // M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp2, newSize);
    strassen(A22, temp2, M4, newSize);

    // M5 = (A11 + A12) * B22
    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, M7, newSize);

    // Combine results into C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize); freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize); freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize); freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize); freeMatrix(M7, newSize);
    freeMatrix(temp1, newSize); freeMatrix(temp2, newSize);
}

void performanceTest(int A[SIZE][SIZE], int B[SIZE][SIZE]) {
    int C[SIZE][SIZE];

    clock_t start, end;
    double time_traditional, time_strassen;

    // Traditional Multiplication
    start = clock();
    traditionalMultiplication(A, B, C);
    end = clock();
    time_traditional = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Strassen's Multiplication
    int** A_dyn = allocateMatrix(SIZE);
    int** B_dyn = allocateMatrix(SIZE);
    int** C_dyn = allocateMatrix(SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            A_dyn[i][j] = A[i][j];
            B_dyn[i][j] = B[i][j];
        }

    start = clock();
    strassen(A_dyn, B_dyn, C_dyn, SIZE);
    end = clock();
    time_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Traditional Multiplication Time: %f seconds\n", time_traditional);
    printf("Strassen's Multiplication Time: %f seconds\n", time_strassen);

    freeMatrix(A_dyn, SIZE);
    freeMatrix(B_dyn, SIZE);
    freeMatrix(C_dyn, SIZE);
}

int main() {
    int A[SIZE][SIZE] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int B[SIZE][SIZE] = {{17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};

    performanceTest(A, B);

    return 0;
}
