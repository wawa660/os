#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, total = 0;
    int requests[100];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (i = 0; i < n; i++) {
        total += abs(requests[i] - head);
        printf("Move from %d to %d (Distance: %d)\n", head, requests[i], abs(requests[i] - head));
        head = requests[i];
    }

    printf("Total head movement (FCFS): %d\n", total);
    return 0;
}

