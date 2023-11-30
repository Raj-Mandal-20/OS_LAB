#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t semaphore;

void *countCharacters(void *arg) {
    char *str = (char *)arg;
    int length = strlen(str);
    printf("String length calculated by the thread: %d\n", length);
    sem_post(&semaphore);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    char input[100];

    sem_init(&semaphore, 0, 0);

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    pthread_create(&thread, NULL, countCharacters, input);

    sem_wait(&semaphore);
    printf("String entered by the main thread: %s", input);

    pthread_join(thread, NULL);
    sem_destroy(&semaphore);

    return 0;
}
