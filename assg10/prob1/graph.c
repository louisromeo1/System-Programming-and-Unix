#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "graph.h"
#include "utils.h"
// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
typedef enum {
    NOT_VISITED,
    VISITING,
    VISITED
} VisitStatus;

// Create a new dependency graph
DependencyGraph *createDependencyGraph() {
    DependencyGraph *graph = malloc(sizeof(DependencyGraph));
    if (!graph) {
        perror("Error allocating memory for graph");
        exit(1);
    }
    graph->nodes = NULL;
    graph->firstTarget = NULL;
    return graph;
}

// Add a target node to the dependency graph
Node *addTarget(DependencyGraph *graph, const char *name) {
    Node *node = findNode(graph, name);
    if (!node) {
        node = malloc(sizeof(Node));
        if (!node) {
            perror("Error allocating memory for node");
            exit(1);
        }
        node->name = strdup(name);
        node->dependencies = NULL;
        node->commands = NULL;
        node->visited = NOT_VISITED;
        node->next = graph->nodes;
        graph->nodes = node;

        if (!graph->firstTarget) {
            graph->firstTarget = node->name;
        }
    }
    return node;
}

// Find a node in the dependency graph by name
Node *findNode(DependencyGraph *graph, const char *name) {
    for (Node *current = graph->nodes; current != NULL; current = current->next) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
    }
    return NULL;
}

// Check if any dependencies are newer than the target
int isDependencyNewer(Node *node) {
    struct stat targetStat, depStat;
    if (stat(node->name, &targetStat) != 0) {
        return 1;
    }

    for (Dependency *dep = node->dependencies; dep != NULL; dep = dep->next) {
        if (stat(dep->name, &depStat) == 0) {
            if (difftime(depStat.st_mtime, targetStat.st_mtime) > 0) {
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Dependency '%s' does not exist.\n", dep->name);
            return 1;
        }
    }
    return 0;
}

// Process a target in the graph recursively
int processTarget(DependencyGraph *graph, const char *target) {
    Node *node = findNode(graph, target);
    if (!node) {
        fprintf(stderr, "Error: Target '%s' not found.\n", target);
        return 0;
    }

    if (node->visited == VISITING) {
        fprintf(stderr, "Error: Circular dependency detected involving target '%s'.\n", target);
        return 0;
    }

    if (node->visited == VISITED) {
        return 1;
    }

    node->visited = VISITING;

    struct stat targetStat;
    int targetExists = stat(target, &targetStat) == 0;

    for (Dependency *dep = node->dependencies; dep; dep = dep->next) {
        if (!processTarget(graph, dep->name)) {
            return 0;
        }
    }

    if (!targetExists || isDependencyNewer(node)) {
        for (Command *cmd = node->commands; cmd; cmd = cmd->next) {
            printf("%s\n", cmd->command);
            if (system(cmd->command) != 0) {
                fprintf(stderr, "Error: Command failed.\n");
                return 0;
            }
        }
    } else {
        printf("%s is up to date.\n", target);
    }

    node->visited = VISITED;
    return 1;
}

// Free all dynamically allocated memory in the graph
void freeDependencyGraph(DependencyGraph *graph) {
    Node *node = graph->nodes;
    while (node) {
        Node *nextNode = node->next;

        free(node->name);
        while (node->dependencies) {
            Dependency *nextDep = node->dependencies->next;
            free(node->dependencies->name);
            free(node->dependencies);
            node->dependencies = nextDep;
        }

        while (node->commands) {
            Command *nextCmd = node->commands->next;
            free(node->commands->command);
            free(node->commands);
            node->commands = nextCmd;
        }

        free(node);
        node = nextNode;
    }
    free(graph);
}
