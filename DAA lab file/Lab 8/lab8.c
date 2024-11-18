#include <stdio.h>

#define MAX 100

int solution[MAX];  // Array to store the current subset solution

// Backtracking function to find the subsets
void sumOfSubset(int set[], int n, int subsetSum, int targetSum, int index, int start) {
    // If the subset sum equals the target sum, print the current subset
    if (subsetSum == targetSum) {
        printf("{ ");
        for (int i = 0; i < index; i++) {
            printf("%d ", solution[i]);
        }
        printf("}\n");
        return;
    }

    // For each element, check if adding it to the subset will help reach the target sum
    for (int i = start; i < n; i++) {
        // If the current element can be included in the subset
        if (subsetSum + set[i] <= targetSum) {
            solution[index] = set[i];  // Include the current element in the solution
            sumOfSubset(set, n, subsetSum + set[i], targetSum, index + 1, i + 1);
        }
    }
}

int main() {
    int set[] = {10, 7, 5, 18, 12, 20, 15};  // Example set of positive integers
    int n = sizeof(set) / sizeof(set[0]);
    int targetSum = 35;  // Target sum to be achieved by subsets

    printf("Subsets with sum %d are:\n", targetSum);
    sumOfSubset(set, n, 0, targetSum, 0, 0);

    return 0;
}
