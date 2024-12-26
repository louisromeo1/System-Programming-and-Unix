// Louis Romeo
// CSC 352 assg9
// 11/21/2024
#include "mymake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *createGraph() {
    Graph *graph = malloc(sizeof(Graph));
    graph->head = NULL;
    return graph;
}

Node *createNode(const char *name) {
    Node *node = malloc(sizeof(Node));
    node->name = strdup(name);
    node->dependencies = NULL;
    node->num_dependencies = 0;
    node->commands = NULL;
    node->num_commands = 0;
    node->visited = 0;
    node->next = NULL;
    return node;
}

void addNode(Graph *graph, Node *node) {
    node->next = graph->head;
    graph->head = node;
}

Node *findNode(Graph *graph, const char *name) {
    for (Node *n = graph->head; n; n = n->next) {
        if (strcmp(n->name, name) == 0) {
            return n;
        }
    }
    return NULL;
}

Node *findOrCreateNode(Graph *graph, const char *name) {
    Node *node = findNode(graph, name);
    if (!node) {
        node = createNode(name);
        addNode(graph, node);
    }
    return node;
}

void addDependency(Node *node, Node *dependency) {
    node->dependencies = realloc(node->dependencies, sizeof(Node *) * (node->num_dependencies + 1));
    node->dependencies[node->num_dependencies++] = dependency;
}

void addCommand(Node *node, const char *command) {
    node->commands = realloc(node->commands, sizeof(char *) * (node->num_commands + 1));
    node->commands[node->num_commands++] = strdup(command);
}

void postOrderTraversal(Node *node) {
    if (node->visited) return;

    node->visited = 1;
    for (int i = 0; i < node->num_dependencies; ++i) {
        postOrderTraversal(node->dependencies[i]);
    }

    printf("%s\n", node->name);
    for (int i = 0; i < node->num_commands; ++i) {
        printf("  %s\n", node->commands[i]);
    }
}

void freeGraph(Graph *graph) {
    Node *node = graph->head;
    while (node) {
        Node *next = node->next;
        free(node->name);
        for (int i = 0; i < node->num_dependencies; ++i) {
            // Dependencies are shared, so we don't free them here
        }
        free(node->dependencies);
        for (int i = 0; i < node->num_commands; ++i) {
            free(node->commands[i]);
        }
        free(node->commands);
        free(node);
        node = next;
    }
    free(graph);
}
