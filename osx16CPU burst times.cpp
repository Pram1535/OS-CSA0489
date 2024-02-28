#include <stdio.h>

// Structure to represent a process
typedef struct {
    char id;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to calculate average waiting time and average turnaround time
void computeAverages(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Calculate waiting time and turnaround time for each process
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    totalWaitingTime = 0;
    totalTurnaroundTime = processes[0].burstTime;
    for (int i = 1; i < n; ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Compute and print average waiting time and average turnaround time
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    Process processes[] = {
        {'P1', 10, 0, 0, 0},
        {'P2', 15, 0, 0, 0},
        {'P3', 25, 0, 0, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    computeAverages(processes, n);

    return 0;
}

