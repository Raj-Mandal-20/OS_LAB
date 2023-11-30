#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5

sem_t mutex, wrt;
int data = 0, readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&wrt); // First reader acquires write lock
        }
        sem_post(&mutex);

        // Reading data by the reader
        printf("Reader %d reads data: %d\n", reader_id, data);
        sleep(1); // Simulating reading time

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&wrt); // Last reader releases write lock
        }
        sem_post(&mutex);

        sleep(2); // Rest period between reads
    }
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&wrt);

        // Writing data by the writer
        data++;
        printf("Writer %d writes data: %d\n", writer_id, data);
        sleep(2); // Simulating writing time

        sem_post(&wrt);

        sleep(4); // Rest period between writes
    }
    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writer_thread;
    int reader_ids[MAX_READERS], writer_id = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < MAX_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer thread
    pthread_create(&writer_thread, NULL, writer, &writer_id);

    // Join threads
    for (int i = 0; i < MAX_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
