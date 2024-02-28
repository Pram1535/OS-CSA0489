#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;          // Process ID
    int burstTime;   // Burst time
    int arrivalTime; // Arrival time
    int waitingTime; // Waiting time
    int turnaroundTime; // Turnaround time
} Process;

// Function to compute average waiting time and average turnaround time
void computeAverages(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            processes[i].waitingTime = 0;
        } else {
            processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        }
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    Process processes[] = {
        {0, 2, 0, 0, 0}, // Process ID, Burst Time, Arrival Time, Waiting Time, Turnaround Time
        {1, 4, 0, 0, 0},
        {2, 8, 0, 0, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    computeAverages(processes, n);

    return 0;
}

