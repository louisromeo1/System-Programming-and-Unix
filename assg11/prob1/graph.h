#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct MovieNode {
    char name[256];
    struct MovieNode *next;
} MovieNode;

typedef struct ActorNode {
    char *name;
    MovieNode *movies;
    struct ActorNode *next;
    int visited; // For BFS
    int distance; // Bacon score distance
} ActorNode;

typedef struct Graph {
    ActorNode *actors;
} Graph;

Graph *create_graph();
void free_graph(Graph *graph);
int build_graph_from_file(Graph *graph, FILE *file);
void add_actor_to_movie(Graph *graph, const char *actor_name, const char *movie_name);
ActorNode *find_or_create_actor(Graph *graph, const char *actor_name);
MovieNode *find_or_create_movie(ActorNode *actor, const char *movie_name);
int calculate_bacon_score(Graph *graph, const char *actor_name);
int calculate_bacon_score_with_path(Graph *graph, const char *actor_name, char **path);

#endif
