// Louis Romeo
// CSC 352 assg9
// 11/21/2024
// Contains a parser program for Makefile.
#include "mymake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Graph *parseMakefile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Graph *graph = createGraph();
    char *line = NULL;
    size_t len = 0;
    Node *currentNode = NULL;

    while (getline(&line, &len, file) != -1) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        if (strchr(line, ':')) {
            // Parse target and dependencies
            char *target = strtok(line, ":");
            char *deps = strtok(NULL, "");

            if (!target) {
                fprintf(stderr, "Error: Invalid target line.\n");
                free(line);
                fclose(file);
                freeGraph(graph);
                exit(EXIT_FAILURE);
            }

            // Trim whitespace
            target = trimWhitespace(target);

            if (findNode(graph, target)) {
                fprintf(stderr, "Error: Duplicate target '%s'.\n", target);
                free(line);
                fclose(file);
                freeGraph(graph);
                exit(EXIT_FAILURE);
            }

            currentNode = createNode(target);
            addNode(graph, currentNode);

            if (deps) {
                char *dep = strtok(deps, " \t");
                while (dep) {
                    dep = trimWhitespace(dep);
                    Node *depNode = findOrCreateNode(graph, dep);
                    addDependency(currentNode, depNode);
                    dep = strtok(NULL, " \t");
                }
            }
        } else if (line[0] == '\t') {
            if (!currentNode) {
                fprintf(stderr, "Error: Command without a target.\n");
                free(line);
                fclose(file);
                freeGraph(graph);
                exit(EXIT_FAILURE);
            }

            addCommand(currentNode, line + 1); // Skip the leading tab
        } else if (*line) {
            fprintf(stderr, "Error: Invalid line format.\n");
            free(line);
            fclose(file);
            freeGraph(graph);
            exit(EXIT_FAILURE);
        }
    }

    free(line);
    fclose(file);
    return graph;
}
