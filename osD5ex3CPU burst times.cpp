#include <stdio.h>
struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
void sjf(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].turnaround_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAvgTimes(struct Process processes[], int n, float *avg_waiting_time, float *avg_turnaround_time) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    *avg_waiting_time = (float)total_waiting_time / n;
    *avg_turnaround_time = (float)total_turnaround_time / n;
}

int main() {
    struct Process processes[] = {
        {1, 6, 0, 0},
        {2, 8, 0, 0},
        {3, 7, 0, 0},
        {4, 3, 0, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    sjf(processes, n);
    float avg_waiting_time, avg_turnaround_time;
    calculateAvgTimes(processes, n, &avg_waiting_time, &avg_turnaround_time);

    // Output results
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

