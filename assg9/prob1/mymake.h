// Louis Romeo
// CSC 352 assg9
// 11/21/2024
#ifndef MYMAKE_H
#define MYMAKE_H

typedef struct Node {
    char *name;
    struct Node **dependencies;
    int num_dependencies;
    char **commands;
    int num_commands;
    int visited;
    struct Node *next;
} Node;

typedef struct Graph {
    Node *head;
} Graph;

// Parsing
Graph *parseMakefile(const char *filename);

// Graph Operations
Graph *createGraph();
Node *createNode(const char *name);
void addNode(Graph *graph, Node *node);
Node *findNode(Graph *graph, const char *name);
Node *findOrCreateNode(Graph *graph, const char *name);
void addDependency(Node *node, Node *dependency);
void addCommand(Node *node, const char *command);
void postOrderTraversal(Node *node);
void freeGraph(Graph *graph);

// Utility
char *trimWhitespace(char *str);

#endif // MYMAKE_H
