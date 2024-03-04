#include <stdio.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int executed;
};
void calculateWaitingTime(struct Process processes[], int n) {
    int currentTime = 0, completed = 0, minIndex, minBurst;
    while (completed != n) {
        minBurst = 9999; // Initialize to a large value
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].executed == 0) {
                if (processes[i].burst_time < minBurst) {
                    minBurst = processes[i].burst_time;
                    minIndex = i;
                }
            }
        }
        processes[minIndex].waiting_time = currentTime - processes[minIndex].arrival_time;
        currentTime += processes[minIndex].burst_time;
        processes[minIndex].turnaround_time = currentTime - processes[minIndex].arrival_time;
        processes[minIndex].executed = 1;
        completed++;
    }
}
void calculateAverageTime(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    calculateWaitingTime(processes, n);
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waiting_time;
        totalTurnaroundTime += processes[i].turnaround_time;
    }
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d:\n ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].executed = 0;
    }
    calculateAverageTime(processes, n);
    return 0;
}

