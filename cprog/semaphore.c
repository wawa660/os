#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

// Shared buffer and variables
int buffer[BUFFER_SIZE];
int in = 0;    // Index for producer
int out = 0;   // Index for consumer
int produced = 0;
int consumed = 0;

// Semaphores and mutex
sem_t empty;    // Counts empty buffer slots
sem_t full;     // Counts filled buffer slots
pthread_mutex_t mutex;

void* producer(void* arg) {
    while (produced < MAX_ITEMS) {
        // Wait for empty slot
        sem_wait(&empty);
        
        // Lock the buffer
        pthread_mutex_lock(&mutex);
        
        // Produce item
        buffer[in] = produced;
        printf("Produced item %d at position %d\n", produced, in);
        in = (in + 1) % BUFFER_SIZE;
        produced++;
        
        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has a new item
        sem_post(&full);
        
        // Simulate some work
        sleep(rand() % 2);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (consumed < MAX_ITEMS) {
        // Wait for full slot
        sem_wait(&full);
        
        // Lock the buffer
        pthread_mutex_lock(&mutex);
        
        // Consume item
        int item = buffer[out];
        printf("Consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        consumed++;
        
        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has an empty slot
        sem_post(&empty);
        
        // Simulate some work
        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&full, 0, 0);             // Initially no slots are full
    pthread_mutex_init(&mutex, NULL);
    
    // Seed random number generator
    srand(time(NULL));
    
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    
    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    printf("Production and consumption completed\n");
    return 0;
}
