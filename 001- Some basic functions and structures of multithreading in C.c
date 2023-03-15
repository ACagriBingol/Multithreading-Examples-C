#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Create a mutex variable to prevent race conditions
pthread_mutex_t mutex;

// Create a conditional variable to signal when a task is complete
pthread_cond_t task_complete;

// Create a barrier to ensure all tasks start at the same time
pthread_barrier_t start_barrier;

// Define the number of threads to create
#define NUM_THREADS 3

// Define the number of iterations for each thread to complete
#define ITERATIONS 10

// Define a global variable to track the number of completed tasks
int completed_tasks = 0;

// Define a function to perform the first task
void* task1(void* arg) {
    // Wait for all threads to start
    pthread_barrier_wait(&start_barrier);

    // Perform the task
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Task 1, iteration %d\n", i);
    }

    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    // Increment the number of completed tasks
    completed_tasks++;

    // Signal that the task is complete
    pthread_cond_signal(&task_complete);

    // Release the mutex lock
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Define a function to perform the second task
void* task2(void* arg) {
    // Wait for all threads to start
    pthread_barrier_wait(&start_barrier);

    // Perform the task
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Task 2, iteration %d\n", i);
    }

    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    // Increment the number of completed tasks
    completed_tasks++;

    // Signal that the task is complete
    pthread_cond_signal(&task_complete);

    // Release the mutex lock
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Define a function to perform the third task
void* task3(void* arg) {
    // Wait for all threads to start
    pthread_barrier_wait(&start_barrier);

    // Perform the task
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Task 3, iteration %d\n", i);
    }

    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    // Increment the number of completed tasks
    completed_tasks++;

    // Signal that the task is complete
    pthread_cond_signal(&task_complete);

    // Release the mutex lock
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    // Initialize the mutex and conditional variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&task_complete, NULL);

    // Initialize the barrier with the number of threads
    pthread_barrier_init(&start_barrier, NULL, NUM_THREADS);

    // Create an array of threads
    pthread_t threads[NUM_THREADS];

    // Create the threads
    pthread_create(&threads[0], NULL, task1, NULL);
    pthread_create(&threads[1], NULL, task2, NULL);
    pthread_create(&threads[2], NULL, task3, NULL);

    // Wait for all tasks to complete
    pthread_mutex_lock(&mutex);
    while (completed_tasks < NUM_THREADS) {
        pthread_cond_wait(&task_complete, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    // Join the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex and conditional variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&task_complete);

    // Destroy the barrier
    pthread_barrier_destroy(&start_barrier);

    return 0;

}
        