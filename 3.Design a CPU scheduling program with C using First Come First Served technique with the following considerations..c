#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid; // Process ID
    int burst_time; // Burst time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
} Process;

void calculateWaitingTime(Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void printProcesses(Process processes[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        processes[i].pid = i+1;
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    printProcesses(processes, n);

    free(processes);

    return 0;
}
