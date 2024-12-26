#ifndef GRAPH_H
#define GRAPH_H
// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
typedef struct Dependency {
    char *name;
    struct Dependency *next;
} Dependency;

typedef struct Command {
    char *command;
    struct Command *next;
} Command;

typedef struct Node {
    char *name;
    Dependency *dependencies;
    Command *commands;
    int visited;
    struct Node *next;
} Node;

typedef struct DependencyGraph {
    Node *nodes;
    char *firstTarget;
} DependencyGraph;

// Function prototypes
DependencyGraph *createDependencyGraph();
Node *addTarget(DependencyGraph *graph, const char *name);
int processTarget(DependencyGraph *graph, const char *target);
void freeDependencyGraph(DependencyGraph *graph);
Node *findNode(DependencyGraph *graph, const char *name);
int isDependencyNewer(Node *node);

#endif
