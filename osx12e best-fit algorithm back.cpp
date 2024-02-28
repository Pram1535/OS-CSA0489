#include <stdio.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 5

void bestFit(int partitions[MAX_PARTITIONS], int processes[MAX_PROCESSES], int allocation[MAX_PROCESSES]) {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        int bestFitIdx = -1;
        for (int j = 0; j < MAX_PARTITIONS; ++j) {
            if (partitions[j] >= processes[i]) {
                if (bestFitIdx == -1 || partitions[j] < partitions[bestFitIdx]) {
                    bestFitIdx = j;
                }
            }
        }
        if (bestFitIdx != -1) {
            allocation[i] = partitions[bestFitIdx];
            partitions[bestFitIdx] -= processes[i];
        } else {
            allocation[i] = -1; // Couldn't allocate
        }
    }
}

int main() {
    int partitions[MAX_PARTITIONS] = {300, 600, 350, 200, 750, 125};
    int processes[MAX_PROCESSES] = {115, 500, 358, 200, 375};
    int allocation[MAX_PROCESSES];

    bestFit(partitions, processes, allocation);

    printf("Memory Allocation:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (allocation[i] != -1) {
            printf("Process %d (Size: %d KB) -> Allocated %d KB\n", i+1, processes[i], allocation[i]);
        } else {
            printf("Process %d (Size: %d KB) -> Not Allocated (No suitable partition)\n", i+1, processes[i]);
        }
    }

    return 0;
}

