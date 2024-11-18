#include <stdio.h>
#include <stdlib.h>

// Structure for storing activities
struct Activity {
    int start;
    int finish;
};

// Comparator function for qsort to sort activities by finish time
int compare(const void *a, const void *b) {
    struct Activity *activityA = (struct Activity *)a;
    struct Activity *activityB = (struct Activity *)b;
    return (activityA->finish - activityB->finish);
}

// Function to perform activity selection
void activitySelection(struct Activity arr[], int n) {
    // Sort activities by finish time
    qsort(arr, n, sizeof(struct Activity), compare);

    printf("Selected activities:\n");

    // The first activity always gets selected
    int i = 0;
    printf("Activity %d: Start = %d, Finish = %d\n", i + 1, arr[i].start, arr[i].finish);

    // Iterate through the remaining activities
    for (int j = 1; j < n; j++) {
        // If this activity starts after or when the last selected activity finishes
        if (arr[j].start >= arr[i].finish) {
            printf("Activity %d: Start = %d, Finish = %d\n", j + 1, arr[j].start, arr[j].finish);
            i = j; // Update the index of the last selected activity
        }
    }
}

int main() {
    struct Activity arr[] = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Activities sorted by finish time:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: Start = %d, Finish = %d\n", i + 1, arr[i].start, arr[i].finish);
    }
    printf("\n");

    activitySelection(arr, n);

    return 0;
}
