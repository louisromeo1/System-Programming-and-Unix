// Louis Romeo
// CSC 352 assg9
// 11/21/2024
#include "mymake.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s aMakeFile aTarget\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *makeFile = argv[1];
    const char *target = argv[2];

    Graph *graph = parseMakefile(makeFile);

    Node *startNode = findNode(graph, target);
    if (!startNode) {
        fprintf(stderr, "Error: Target '%s' not found in the makefile.\n", target);
        freeGraph(graph);
        exit(EXIT_FAILURE);
    }

    postOrderTraversal(startNode);

    freeGraph(graph);
    return 0;
}
