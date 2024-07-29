#include <stdio.h>

struct Process {
    int pid;       
    int burstTime; 
    int waitTime;  
    int tat;       
};

void calculateWaitTime(struct Process proc[], int n) {
    proc[0].waitTime = 0; 
    for (int i = 1; i < n; i++) {
        proc[i].waitTime = proc[i-1].waitTime + proc[i-1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].burstTime + proc[i].waitTime;
    }
}

void sortProcessesByBurstTime(struct Process proc[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (proc[j].burstTime > proc[j+1].burstTime) {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void printProcessInfo(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitTime, proc[i].tat);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i+1;
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burstTime);
    }

    sortProcessesByBurstTime(proc, n);
    calculateWaitTime(proc, n);
    calculateTurnaroundTime(proc, n);

    printf("\nProcess execution order (by shortest burst time):\n");
    printProcessInfo(proc, n);

    float totalWaitTime = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWaitTime += proc[i].waitTime;
        totalTAT += proc[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWaitTime / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
