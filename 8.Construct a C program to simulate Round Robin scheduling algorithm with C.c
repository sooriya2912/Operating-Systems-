#include <stdio.h>

struct Process {
    int pid;       
    int burstTime; 
    int remainingTime; 
    int waitTime;  
    int tat;       
};

void calculateWaitTime(struct Process proc[], int n, int quantum) {
    int currentTime = 0;
    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                done = 0;
                if (proc[i].remainingTime > quantum) {
                    currentTime += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].waitTime = currentTime - proc[i].burstTime;
                    proc[i].remainingTime = 0;
                }
            }
        }
    } while (!done);
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].burstTime + proc[i].waitTime;
    }
}

void printProcessInfo(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].waitTime, proc[i].tat);
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].waitTime = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    calculateWaitTime(proc, n, quantum);
    calculateTurnaroundTime(proc, n);

    printf("\nProcess execution details:\n");
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
