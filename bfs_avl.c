#include <stdio.h>
#include <stdbool.h>
#define MAX_VERTICES 100

// Queue implementation for BFS
typedef struct
{
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// Graph representation using adjacency matrix
typedef struct
{
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to initialize a queue
void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* q){
    return q->rear == -1;
}

// Function to add an element to the queue
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full.\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }

        q->rear++;
        q->items[q->rear] = value;
    }
}

// Function to remove an element from the queue
int dequeue(Queue* q) {
    int item;
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Breadth-First Search traversal
void BFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // Initialize visited array with 0
    Queue q;
    initializeQueue(&q);

    // Visit the startVertex and enqueue it
    visited[startVertex] = 1;
    printf("BFS traversal starting from vertex %d: ", startVertex);
    enqueue(&q, startVertex);

    while (!isQueueEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        // Enqueue all adjacent unvisited vertices and mark them as visited
        for (int i = 0; i < graph->vertices; ++i) {
            if (graph->adjMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    Graph graph;
    int vertices, edges, v1, v2;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    graph.vertices = vertices;

    // Initialize the adjacency matrix with 0's
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            graph.adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    // Add edges to the graph
    for (int i = 0; i < edges; ++i) {
        printf("Enter edge %d vertices (v1 v2): ", i + 1);
        scanf("%d %d", &v1, &v2);
        graph.adjMatrix[v1][v2] = 1;
        graph.adjMatrix[v2][v1] = 1;
    }

    int startVertex;
    printf("Enter the starting vertex for BFS traversal: ");
    scanf("%d", &startVertex);

    BFS(&graph, startVertex);

    return 0;
}
