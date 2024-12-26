#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "graph.h"
#include "utils.h"

// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
DependencyGraph *parseMakefile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening makefile");
        return NULL;
    }

    DependencyGraph *graph = createDependencyGraph();
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        char *trimmedLine = trimWhitespace(line);
        if (strlen(trimmedLine) == 0 || trimmedLine[0] == '#') continue;

        char *target = strtok(trimmedLine, ":");
        if (!target) continue;

        target = trimWhitespace(target);
        char *dependencies = strtok(NULL, "\n");
        if (dependencies) dependencies = trimWhitespace(dependencies);

        Node *node = addTarget(graph, target);
        if (dependencies) {
            char *dep = strtok(dependencies, " ");
            while (dep) {
                addDependency(node, dep);
                dep = strtok(NULL, " ");
            }
        }

        while (fgets(line, sizeof(line), file)) {
            if (line[0] != '\t') break;
            char *command = trimWhitespace(line + 1);
            addCommand(node, command);
        }
    }

    fclose(file);
    return graph;
}

void addDependency(Node *node, const char *dependencyName) {
    Dependency *newDep = malloc(sizeof(Dependency));
    if (!newDep) {
        perror("Error allocating memory for dependency");
        exit(1);
    }
    newDep->name = strdup(dependencyName);
    newDep->next = node->dependencies;
    node->dependencies = newDep;
}

void addCommand(Node *node, const char *command) {
    Command *newCmd = malloc(sizeof(Command));
    if (!newCmd) {
        perror("Error allocating memory for command");
        exit(1);
    }
    newCmd->command = strdup(command);
    newCmd->next = node->commands;
    node->commands = newCmd;
}
