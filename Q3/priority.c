#include<stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int priority[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n];

    findWaitingTime(processes, n, bt, wt, priority);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], priority[i], wt[i], tat[i]);
    }

    printf("Average waiting time: %.2f\n", (float)total_wt / (float)n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / (float)n);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {6, 8, 4};
    int priority[] = {2, 1, 3};

    findAvgTime(processes, n, burst_time, priority);

    return 0;
}
