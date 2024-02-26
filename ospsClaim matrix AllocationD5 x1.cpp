#include <stdio.h>
#define PROCESSES 4
#define RESOURCES 3
int isSafe(int available[], int max[][RESOURCES], int alloc[][RESOURCES]) {
    int need[PROCESSES][RESOURCES];
    int finish[PROCESSES] = {0};
    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    int work[RESOURCES];
    for (int i = 0; i < RESOURCES; i++) {
        work[i] = available[i];
    }
    int count = 0;
    while (count < PROCESSES) {
        int found = 0;
        for (int i = 0; i < PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == RESOURCES) {
                    for (int k = 0; k < RESOURCES; k++) {
                        work[k] += alloc[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    return count == PROCESSES;
}

int main() {
    int claim[PROCESSES][RESOURCES] = {
        {3, 2, 2},
        {6, 1, 3},
        {3, 1, 4},
        {4, 2, 2}
    };
    int allocation[PROCESSES][RESOURCES] = {
        {1, 0, 0},
        {6, 1, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int available[RESOURCES] = {3, 2, 2};

    if (isSafe(available, claim, allocation)) {
        printf("System is in safe state\n");
    } else {
        printf("System is not in safe state\n");
    }

    return 0;
}

