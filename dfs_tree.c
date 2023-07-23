#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Stack implementation for DFS
typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

// Graph representation using adjacency matrix
typedef struct {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to initialize a stack
void initializeStack(Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element into the stack
void push(Stack* stack, int value) {
    stack->top++;
    stack->items[stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    int item;
    if (isStackEmpty(stack)) {
        printf("Stack is empty.\n");
        item = -1;
    } else {
        item = stack->items[stack->top];
        stack->top--;
    }
    return item;
}

// Depth-First Search traversal
void DFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // Initialize visited array with 0
    Stack stack;
    initializeStack(&stack);

    // Visit the startVertex and push it onto the stack
    visited[startVertex] = 1;
    printf("DFS traversal starting from vertex %d: ", startVertex);
    push(&stack, startVertex);

    while (!isStackEmpty(&stack)) {
        int currentVertex = pop(&stack);
        printf("%d ", currentVertex);

        // Visit all adjacent unvisited vertices and push them onto the stack
        for (int i = 0; i < graph->vertices; ++i) {
            if (graph->adjMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                push(&stack, i);
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
    printf("Enter the starting vertex for DFS traversal: ");
    scanf("%d", &startVertex);

    DFS(&graph, startVertex);

    return 0;
}
