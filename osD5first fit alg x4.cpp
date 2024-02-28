#include <stdio.h>
#define NUM_PARTITIONS 6
#define NUM_PROCESSES 5

void firstFit(int partitions[], int processes[], int num_partitions, int num_processes) {
    int allocation[num_processes];
    for (int i = 0; i < num_processes; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_partitions; j++) {
            if (partitions[j] >= processes[i]) {
                allocation[i] = j;
                partitions[j] -= processes[i];
                break;
            }
        }
    }
    printf("Process No.\tProcess Size\tPartition No.\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t\t%d KB\t\t", i+1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]+1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int partitions[NUM_PARTITIONS] = {300, 600, 350, 200, 750, 125}; 
    int processes[NUM_PROCESSES] = {115, 500, 358, 200, 375}; 

    printf("First-Fit Allocation:\n");
    firstFit(partitions, processes, NUM_PARTITIONS, NUM_PROCESSES);

    return 0;
}

