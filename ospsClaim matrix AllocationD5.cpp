#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 4
#define NUM_RESOURCES 3

// Function prototypes
bool isSafe(int processes[], int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES]);

int main() {
    // Given claim matrix
    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2}
    };

    // Given allocation matrix
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1}
    };

    // Available resources
    int available[NUM_RESOURCES] = {3, 3, 2};

    // List of processes
    int processes[NUM_PROCESSES] = {0, 1, 2, 3};

    // Check if system is in safe state
    if (isSafe(processes, available, max, allocation)) {
        printf("System is in a safe state\n");
    } else {
        printf("System is not in a safe state\n");
    }

    return 0;
}

bool isSafe(int processes[], int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES]) {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES];

    // Initialize work and finish array
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUM_PROCESSES; i++) {
        finish[i] = false;
    }

    // Check for safe state
    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }
    return true; // System is in a safe state
}

