#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int V;
    int** adj;
} Graph;
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->adj[i][j] = 0;
        }
    }
    return graph;
}
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) free(graph->adj[i]);
    free(graph->adj);
    free(graph);
}
void addEdge(Graph* graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1;
}
void BFS(Graph* graph, int start) {
    int V = graph->V;
    int* visited = (int*)malloc(V * sizeof(int));
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    queue[rear++] = start;
    visited[start] = 1;
    printf("BFS: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        for (int i = 0; i < V; i++) {
            if (graph->adj[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}
void DFS(Graph* graph, int start) {
    int V = graph->V;
    int* visited = (int*)malloc(V * sizeof(int));
    int* stack = (int*)malloc(V * sizeof(int));
    int top = -1;
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    stack[++top] = start;

    printf("DFS: ");
    while (top >= 0) {
        int current = stack[top--];
        if (!visited[current]) {
            visited[current] = 1;
            printf("%d ", current);
        }
        for (int i = V - 1; i >= 0; i--) {
            if (graph->adj[current][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
    printf("\n");
    free(visited);
    free(stack);
}

int main() {
    int V, E;
    printf("Dinh: ");
    scanf("%d", &V);
    printf("Canh: ");
    scanf("%d", &E);
    Graph* graph = createGraph(V);
    printf("Nhap cac canh\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    int start;
    printf("Nhap dinh bat dau ");
    scanf("%d", &start);
    BFS(graph, start);
    DFS(graph, start);
    freeGraph(graph);
    return 0;
}
