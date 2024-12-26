#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Author: Louis Romeo
// CSC 352
// Assignment 8 Prob 1
// Purpose: Program models the shortest path Djikstra's algorithm.

#define MAX_NAME_LEN 64
#define INITIAL_CAPACITY 10

typedef struct Edge {
    int distance;
    struct Vertex *destination;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    char name[MAX_NAME_LEN + 1];
    int minDist;
    int visited;
    struct Edge *edges;
    struct Vertex *next;
} Vertex;

typedef struct Graph {
    Vertex *vertices;
} Graph;

// Function prototypes
Graph *createGraph();
Vertex *addVertex(Graph *graph, const char *name);
void addEdge(Graph *graph, const char *name1, const char *name2, int distance);
Vertex *findVertex(Graph *graph, const char *name);
void dijkstra(Graph *graph, Vertex *source);
int findShortestPath(Graph *graph, const char *start, const char *end);
void freeGraph(Graph *graph);
void resetGraph(Graph *graph);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s inFile\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    Graph *graph = createGraph();
    char name1[MAX_NAME_LEN + 1], name2[MAX_NAME_LEN + 1];
    int distance;

    while (fscanf(file, "%64s %64s %d", name1, name2, &distance) == 3) {
        addEdge(graph, name1, name2, distance);
    }
    fclose(file);

    char start[MAX_NAME_LEN + 1], end[MAX_NAME_LEN + 1];
    while (scanf("%64s %64s", start, end) == 2) {
        int result = findShortestPath(graph, start, end);
        if (result != INT_MAX) {
            printf("%d\n", result);
        } else {
            fprintf(stderr, "No path between %s and %s\n", start, end);
        }
        resetGraph(graph);
    }

    freeGraph(graph);
    return EXIT_SUCCESS;
}

// Create a new graph
Graph *createGraph() {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = NULL;
    return graph;
}

// Add a vertex to the graph
Vertex *addVertex(Graph *graph, const char *name) {
    Vertex *newVertex = malloc(sizeof(Vertex));
    strncpy(newVertex->name, name, MAX_NAME_LEN);
    newVertex->name[MAX_NAME_LEN] = '\0';
    newVertex->minDist = INT_MAX;
    newVertex->visited = 0;
    newVertex->edges = NULL;
    newVertex->next = graph->vertices;
    graph->vertices = newVertex;
    return newVertex;
}

// Find a vertex in the graph by name
Vertex *findVertex(Graph *graph, const char *name) {
    Vertex *current = graph->vertices;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Add an edge to the graph
void addEdge(Graph *graph, const char *name1, const char *name2, int distance) {
    Vertex *vertex1 = findVertex(graph, name1);
    if (!vertex1) vertex1 = addVertex(graph, name1);

    Vertex *vertex2 = findVertex(graph, name2);
    if (!vertex2) vertex2 = addVertex(graph, name2);

    Edge *edge1 = malloc(sizeof(Edge));
    edge1->distance = distance;
    edge1->destination = vertex2;
    edge1->next = vertex1->edges;
    vertex1->edges = edge1;

    Edge *edge2 = malloc(sizeof(Edge));
    edge2->distance = distance;
    edge2->destination = vertex1;
    edge2->next = vertex2->edges;
    vertex2->edges = edge2;
}

// Dijkstra's algorithm
void dijkstra(Graph *graph, Vertex *source) {
    source->minDist = 0;
    Vertex *u;

    while (1) {
        int smallestDist = INT_MAX;
        u = NULL;

        // Find the unvisited vertex with the smallest minDist
        Vertex *current = graph->vertices;
        while (current) {
            if (!current->visited && current->minDist < smallestDist) {
                smallestDist = current->minDist;
                u = current;
            }
            current = current->next;
        }

        if (!u) break;  // No more reachable vertices

        u->visited = 1;

        Edge *edge = u->edges;
        while (edge) {
            Vertex *v = edge->destination;
            int newDist = u->minDist + edge->distance;

            if (newDist < v->minDist) {
                v->minDist = newDist;
            }
            edge = edge->next;
        }
    }
}

// Find the shortest path between two cities
int findShortestPath(Graph *graph, const char *start, const char *end) {
    Vertex *startVertex = findVertex(graph, start);
    Vertex *endVertex = findVertex(graph, end);

    if (!startVertex || !endVertex) {
        return INT_MAX; // No path
    }

    dijkstra(graph, startVertex);
    return endVertex->minDist;
}

// Free the graph and all its vertices and edges
void freeGraph(Graph *graph) {
    Vertex *vertex = graph->vertices;
    while (vertex) {
        Edge *edge = vertex->edges;
        while (edge) {
            Edge *tempEdge = edge;
            edge = edge->next;
            free(tempEdge);
        }
        Vertex *tempVertex = vertex;
        vertex = vertex->next;
        free(tempVertex);
    }
    free(graph);
}

// Reset the graph for a new query
void resetGraph(Graph *graph) {
    Vertex *vertex = graph->vertices;
    while (vertex) {
        vertex->minDist = INT_MAX;
        vertex->visited = 0;
        vertex = vertex->next;
    }
}
