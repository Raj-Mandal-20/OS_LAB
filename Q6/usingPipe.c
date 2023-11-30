#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close reading end in parent

        char message[] = "Hello, child! This is a message from the parent.";
        write(pipefd[1], message, strlen(message) + 1); // Write message to pipe

        close(pipefd[1]); // Close writing end in parent
    } else { // Child process
        close(pipefd[1]); // Close writing end in child

        read(pipefd[0], buffer, BUFFER_SIZE); // Read message from pipe
        printf("Child received: %s\n", buffer);

        close(pipefd[0]); // Close reading end in child
    }

    return 0;
}
