#include <stdio.h>

#define MAX_PROCESS 10

typedef struct {
    int burst_time;
    int remaining_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;
void roundRobin(Process processes[], int n, int quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int quantum_timer = quantum;

    while (remaining_processes > 0) {
        int flag = 0;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                flag = 1;

                if (processes[i].remaining_time > quantum) {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].waiting_time = current_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                    processes[i].turnaround_time = current_time;
                }
            }
        }

        if (flag == 0)
            break;
    }
}

int main() {
    Process processes[MAX_PROCESS];
    int n = 3; 
    int quantum = 4; 
    processes[0].burst_time = 24;
    processes[1].burst_time = 3;
    processes[2].burst_time = 3;
    for (int i = 0; i < n; i++) {
        processes[i].arrival_time = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }
    roundRobin(processes, n, quantum);
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Display results
    printf("Average Waiting Time: %.2f ms\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f ms\n", avg_turnaround_time);

    return 0;
}
