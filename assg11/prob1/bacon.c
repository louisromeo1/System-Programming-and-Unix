/*
* File: bacon.c
* Author: Louis Romeo
* Purpose: Implements the main program logic, handling command-line arguments,
* creating the graph and getting Bacon scores.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

void print_usage() {
    fprintf(stderr, "Usage: bacon [-l] <inFile>\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int show_path = 0;
    char *filename = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            show_path = 1;
        } else if (!filename) {
            filename = argv[i];
        } else {
            print_usage();
        }
    }

    if (!filename) {
        print_usage();
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Graph *graph = create_graph();
    if (!build_graph_from_file(graph, file)) {
        fprintf(stderr, "Error reading graph from file\n");
        fclose(file);
        free_graph(graph);
        exit(1);
    }

    fclose(file);

    char actor[256];
    while (fgets(actor, sizeof(actor), stdin)) {
        actor[strcspn(actor, "\n")] = 0; // Remove newline

        if (strlen(actor) == 0) {
            continue;
        }

        int score;
        if (show_path) {
            char *path = NULL;
            score = calculate_bacon_score_with_path(graph, actor, &path);
            if (score >= 0) {
                printf("%s\n", path);
                free(path);
            }
        } else {
            score = calculate_bacon_score(graph, actor);
        }

        if (score >= 0) {
            if (strcmp(actor, "Kevin Bacon") == 0) {
                printf("Actor '%s' is Kevin Bacon with a score of 0\n", actor);
            } else {
                printf("Score: %d\n", score);
            }
        } else {
            fprintf(stderr, "Actor '%s' not found or no connection to Kevin Bacon\n", actor);
        }
    }

    free_graph(graph);
    return 0;
}
