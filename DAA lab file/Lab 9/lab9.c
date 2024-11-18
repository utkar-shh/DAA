//Backtracking Approach


#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Backtracking function to solve 0/1 knapsack
void knapsackBacktracking(int weights[], int values[], int n, int capacity, int index, int currentWeight, int currentValue, int *maxValue) {
    // If the weight exceeds capacity, backtrack
    if (currentWeight > capacity) {
        return;
    }
    // Update the max value
    *maxValue = max(*maxValue, currentValue);
    
    // Explore remaining items
    for (int i = index; i < n; i++) {
        knapsackBacktracking(weights, values, n, capacity, i + 1, currentWeight + weights[i], currentValue + values[i], maxValue);
    }
}

int knapsackBacktrackingSolver(int weights[], int values[], int n, int capacity) {
    int maxValue = 0;
    knapsackBacktracking(weights, values, n, capacity, 0, 0, 0, &maxValue);
    return maxValue;
}



//Branch and Bound Approach


#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

float bound(Node u, int n, int capacity, int weights[], int values[]) {
    if (u.weight >= capacity)
        return 0;
    int profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while ((j < n) && (totweight + weights[j] <= capacity)) {
        totweight += weights[j];
        profit_bound += values[j];
        j++;
    }
    if (j < n)
        profit_bound += (capacity - totweight) * values[j] / (float)weights[j];
    return profit_bound;
}

int knapsackBranchAndBound(int weights[], int values[], int n, int capacity) {
    Node queue[100];
    int front = 0, rear = 0;
    Node u, v;

    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, capacity, weights, values);
    queue[rear++] = u;

    int maxProfit = 0;

    while (front < rear) {
        u = queue[front++];

        if (u.level == n - 1) continue;

        v.level = u.level + 1;
        v.weight = u.weight + weights[v.level];
        v.profit = u.profit + values[v.level];

        if (v.weight <= capacity && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, capacity, weights, values);

        if (v.bound > maxProfit)
            queue[rear++] = v;

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, capacity, weights, values);

        if (v.bound > maxProfit)
            queue[rear++] = v;
    }

    return maxProfit;
}



//Dynamic Programming Approach


int knapsackDP(int weights[], int values[], int n, int capacity) {
    int dp[n + 1][capacity + 1];
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    return dp[n][capacity];
}




//Example of Running the Code



int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);

    printf("Backtracking Solution: %d\n", knapsackBacktrackingSolver(weights, values, n, capacity));
    printf("Branch and Bound Solution: %d\n", knapsackBranchAndBound(weights, values, n, capacity));
    printf("Dynamic Programming Solution: %d\n", knapsackDP(weights, values, n, capacity));

    return 0;
}
