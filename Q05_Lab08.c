#include <stdio.h>
#include <math.h>

int main() {
    float arr[3][3][3];
    const float EPSILON = 0.0001f; // Tolerance for floating-point comparisons

    printf("========================================\n");
    printf("    3x3x3 LAYER SIMILARITY ANALYSIS     \n");
    printf("========================================\n");
    printf("Enter elements for the 3x3x3 3D array (3 layers, each 3x3):\n");

    // Input traversal using 3 nested loops
    for (int k = 0; k < 3; k++) {
        printf("\n--- Enter Data for Layer %d ---\n", k + 1);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("Element [%d][%d][%d]: ", k, i, j);
                scanf("%f", &arr[k][i][j]);
            }
        }
    }

    // Display all three layer matrices clearly
    printf("\n========================================\n");
    printf("          LAYER MATRICES SUMMARY        \n");
    printf("========================================\n");
    for (int k = 0; k < 3; k++) {
        printf("\nLayer %d Matrix:\n", k + 1);
        for (int i = 0; i < 3; i++) {
            printf("| ");
            for (int j = 0; j < 3; j++) {
                printf("%8.2f ", arr[k][i][j]);
            }
            printf("|\n");
        }
    }

    // Pairwise Layer Similarity Examination
    // Pairs: (Layer 1 & 2), (Layer 1 & 3), (Layer 2 & 3)
    printf("\n========================================\n");
    printf("        PAIRWISE LAYER SIMILARITY       \n");
    printf("========================================\n");

    int pairs[3][2] = {
        {0, 1}, // Layer 1 vs Layer 2
        {0, 2}, // Layer 1 vs Layer 3
        {1, 2}  // Layer 2 vs Layer 3
    };

    for (int p = 0; p < 3; p++) {
        int l1 = pairs[p][0];
        int l2 = pairs[p][1];
        int identical = 1;
        int diffCount = 0;

        // Compare corresponding elements using nested loops
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (fabsf(arr[l1][i][j] - arr[l2][i][j]) > EPSILON) {
                    identical = 0;
                    diffCount++;
                }
            }
        }

        printf("\nComparison: Layer %d vs Layer %d\n", l1 + 1, l2 + 1);
        if (identical) {
            printf("  -> Status: IDENTICAL (All 9 elements match)\n");
        } else {
            printf("  -> Status: DISTINCT (%d element(s) differ)\n", diffCount);
        }
    }

    // Global Similarity Insight across all 3 layers
    int allIdentical = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (fabsf(arr[0][i][j] - arr[1][i][j]) > EPSILON || fabsf(arr[0][i][j] - arr[2][i][j]) > EPSILON) {
                allIdentical = 0;
            }
        }
    }

    printf("\n----------------------------------------\n");
    if (allIdentical) {
        printf("Global Insight: All three layers are completely identical across the 3D structure.\n");
    } else {
        printf("Global Insight: Layers contain variations and structural differences across the 3D space.\n");
    }
    printf("========================================\n");

    return 0;
}