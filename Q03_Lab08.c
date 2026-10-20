#include <stdio.h>

int main() {
    int r1, c1, r2, c2;

    printf("========================================\n");
    printf("        MATRIX MULTIPLICATION PROGRAM   \n");
    printf("========================================\n");
    
    printf("Enter rows and columns for Matrix A (max 3x3): ");
    scanf("%d %d", &r1, &c1);
    
    printf("Enter rows and columns for Matrix B (max 3x3): ");
    scanf("%d %d", &r2, &c2);

    // Validate size boundaries
    if (r1 < 1 || r1 > 3 || c1 < 1 || c1 > 3 || r2 < 1 || r2 > 3 || c2 < 1 || c2 > 3) {
        printf("Error: Matrix dimensions must be between 1 and 3.\n");
        return 1;
    }

    // Validate multiplication condition: 
    if (c1 != r2) {
        printf("\nError: Multiplication not possible!\n");
        printf("Columns of Matrix A (%d) must match rows of Matrix B (%d).\n", c1, r2);
        return 1;
    }

    float A[3][3], B[3][3], result[3][3] = {0};

    // Input Matrix A
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%f", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%f", &B[i][j]);
        }
    }

    // Matrix Multiplication 
    for (int i = 0; i < r1; i++) {         
        for (int j = 0; j < c2; j++) {     
            for (int k = 0; k < c1; k++) { 
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Display Matrix A
    printf("\n----------------------------------------\n");
    printf("Matrix A (%dx%d):\n", r1, c1);
    for (int i = 0; i < r1; i++) {
        printf("| ");
        for (int j = 0; j < c1; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("|\n");
    }

    // Display Matrix B
    printf("\n----------------------------------------\n");
    printf("Matrix B (%dx%d):\n", r2, c2);
    for (int i = 0; i < r2; i++) {
        printf("| ");
        for (int j = 0; j < c2; j++) {
            printf("%8.2f ", B[i][j]);
        }
        printf("|\n");
    }

    // Display Resultant Matrix
    printf("\n----------------------------------------\n");
    printf("Resultant Matrix (A x B) (%dx%d):\n", r1, c2);
    for (int i = 0; i < r1; i++) {
        printf("| ");
        for (int j = 0; j < c2; j++) {
            printf("%8.2f ", result[i][j]);
        }
        printf("|\n");
    }
    printf("========================================\n");

    return 0;
}