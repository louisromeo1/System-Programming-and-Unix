#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "graph.h"
// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
int main(int argc, char *argv[]) {
    char *makefile = "myMakefile";
    char *target = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                makefile = argv[++i];
            } else {
                fprintf(stderr, "Error: No file name provided after -f.\n");
                exit(1);
            }
        } else {
            if (target) {
                fprintf(stderr, "Error: Multiple targets specified.\n");
                exit(1);
            }
            target = argv[i];
        }
    }

    // Parse the makefile
    DependencyGraph *graph = parseMakefile(makefile);
    if (!graph) {
        fprintf(stderr, "Error: Failed to parse makefile.\n");
        exit(1);
    }

    // Use the first target if none specified
    if (!target) {
        target = graph->firstTarget;
    }

    if (!target) {
        fprintf(stderr, "Error: No target found in makefile.\n");
        freeDependencyGraph(graph);
        exit(1);
    }

    // Process the target
    if (!processTarget(graph, target)) {
        fprintf(stderr, "Error: Failed to process target '%s'.\n", target);
        freeDependencyGraph(graph);
        exit(1);
    }

    freeDependencyGraph(graph);
    return 0;
}
