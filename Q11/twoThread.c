#include <stdio.h>
#include <pthread.h>

// Structure to pass multiple parameters to the thread
struct ThreadArgs {
    int number;
    int result;
};

// Function to calculate factorial
void *calculateFactorial(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int num = args->number;
    int factorial = 1;

    for (int i = 2; i <= num; i++) {
        factorial *= i;
    }

    args->result = factorial;
    pthread_exit(NULL);
}

// Function to reverse a number
void *reverseNumber(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int num = args->number;
    int reverse = 0;

    while (num != 0) {
        reverse = reverse * 10 + num % 10;
        num /= 10;
    }

    args->result = reverse;
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_factorial, thread_reverse;
    struct ThreadArgs args_factorial, args_reverse;

    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    args_factorial.number = number;
    args_reverse.number = number;

    // Create threads for factorial and reverse calculations
    pthread_create(&thread_factorial, NULL, calculateFactorial, (void *)&args_factorial);
    pthread_create(&thread_reverse, NULL, reverseNumber, (void *)&args_reverse);

    // Wait for both threads to complete
    pthread_join(thread_factorial, NULL);
    pthread_join(thread_reverse, NULL);

    printf("Factorial of %d is: %d\n", number, args_factorial.result);
    printf("Reverse of %d is: %d\n", number, args_reverse.result);

    return 0;
}
