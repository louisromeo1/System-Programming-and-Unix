/*
* File: graph.c
* Author: Louis Romeo
* Purpose: Manages the graph structure, including actors, movies, and connections,
* and provides functions for BFS-based Bacon score computation.
*/
#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Graph *create_graph() {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->actors = NULL;
    return graph;
}

void free_graph(Graph *graph) {
    if (!graph) return;
    ActorNode *actor = graph->actors;
    while (actor) {
        MovieNode *movie = actor->movies;
        while (movie) {
            MovieNode *temp_movie = movie;
            movie = movie->next;
            free(temp_movie);
        }
        ActorNode *temp_actor = actor;
        actor = actor->next;
        free(temp_actor->name);
        free(temp_actor);
    }
    free(graph);
}

int build_graph_from_file(Graph *graph, FILE *file) {
    char line[512];
    char current_movie[256] = {0};

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline

        if (strncmp(line, "Movie: ", 7) == 0) {
            strncpy(current_movie, line + 7, sizeof(current_movie) - 1);
        } else if (strlen(line) > 0) {
            add_actor_to_movie(graph, line, current_movie);
        }
    }

    return 1;
}

void add_actor_to_movie(Graph *graph, const char *actor_name, const char *movie_name) {
    ActorNode *actor = find_or_create_actor(graph, actor_name);
    MovieNode *movie = find_or_create_movie(actor, movie_name);

    if (!movie) {
        MovieNode *new_movie = malloc(sizeof(MovieNode));
        if (!new_movie) return;
        strncpy(new_movie->name, movie_name, sizeof(new_movie->name) - 1);
        new_movie->name[sizeof(new_movie->name) - 1] = '\0';
        new_movie->next = actor->movies;
        actor->movies = new_movie;
    }
}

ActorNode *find_or_create_actor(Graph *graph, const char *actor_name) {
    ActorNode *actor = graph->actors;
    while (actor) {
        if (strcmp(actor->name, actor_name) == 0) {
            return actor;
        }
        actor = actor->next;
    }

    ActorNode *new_actor = malloc(sizeof(ActorNode));
    if (!new_actor) return NULL;
    new_actor->name = strdup(actor_name);
    new_actor->movies = NULL;
    new_actor->next = graph->actors;
    graph->actors = new_actor;
    return new_actor;
}

MovieNode *find_or_create_movie(ActorNode *actor, const char *movie_name) {
    MovieNode *movie = actor->movies;
    while (movie) {
        if (strcmp(movie->name, movie_name) == 0) {
            return movie;
        }
        movie = movie->next;
    }
    return NULL;
}

int calculate_bacon_score(Graph *graph, const char *actor_name) {
    return calculate_bacon_score_with_path(graph, actor_name, NULL);
}

int calculate_bacon_score_with_path(Graph *graph, const char *actor_name, char **path) {
    if (!graph || !actor_name) return -1;

    // Special case for Kevin Bacon himself
    if (strcmp(actor_name, "Kevin Bacon") == 0) {
    	if (path) {
    		*path = strdup("Path: Kevin Bacon");
    	}
    	return 0;
    }

    ActorNode *start_actor = find_or_create_actor(graph, actor_name);
    ActorNode *bacon_actor = find_or_create_actor(graph, "Kevin Bacon");
    if (!start_actor || !bacon_actor) return -1;

    Queue *queue = create_queue();
    enqueue(queue, bacon_actor);

    // Initialize distances and visited flags
    ActorNode *actor = graph->actors;
    while (actor) {
        actor->visited = 0;
        actor->distance = -1;
        actor = actor->next;
    }
    bacon_actor->visited = 1;
    bacon_actor->distance = 0;

    while (!is_queue_empty(queue)) {
        ActorNode *current = dequeue(queue);
        MovieNode *movie = current->movies;

        while (movie) {
            ActorNode *neighbor_actor = graph->actors;
            while (neighbor_actor) {
                if (neighbor_actor != current && find_or_create_movie(neighbor_actor, movie->name)) {
                    if (!neighbor_actor->visited) {
                        neighbor_actor->visited = 1;
                        neighbor_actor->distance = current->distance + 1;

                        if (strcmp(neighbor_actor->name, actor_name) == 0) {
                            free_queue(queue);
                            return neighbor_actor->distance;
                        }

                        enqueue(queue, neighbor_actor);
                    }
                }
                neighbor_actor = neighbor_actor->next;
            }
            movie = movie->next;
        }
    }
    free_queue(queue);
    return -1; // No connection found
}
