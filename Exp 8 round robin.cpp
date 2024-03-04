#include <stdio.h>
// Process structure
struct Process {
    int id;           // Process ID
    int burst_time;   // Burst time
    int remaining_time; // Remaining time
    int arrival_time; // Arrival time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time
    int wait_time; // Wait time
};
// Function to perform round robin scheduling
void roundRobin(struct Process processes[], int n, int quantum) {
    int i, completed = 0, time = 0;
    float total_turnaround_time = 0, total_wait_time = 0;
    printf("\nRound Robin Scheduling:\n");
    printf("Time\tProcess\n");
    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    printf("%d-%d\tP%d\n", time - processes[i].remaining_time, time, processes[i].id);
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    completed++;
                    // Calculate turnaround time and wait time
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].wait_time = processes[i].turnaround_time - processes[i].burst_time;
                    // Update total turnaround time and wait time
                    total_turnaround_time += processes[i].turnaround_time;
                    total_wait_time += processes[i].wait_time;
                } else {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                    printf("%d-%d\tP%d\n", time - quantum, time, processes[i].id);
                }
            }
        }
    }
    // Calculate and print average turnaround time and average wait time
    float avg_turnaround_time = total_turnaround_time / n;
    float avg_wait_time = total_wait_time / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Wait Time: %.2f\n", avg_wait_time);
}
int main() {
    int n, quantum, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    // Input burst time for each process
    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter the arrival time for process P%d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time for process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    roundRobin(processes, n, quantum);
    return 0;
}

