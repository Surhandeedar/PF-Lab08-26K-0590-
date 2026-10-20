#include <stdio.h>

int main() {
    float arr[3][3][3];

    printf("========================================\n");
    printf("     3x3x3 3D ARRAY ANALYSIS PROGRAM    \n");
    printf("========================================\n");
    printf("Enter elements for the 3x3x3 3D array (3 layers, each 3x3):\n");

    // Input traversal using 3 nested loops (Layer -> Row -> Column)
    for (int k = 0; k < 3; k++) {
        printf("\n--- Enter Data for Layer %d ---\n", k + 1);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("Element [%d][%d][%d]: ", k, i, j);
                scanf("%f", &arr[k][i][j]);
            }
        }
    }

    // Overall metrics initialization
    float grandTotal = 0;
    float globalMax, globalMin;
    int firstElement = 1;

    printf("\n========================================\n");
    printf("        LAYER-WISE ANALYTICAL RESULTS   \n");
    printf("========================================\n");

    // Analysis traversal using 3 nested loops
    for (int k = 0; k < 3; k++) {
        float layerSum = 0;
        float layerMax = arr[k][0][0];
        float layerMin = arr[k][0][0];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float val = arr[k][i][j];
                
                // Accumulate totals and track extremes
                layerSum += val;
                grandTotal += val;

                if (val > layerMax) layerMax = val;
                if (val < layerMin) layerMin = val;

                // Track global max/min across all layers
                if (firstElement) {
                    globalMax = val;
                    globalMin = val;
                    firstElement = 0;
                } else {
                    if (val > globalMax) globalMax = val;
                    if (val < globalMin) globalMin = val;
                }
            }
        }

        float layerAvg = layerSum / 9.0f; // Each layer has 9 elements (3x3)

        // Display individual layer grid
        printf("\nLayer %d Matrix:\n", k + 1);
        for (int i = 0; i < 3; i++) {
            printf("| ");
            for (int j = 0; j < 3; j++) {
                printf("%8.2f ", arr[k][i][j]);
            }
            printf("|\n");
        }
        
        // Display Layer Statistics
        printf("----------------------------------------\n");
        printf("Layer %d Statistics:\n", k + 1);
        printf("  - Layer Total Sum : %.2f\n", layerSum);
        printf("  - Layer Average   : %.2f\n", layerAvg);
        printf("  - Layer Maximum   : %.2f\n", layerMax);
        printf("  - Layer Minimum   : %.2f\n", layerMin);
        printf("----------------------------------------\n");
    }

    // Compute overall statistics across all 27 elements (3 x 3 x 3)
    float overallAvg = grandTotal / 27.0f;

    // Display Overall Data Insights
    printf("\n========================================\n");
    printf("        OVERALL DATA INSIGHTS           \n");
    printf("========================================\n");
    printf("  - Grand Total Sum (All Layers) : %.2f\n", grandTotal);
    printf("  - Overall Average              : %.2f\n", overallAvg);
    printf("  - Global Maximum Value         : %.2f\n", globalMax);
    printf("  - Global Minimum Value         : %.2f\n", globalMin);
    printf("========================================\n");

    return 0;
}