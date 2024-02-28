#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to calculate the need matrix
void calculateNeedMatrix(int allocation[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES]) {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int need[MAX_PROCESSES][MAX_RESOURCES];

    // Calculate the need matrix
    calculateNeedMatrix(allocation, max, need);

    // Print the need matrix
    printf("Need Matrix:\n");
    printMatrix(need, MAX_PROCESSES, MAX_RESOURCES);

    return 0;
}

