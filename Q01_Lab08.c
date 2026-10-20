#include <stdio.h>

int main() {
    float mat[3][3];
    float trans[3][3];
    float cof[3][3];
    float adj[3][3];
    float inv[3][3];
    float det = 0;

    printf("========================================\n");
    printf("     3x3 MATRIX ANALYSIS PROGRAM        \n");
    printf("========================================\n");
    printf("Enter the elements of the 3x3 matrix:\n");
    
    // Input matrix elements using nested loops
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%f", &mat[i][j]);
        }
    }

    // Display Original Matrix
    printf("\n----------------------------------------\n");
    printf("Original Matrix (A):\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%8.2f ", mat[i][j]);
        }
        printf("|\n");
    }

    // 1. Transpose Matrix (A^T) using nested loops
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            trans[i][j] = mat[j][i];
        }
    }
    printf("\n----------------------------------------\n");
    printf("1. Transpose Matrix (A^T):\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%8.2f ", trans[i][j]);
        }
        printf("|\n");
    }

    // 3. Cofactor Matrix (computed first to easily derive determinant and adjoint)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Extract 2x2 submatrix using nested loops
            float sub[2][2];
            int r = 0, c = 0;
            for (int row = 0; row < 3; row++) {
                if (row == i) continue;
                c = 0;
                for (int col = 0; col < 3; col++) {
                    if (col == j) continue;
                    sub[r][c] = mat[row][col];
                    c++;
                }
                r++;
            }
            // Determinant of 2x2 submatrix
            float det2 = (sub[0][0] * sub[1][1]) - (sub[0][1] * sub[1][0]);
            
            // Apply checkerboard sign pattern (-1)^(i+j)
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            cof[i][j] = sign * det2;
        }
    }

    // 2. Determinant of 3x3 Matrix (Laplace expansion along the first row)
    for (int j = 0; j < 3; j++) {
        det += mat[0][j] * cof[0][j];
    }
    printf("\n----------------------------------------\n");
    printf("2. Determinant (det(A)):\n");
    printf("Determinant = %.4f\n", det);

    // Display Cofactor Matrix
    printf("\n----------------------------------------\n");
    printf("3. Cofactor Matrix (C):\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%8.2f ", cof[i][j]);
        }
        printf("|\n");
    }

    // 4. Adjoint Matrix (Transpose of the Cofactor Matrix) using nested loops
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj[i][j] = cof[j][i];
        }
    }
    printf("\n----------------------------------------\n");
    printf("4. Adjoint Matrix (Adj(A)):\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%8.2f ", adj[i][j]);
        }
        printf("|\n");
    }

    // 5. Inverse Matrix (Adj(A) / det(A))
    printf("\n----------------------------------------\n");
    printf("5. Inverse Matrix (A^-1):\n");
    if (det == 0) {
        printf("Error: Matrix is singular (determinant is 0). Inverse does not exist.\n");
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                inv[i][j] = adj[i][j] / det;
            }
        }
        for (int i = 0; i < 3; i++) {
            printf("| ");
            for (int j = 0; j < 3; j++) {
                printf("%8.2f ", inv[i][j]);
            }
            printf("|\n");
        }
    }
    printf("========================================\n");

    return 0;
}