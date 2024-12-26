#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Author: Louis Romeo
// CSC 352
// Assignment 7 Prob 1
// Purpose: Program that models the reachability problem.

#define MAX_NAME_LEN 64

typedef struct Edge {
    struct Vertex *to;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    char name[MAX_NAME_LEN];
    Edge *edges;
    struct Vertex *next;
    int visited;
} Vertex;

typedef struct Graph {
    Vertex *vertices;
} Graph;

Graph graph = {NULL};

Vertex *find_vertex(const char *name) {
    Vertex *v = graph.vertices;
    while (v != NULL) {
        if (strcmp(v->name, name) == 0) return v;
        v = v->next;
    }
    return NULL;
}

Vertex *add_vertex(const char *name) {
    if (find_vertex(name) != NULL) {
        fprintf(stderr, "Error: Vertex %s already declared.\n", name);
        return NULL;
    }
    Vertex *new_vertex = malloc(sizeof(Vertex));
    if (new_vertex == NULL) {
        perror("Failed to allocate memory for vertex");
        exit(EXIT_FAILURE);
    }
    strncpy(new_vertex->name, name, MAX_NAME_LEN);
    new_vertex->name[MAX_NAME_LEN - 1] = '\0'; // null-termination
    new_vertex->edges = NULL;
    new_vertex->visited = 0;
    new_vertex->next = graph.vertices;
    graph.vertices = new_vertex;
    return new_vertex;
}

void add_edge(const char *from, const char *to) {
    Vertex *v_from = find_vertex(from);
    Vertex *v_to = find_vertex(to);

    if (!v_from || !v_to) {
        fprintf(stderr, "Error: Edge has undefined vertex.\n");
        return;
    }

    Edge *e = v_from->edges;
    while (e) {
        if (e->to == v_to) return;  // Edge already exists
        e = e->next;
    }

    Edge *new_edge = malloc(sizeof(Edge));
    if (new_edge == NULL) {
        perror("Failed to allocate memory for edge");
        exit(EXIT_FAILURE);
    }
    new_edge->to = v_to;
    new_edge->next = v_from->edges;
    v_from->edges = new_edge;
}

int dfs(Vertex *from, Vertex *to) {
    if (from == to) return 1;
    if (from->visited) return 0;
    from->visited = 1;
    Edge *e = from->edges;
    while (e != NULL) {
        if (dfs(e->to, to)) return 1;
        e = e->next;
    }
    return 0;
}

void reset_visits() {
    Vertex *v = graph.vertices;
    while (v != NULL) {
        v->visited = 0;
        v = v->next;
    }
}

void process_directive(char *line) {
    char op[3], arg1[MAX_NAME_LEN], arg2[MAX_NAME_LEN];
    int result;

    if (sscanf(line, "%2s %63s %63s", op, arg1, arg2) < 1) {
        fprintf(stderr, "Error: Invalid directive format.\n");
        return;
    }

    if (strcmp(op, "@n") == 0) {
        add_vertex(arg1);
    } else if (strcmp(op, "@e") == 0) {
        add_edge(arg1, arg2);
    } else if (strcmp(op, "@q") == 0) {
        Vertex *from = find_vertex(arg1);
        Vertex *to = find_vertex(arg2);
        if (!from || !to) {
            fprintf(stderr, "Error: Undefined vertices in query.\n");
            return;
        }
        reset_visits();
        result = dfs(from, to);
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error: Unknown operation %s\n", op);
    }
}

void free_graph() {
    Vertex *v = graph.vertices;
    while (v != NULL) {
        Edge *e = v->edges;
        while (e != NULL) {
            Edge *temp_edge = e;
            e = e->next;
            free(temp_edge);
        }
        Vertex *temp_vertex = v;
        v = v->next;
        free(temp_vertex);
    }
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [inFile]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }
    }

    char line[128];
    while (fgets(line, sizeof(line), input)) {
        process_directive(line);
    }

    if (argc == 2) fclose(input);

    // Free all allocated memory before exiting
    free_graph();

    return EXIT_SUCCESS;
}
