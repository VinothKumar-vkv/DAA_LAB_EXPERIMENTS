
#include <stdio.h>
#include <stdlib.h>

// Function to perform standard matrix addition
void addMatrix(int size, int A[size][size], int B[size][size], int C[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to perform standard matrix subtraction
void subMatrix(int size, int A[size][size], int B[size][size], int C[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to implement Strassen's Algorithm for matrix multiplication
void strassen(int size, int A[size][size], int B[size][size], int C[size][size]) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize], M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Dividing the matrices into submatrices
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

    // Computing the 7 products using Strassenís formula
    addMatrix(newSize, A11, A22, temp1);
    addMatrix(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1);

    addMatrix(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2);

    subMatrix(newSize, B12, B22, temp2);
    strassen(newSize, A11, temp2, M3);

    subMatrix(newSize, B21, B11, temp2);
    strassen(newSize, A22, temp2, M4);

    addMatrix(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5);

    subMatrix(newSize, A21, A11, temp1);
    addMatrix(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6);

    subMatrix(newSize, A12, A22, temp1);
    addMatrix(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7);

    // Computing the final submatrices
    addMatrix(newSize, M1, M4, temp1);
    subMatrix(newSize, temp1, M5, temp2);
    addMatrix(newSize, temp2, M7, C11);

    addMatrix(newSize, M3, M5, C12);
    addMatrix(newSize, M2, M4, C21);

    addMatrix(newSize, M1, M3, temp1);
    subMatrix(newSize, temp1, M2, temp2);
    addMatrix(newSize, temp2, M6, C22);

    // Combining submatrices into final matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int size = 2; // Matrix size (must be a power of 2)
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2];

    printf("Matrix A:\n");
    printMatrix(size, A);
    printf("Matrix B:\n");
    printMatrix(size, B);

    strassen(size, A, B, C);

    printf("Resultant Matrix C (A * B):\n");
    printMatrix(size, C);

    return 0;
}
