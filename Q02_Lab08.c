#include <stdio.h>
#include <math.h>

int main() {
    const float EPSILON = 0.0001f;
    int r, c;

    printf("Enter rows and columns (max 5x5): ");
    scanf("%d %d", &r, &c);

    if (r < 1 || r > 5 || c < 1 || c > 5) {
        printf("Error: Dimensions must be between 1 and 5.\n");
        return 1;
    }

    float A[5][5];
    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%f", &A[i][j]);
        }
    }

    int isSquare = (r == c);
    int isRectangular = (r != c);
    int isZero = 1;
    int isDiagonal = isSquare;
    int isScalar = isSquare;
    int isIdentity = isSquare;
    int isUpperTri = isSquare;
    int isLowerTri = isSquare;
    int isSymmetric = isSquare;
    int isSkewSymmetric = isSquare;
    int isRow = (r == 1);
    int isCol = (c == 1);

    // 3. Zero / Null Matrix Check
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (fabsf(A[i][j]) > EPSILON) {
                isZero = 0;
            }
        }
    }
    // Square Matrix property checks
    if (isSquare) {
        float diagVal = A[0][0];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (i != j) {
                    if (fabsf(A[i][j]) > EPSILON) {
                        isDiagonal = 0;
                        isScalar = 0;
                        isIdentity = 0;
                    }
                } else {
                    if (fabsf(A[i][j] - diagVal) > EPSILON) isScalar = 0;
                    if (fabsf(A[i][j] - 1.0f) > EPSILON) isIdentity = 0;
                }

                // Triangular checks
                if (i > j && fabsf(A[i][j]) > EPSILON) isUpperTri = 0;
                if (i < j && fabsf(A[i][j]) > EPSILON) isLowerTri = 0;

                // Symmetry checks
                if (fabsf(A[i][j] - A[j][i]) > EPSILON) isSymmetric = 0;
                if (fabsf(A[i][j] + A[j][i]) > EPSILON || (i == j && fabsf(A[i][j]) > EPSILON)) isSkewSymmetric = 0;
            }
        }
        if (!isDiagonal) isScalar = 0;
    }
    // 11. Determinant (Singular / Non-Singular) using inline Gaussian Elimination
    float det = 1.0f;
    if (isSquare) {
        float temp_det[5][5];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                temp_det[i][j] = A[i][j];
            }
        }
        int sign = 1;
        for (int i = 0; i < r; i++) {
            int pivot = i;
            for (int j = i + 1; j < r; j++) {
                if (fabsf(temp_det[j][i]) > fabsf(temp_det[pivot][i])) {
                    pivot = j;
                }
            }
            if (pivot != i) {
                for (int k = 0; k < r; k++) {
                    float t = temp_det[i][k];
                    temp_det[i][k] = temp_det[pivot][k];
                    temp_det[pivot][k] = t;
                }
                sign = -sign;
            }
            if (fabsf(temp_det[i][i]) < EPSILON) {
                det = 0.0f;
                break;
            }
            for (int j = i + 1; j < r; j++) {
                float factor = temp_det[j][i] / temp_det[i][i];
                for (int k = i; k < r; k++) {
                    temp_det[j][k] -= factor * temp_det[i][k];
                }
            }
        }
        if (det != 0.0f) {
            for (int i = 0; i < r; i++) {
                det *= temp_det[i][i];
            }
            det *= sign;
        }
    }
    // 16 & 17. Idempotent and Nilpotent Matrix Checks
    int isIdempotent = 0;
    int isNilpotent = 0;
    if (isSquare) {
        float A2[5][5];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                A2[i][j] = 0.0f;
                for (int k = 0; k < r; k++) {
                    A2[i][j] += A[i][k] * A[k][j];
                }
            }
        }
        int idem = 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                if (fabsf(A2[i][j] - A[i][j]) > EPSILON) idem = 0;
            }
        }
        isIdempotent = idem;

        float An[5][5];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                An[i][j] = A[i][j];
            }
        }
        for (int p = 2; p <= r + 1; p++) {
            float temp[5][5];
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    temp[i][j] = 0.0f;
                    for (int k = 0; k < r; k++) {
                        temp[i][j] += An[i][k] * A[k][j];
                    }
                }
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    An[i][j] = temp[i][j];
                }
            }
            int zeroMat = 1;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    if (fabsf(An[i][j]) > EPSILON) zeroMat = 0;
                }
            }
            if (zeroMat) {
                isNilpotent = 1;
                break;
            }
        }
    }
    // 12. Equal Matrix Check (Optional)
    int isEqual = 0;
    char checkEqual;
    printf("\nDo you want to compare with a second matrix for Equality? (y/n): ");
    scanf(" %c", &checkEqual);

    if (checkEqual == 'y' || checkEqual == 'Y') {
        float B[5][5];
        printf("Enter elements of Matrix B:\n");
        isEqual = 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                printf("B[%d][%d]: ", i, j);
                scanf("%f", &B[i][j]);
                if (fabsf(A[i][j] - B[i][j]) > EPSILON) isEqual = 0;
            }
        }
    }

    // Display Results
    printf("\n========================================\n");
    printf("         MATRIX CLASSIFICATION          \n");
    printf("========================================\n");
    
    if (isSquare) printf("- Square Matrix\n");
    if (isRectangular) printf("- Rectangular Matrix\n");
    if (isZero) {
        printf("- Zero Matrix\n");
        printf("- Null Matrix\n");
    }
    if (isIdentity) printf("- Identity Matrix\n");
    if (isDiagonal) printf("- Diagonal Matrix\n");
    if (isScalar) printf("- Scalar Matrix\n");
    if (isUpperTri) printf("- Upper Triangular Matrix\n");
    if (isLowerTri) printf("- Lower Triangular Matrix\n");
    if (isSymmetric) printf("- Symmetric Matrix\n");
    if (isSkewSymmetric) printf("- Skew-Symmetric Matrix\n");
    if (isSquare) {
        if (fabsf(det) < EPSILON) printf("- Singular Matrix (Determinant = 0)\n");
        else printf("- Non-Singular Matrix (Determinant = %.2f)\n", det);
    }

    if (checkEqual == 'y' || checkEqual == 'Y') {
        if (isEqual) printf("- Equal Matrix (Matches Matrix B)\n");
        else printf("- Not Equal to Matrix B\n");
    }

    if (isRow) printf("- Row Matrix\n");
    if (isCol) printf("- Column Matrix\n");
    if (isIdempotent) printf("- Idempotent Matrix\n");
    if (isNilpotent) printf("- Nilpotent Matrix\n");
    
    printf("========================================\n");

    return 0;
}