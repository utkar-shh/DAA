#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;
} Item;

// Comparison function for sorting items by value-to-weight ratio (for greedy approach)
int compare(const void *a, const void *b) {
    double r1 = (double)((Item *)a)->value / ((Item *)a)->weight;
    double r2 = (double)((Item *)b)->value / ((Item *)b)->weight;
    return r2 - r1 > 0 ? 1 : -1;
}

// Greedy approach function (not optimal for 0/1 knapsack but used for comparison)
int knapsackGreedy(Item items[], int n, int maxWeight) {
    qsort(items, n, sizeof(Item), compare); // Sort items by value-to-weight ratio

    int totalValue = 0, currentWeight = 0;
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= maxWeight) {
            totalValue += items[i].value;
            currentWeight += items[i].weight;
        }
    }
    return totalValue;
}

// Dynamic Programming approach for 0/1 Knapsack
int knapsackDP(Item items[], int n, int maxWeight) {
    int dp[n + 1][maxWeight + 1];
    
    // Initialize dp array
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= maxWeight; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;  // Base case
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ?
                            items[i - 1].value + dp[i - 1][w - items[i - 1].weight] :
                            dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][maxWeight];  // Maximum value for full capacity and all items
}

int main() {
    int maxWeight = 50; // Maximum weight capacity of the knapsack
    Item items[] = {{60, 10}, {100, 20}, {120, 30}}; // Example items
    int n = sizeof(items) / sizeof(items[0]);

    printf("Greedy approach result : %d\n", knapsackGreedy(items, n, maxWeight));
    printf("Dynamic Programming approach result : %d\n", knapsackDP(items, n, maxWeight));

    return 0;
}
