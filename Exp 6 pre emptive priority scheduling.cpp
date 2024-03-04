#include<stdio.h>
#include<stdlib.h>
// Process structure
typedef struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;
// Function to find the process with highest priority
int findHighestPriority(Process processes[], int n, int current_time) {
    int highest_priority = -1;
    int selected_process = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
            if (highest_priority == -1 || processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                selected_process = i;
            }
        }
    }
    return selected_process;
}
// Function to perform preemptive priority scheduling
void preemptivePriorityScheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int selected_process;
    printf("\nPreemptive Priority Scheduling\n");
    printf("Process Execution Order:\n");
    while (completed < n) {
        selected_process = findHighestPriority(processes, n, current_time);
        if (selected_process == -1) {
            printf("Idle (%d - %d)\n", current_time, current_time + 1);
            current_time++;
        } else {
            printf("P%d (%d - %d)\n", processes[selected_process].process_id, current_time, current_time + 1);
            processes[selected_process].remaining_time--;
            if (processes[selected_process].remaining_time == 0) {
                completed++;
            }
            current_time++;
        }
    }
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process *processes = (Process *)malloc(n * sizeof(Process));
    printf("Enter process details (process_id, arrival_time, burst_time, priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d", &processes[i].process_id, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
    preemptivePriorityScheduling(processes, n);
    free(processes);
    return 0;
}
