#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESS 10
#define MAX_RESOURCE 10

int allocation[MAX_PROCESS][MAX_RESOURCE];
int max[MAX_PROCESS][MAX_RESOURCE];
int need[MAX_PROCESS][MAX_RESOURCE];
int available[MAX_RESOURCE];
bool finished[MAX_PROCESS];

int num_processes, num_resources;

// Function to check if the requested resources can be allocated
bool isSafe(int process, int request[]) {
    int i;
    for (i = 0; i < num_resources; i++) {
        if (request[i] > need[process][i] || request[i] > available[i])
            return false;
    }
    return true;
}

// Function to allocate resources to a process
void allocateResources(int process, int request[]) {
    int i;
    for (i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
}

// Function to release resources from a process
void releaseResources(int process, int request[]) {
    int i;
    for (i = 0; i < num_resources; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }
}

// Banker's Algorithm for deadlock avoidance
void bankersAlgorithm() {
    int i, j;

    for (i = 0; i < num_processes; i++)
        finished[i] = false;

    int work[num_resources];
    for (i = 0; i < num_resources; i++)
        work[i] = available[i];

    int count = 0;
    while (count < num_processes) {
        bool found = false;

        for (i = 0; i < num_processes; i++) {
            if (!finished[i] && isSafe(i, need[i])) {
                printf("Process %d executed\n", i);
                allocateResources(i, allocation[i]);
                finished[i] = true;
                count++;
                found = true;
            }
        }

        if (!found) {
            printf("System is not in safe state\n");
            return;
        }
    }

    printf("System is in safe state\n");
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    bankersAlgorithm();

    return 0;
}
