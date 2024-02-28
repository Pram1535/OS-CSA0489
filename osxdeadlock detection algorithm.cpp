#include <stdio.h>

#define PROCESSES 3
#define RESOURCES 3

// Function to check if the system is in a deadlock state
int isDeadlock(int allocation[PROCESSES][RESOURCES], int max[PROCESSES][RESOURCES], int available[RESOURCES]) {
    int need[PROCESSES][RESOURCES];

    // Calculate the Need Matrix
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int finish[PROCESSES] = {0}; // Initialize all processes as unfinished

    int work[RESOURCES];
    for (int i = 0; i < RESOURCES; ++i) {
        work[i] = available[i];
    }

    int safeSequence[PROCESSES];
    int count = 0;

    while (count < PROCESSES) {
        int found = 0;
        for (int p = 0; p < PROCESSES; ++p) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < RESOURCES; ++j) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == RESOURCES) {
                    for (int k = 0; k < RESOURCES; ++k)
                        work[k] += allocation[p][k];
                    safeSequence[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break; // If no process found, the system is in deadlock
    }

    if (count < PROCESSES) {
        printf("System is in deadlock.\n");
        printf("Deadlocked processes: ");
        for (int i = 0; i < PROCESSES; ++i) {
            if (!finish[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
        return 1; // Deadlock detected
    } else {
        printf("System is not in deadlock.\n");
        return 0; // No deadlock
    }
}

int main() {
    int maxMatrix[PROCESSES][RESOURCES] = {{3, 6, 8}, {4, 3, 3}, {3, 4, 4}};
    int allocationMatrix[PROCESSES][RESOURCES] = {{3, 3, 3}, {2, 0, 3}, {1, 2, 4}};
    int available[RESOURCES] = {1, 2, 0};

    isDeadlock(allocationMatrix, maxMatrix, available);

    return 0;
}

