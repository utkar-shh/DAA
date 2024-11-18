#include <stdio.h>
#include <limits.h>

#define N 5  // Maximum number of matrices

// Function to print the optimal parenthesization
void printOptimalParenthesis(int s[N][N], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    } else {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to perform matrix chain multiplication and find the minimum cost
void matrixChainOrder(int p[], int n) {
    int m[N][N] = {0};     // m[i][j] stores the minimum number of multiplications needed to compute the product from A_i to A_j
    int s[N][N] = {0};     // s[i][j] stores the index of the optimal split point

    // Calculate m[i][j] for chain lengths 2 to n
    for (int l = 2; l < n; l++) {  // l is chain length
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print the minimum cost and the optimal parenthesization
    printf("Minimum number of multiplications required: %d\n", m[1][n - 1]);
    printf("Optimal Parenthesization: ");
    printOptimalParenthesis(s, 1, n - 1);
    printf("\n");
}

int main() {
    int p[] = {10, 30, 5, 60, 5}; // Example matrix dimensions (for 4 matrices, dimensions are 10x30, 30x5, 5x60, 60x5)
    int n = sizeof(p) / sizeof(p[0]);

    matrixChainOrder(p, n);
    return 0;
}
