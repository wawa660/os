#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

// Function to sort processes by priority
void sortByPriority(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                // Swap processes if the priority of i is greater than j
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time
void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].burst_time + proc[i - 1].waiting_time;
    }
}

// Function to calculate turnaround time
void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

// Function to display results
void displayResults(struct Process proc[], int n) {
    printf("\nProcess ID | Burst Time | Priority | Waiting Time | Turnaround Time\n");
    printf("--------------------------------------------------------------------\n");

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("%9d | %10d | %8d | %12d | %15d\n", proc[i].id, proc[i].burst_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for process %d: ", proc[i].id);
        scanf("%d", &proc[i].priority);
    }

    // Sort processes by priority
    sortByPriority(proc, n);

    // Calculate waiting time and turnaround time
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    // Display results
    displayResults(proc, n);

    return 0;
}
