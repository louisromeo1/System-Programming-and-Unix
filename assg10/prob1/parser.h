#ifndef PARSER_H
#define PARSER_H
// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
#include "graph.h"

DependencyGraph *parseMakefile(const char *filename);
void addDependency(Node *node, const char *dependencyName);
void addCommand(Node *node, const char *command);


#endif
