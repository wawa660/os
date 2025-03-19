#include<stdio.h>

int main()
{
    int p[10], at[10], bt[10], ct[10], tat[10], wt[10], i, j, temp = 0, n;
    float awt = 0, atat = 0;

    // Input number of processes
    printf("Enter number of processes you want: ");
    scanf("%d", &n);

    // Input process IDs
    printf("Enter %d process IDs: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Input arrival times
    printf("Enter %d arrival times: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    // Input burst times
    printf("Enter %d burst times: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    // Sorting processes based on arrival times
    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - i - 1); j++) {
            if (at[j] > at[j + 1]) {
                // Swap process IDs, arrival times, and burst times
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;

                temp = at[j + 1];
                at[j + 1] = at[j];
                at[j] = temp;

                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculate completion times
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        // When a process is idle in between
        temp = 0;
        if (ct[i - 1] < at[i]) {
            temp = at[i] - ct[i - 1];
        }
        ct[i] = ct[i - 1] + bt[i] + temp;
    }

    // Calculate turnaround time and waiting time
    printf("\nP\t A.T\t B.T\t C.T\t TAT\t WT\n");
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        atat += tat[i];
        awt += wt[i];
    }

    atat = atat / n;
    awt = awt / n;

    // Output the result
    for (i = 0; i < n; i++) {
        printf("P%d\t %d\t %d\t %d \t %d \t %d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %f", atat);
    printf("\nAverage Waiting Time = %f", awt);

    return 0;
}

