#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid; // Process ID
    int burst_time; // Burst time
    int remaining_time; // Remaining burst time
    int priority; // Priority
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
    int arrival_time; // Arrival time
} Process;

void calculateWaitingTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));
    int *is_completed = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        is_completed[i] = 0;
    }

    int completed = 0, current_time = 0, min_priority, shortest, finish_time;
    while (completed != n) {
        shortest = -1;
        min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i] &&
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].remaining_time--;
        current_time++;

        if (processes[shortest].remaining_time == 0) {
            finish_time = current_time;
            processes[shortest].turnaround_time = finish_time;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time;
            is_completed[shortest] = 1;
            completed++;
        }
    }

    calculateTurnaroundTime(processes, n);

    printf("\nPID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }

    free(processes);
    free(is_completed);

    return 0;
}
