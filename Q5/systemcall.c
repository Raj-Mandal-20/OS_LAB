#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        execlp("ls", "ls", NULL);
    } else {
        // Parent process
        wait(NULL);
        printf("Child process finished\n");
    }

    return 0;
}
