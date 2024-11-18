#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 5  // Adjusted to match the example graph size

// Structure to represent a graph edge
typedef struct {
    int src, dest, weight;
} Edge;

// Bellman-Ford Algorithm
void bellmanFord(Edge edges[], int V, int E, int start) {
    int dist[V];
    
    // Step 1: Initialize distances from start to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    
    // Step 2: Relax all edges V-1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }
    
    // Print the shortest distances
    printf("Distances from source %d:\n", start);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("Distance to vertex %d is INF\n", i);
        } else {
            printf("Distance to vertex %d is %d\n", i, dist[i]);
        }
    }
}

// Dijkstra's Algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int start) {
    int dist[V];
    int visited[V];
    
    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        
        // Find the vertex with the minimum distance value
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        
        // If no vertex is reachable, break
        if (u == -1) {
            break;
        }
        
        visited[u] = 1;
        
        // Update the distance of the adjacent vertices of the chosen vertex
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    // Print the shortest distances
    printf("Distances from source %d:\n", start);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("Distance to vertex %d is INF\n", i);
        } else {
            printf("Distance to vertex %d is %d\n", i, dist[i]);
        }
    }
}

int main() {
    int V = MAX_VERTICES; // Number of vertices
    int E = 8;            // Number of edges
    
    // Example graph for Bellman-Ford (edge list)
    Edge edges[] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };
    
    printf("Bellman-Ford Algorithm:\n");
    bellmanFord(edges, V, E, 0);
    
    // Example graph for Dijkstra (adjacency matrix)
    int graphDijkstra[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, 0, 30, 0},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {0, 0, 10, 60, 0}
    };
    
    printf("\nDijkstra's Algorithm:\n");
    dijkstra(graphDijkstra, V, 0);
    
    return 0;
}
