#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure
struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive insertion in BST
struct Node* recursiveInsert(struct Node* node, int data) {
    if (node == NULL) 
        return createNode(data);
    
    if (data < node->data)
        node->left = recursiveInsert(node->left, data);
    else if (data > node->data)
        node->right = recursiveInsert(node->right, data);
    
    return node;
}

// Iterative insertion in BST
struct Node* iterativeInsert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* parent = NULL;
    struct Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else // Duplicate data is not allowed
            return root;
    }

    if (parent == NULL)
        return newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Inorder traversal (for testing)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to compare performance
void performanceTest(int arr[], int size) {
    struct Node* root = NULL;
    clock_t start, end;
    double time_recursive, time_iterative;

    // Recursive insertion performance
    start = clock();
    for (int i = 0; i < size; i++) {
        root = recursiveInsert(root, arr[i]);
    }
    end = clock();
    time_recursive = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Clear the tree
    root = NULL;

    // Iterative insertion performance
    start = clock();
    for (int i = 0; i < size; i++) {
        root = iterativeInsert(root, arr[i]);
    }
    end = clock();
    time_iterative = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Display results
    printf("Recursive Insertion Time: %f seconds\n", time_recursive);
    printf("Iterative Insertion Time: %f seconds\n", time_iterative);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Display insertion order
    printf("Insertion order: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Compare performance
    performanceTest(arr, size);

    return 0;
}
