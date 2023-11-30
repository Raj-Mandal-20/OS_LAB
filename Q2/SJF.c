#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    while (completed != n) {
        int shortest = -1;
        int shortestBurst = 999999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].isCompleted == 0) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            currentTime++;
        } else {
            processes[shortest].completionTime = currentTime + processes[shortest].burstTime;
            processes[shortest].turnaroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
            processes[shortest].isCompleted = 1;
            completed++;
            currentTime = processes[shortest].completionTime;
        }
    }
}

void displayProcesses(struct Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].isCompleted = 0;
    }

    calculateTimes(processes, n);

    printf("\nSJF Scheduling:\n");
    displayProcesses(processes, n);

    return 0;
}
