#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EAT_COUNT 3  // Number of times each philosopher will eat before stopping

// Forks represented as mutexes
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Philosopher struct
typedef struct {
    int id;
} philosopher_t;

// Function for a philosopher to think
void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    sleep(1); // Simulate thinking time
}

// Function for a philosopher to eat
void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(2); // Simulate eating time
}

// Function for the philosopher to perform actions
void* philosopher(void* arg) {
    philosopher_t* philo = (philosopher_t*)arg;
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % NUM_PHILOSOPHERS;
    int eat_count = 0;

    while (eat_count < EAT_COUNT) { // Philosophers stop after eating EAT_COUNT times
        think(philo->id);

        // Pick up the left fork
        pthread_mutex_lock(&forks[left_fork]);

        // Pick up the right fork
        pthread_mutex_lock(&forks[right_fork]);

        eat(philo->id);
        eat_count++;

        // Put down the right fork
        pthread_mutex_unlock(&forks[right_fork]);

        // Put down the left fork
        pthread_mutex_unlock(&forks[left_fork]);
    }

    printf("Philosopher %d has finished eating.\n", philo->id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    philosopher_t philosophers[NUM_PHILOSOPHERS];

    // Initialize forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        pthread_create(&threads[i], NULL, philosopher, (void*)&philosophers[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

