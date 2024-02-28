#include <stdio.h>

#define MAX_PROCESSES 3

// Structure to represent a process
typedef struct {
    char id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to compute average waiting time and average turnaround time
void computeAverages(Process processes[], int n, int quantum) {
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    while (1) {
        int allFinished = 1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].remainingTime > 0) {
                allFinished = 0;
                if (processes[i].remainingTime > quantum) {
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].waitingTime = currentTime - processes[i].burstTime - processes[i].arrivalTime;
                    processes[i].remainingTime = 0;
                }
                totalTurnaroundTime += currentTime - processes[i].arrivalTime;
            }
        }
        if (allFinished == 1)
            break;
    }

    // Compute and print average waiting time and average turnaround time
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {'P1', 24, 24, 0, 0, 0},
        {'P2', 3, 3, 0, 0, 0},
        {'P3', 3, 3, 0, 0, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 4;

    computeAverages(processes, n, quantum);

    return 0;
}

