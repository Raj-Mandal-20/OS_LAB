#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main() {
    int pipefd[2];
    pid_t pid;

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
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefd[1]); // Close original pipe write end

        execlp("ls", "ls", NULL); // Execute ls command
    } else { // Child process
        close(pipefd[1]); // Close writing end in child
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefd[0]); // Close original pipe read end

        execlp("sort", "sort", NULL); // Execute sort command
    }

    return 0;
}
