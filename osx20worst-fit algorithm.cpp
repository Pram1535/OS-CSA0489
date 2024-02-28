#include <stdio.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 5

// Function to allocate memory using worst-fit algorithm
void worstFit(int partitions[MAX_PARTITIONS], int processes[MAX_PROCESSES], int allocation[MAX_PROCESSES]) {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        int worstFitIdx = -1;
        for (int j = 0; j < MAX_PARTITIONS; ++j) {
            if (partitions[j] >= processes[i]) {
                if (worstFitIdx == -1 || partitions[j] > partitions[worstFitIdx]) {
                    worstFitIdx = j;
                }
            }
        }
        if (worstFitIdx != -1) {
            allocation[i] = partitions[worstFitIdx];
            partitions[worstFitIdx] -= processes[i];
        } else {
            allocation[i] = -1; // Couldn't allocate
        }
    }
}

int main() {
    int partitions[MAX_PARTITIONS] = {300, 600, 350, 200, 750, 125};
    int processes[MAX_PROCESSES] = {115, 500, 358, 200, 375};
    int allocation[MAX_PROCESSES];

    worstFit(partitions, processes, allocation);

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

