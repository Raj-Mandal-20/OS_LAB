#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg) {
    printf("New Thread: Thread ID: %lu, Process ID: %d\n", pthread_self(), getpid());
    return NULL;
}

int main() {
    pthread_t newThread;

    // Creating a new thread
    if (pthread_create(&newThread, NULL, threadFunction, NULL) != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }

    printf("Main Thread: Thread ID: %lu, Process ID: %d\n", pthread_self(), getpid());

    // Wait for the newly created thread to finish
    pthread_join(newThread, NULL);

    return 0;
}
