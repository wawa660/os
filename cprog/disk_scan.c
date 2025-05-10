#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int i, j, n, head, size, total = 0, direction;
    int requests[100], left[100], right[100], l = 0, r = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (0 to size-1): ");
    scanf("%d", &size);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    qsort(left, l, sizeof(int), compare);
    qsort(right, r, sizeof(int), compare);

    printf("Head movement:\n");

    if (direction == 1) {  // Moving right
        for (i = 0; i < r; i++) {
            printf("Move from %d to %d (Distance: %d)\n", head, right[i], abs(right[i] - head));
            total += abs(right[i] - head);
            head = right[i];
        }
        if (l > 0) {
            total += abs((size - 1) - head);
            head = size - 1;
            printf("Move to end of disk: %d\n", head);
            total += abs(head - left[l - 1]);
            for (i = l - 1; i >= 0; i--) {
                printf("Move from %d to %d (Distance: %d)\n", head, left[i], abs(left[i] - head));
                total += abs(left[i] - head);
                head = left[i];
            }
        }
    } else {  // Moving left
        for (i = l - 1; i >= 0; i--) {
            printf("Move from %d to %d (Distance: %d)\n", head, left[i], abs(left[i] - head));
            total += abs(left[i] - head);
            head = left[i];
        }
        if (r > 0) {
            total += head;  // Move to start of disk (0)
            head = 0;
            printf("Move to start of disk: %d\n", head);
            for (i = 0; i < r; i++) {
                printf("Move from %d to %d (Distance: %d)\n", head, right[i], abs(right[i] - head));
                total += abs(right[i] - head);
                head = right[i];
            }
        }
    }

    printf("Total head movement (SCAN): %d\n", total);
    return 0;
}

