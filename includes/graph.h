/* Victor Forbes - 9293394 */

#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

/* Creates a Graph with Vertex values of size "vertex_value_size"
and Edge values of size "edge_value_size". */
Graph *graph_new(int, int);

/* Erases every element in the Graph. */
void graph_clear(Graph *);

/* Destroys the Graph. */
void graph_delete(Graph *);

/* Inserts a Vertex in the Graph and returns a reference to it. */
Vertex *graph_insert_vertex(Graph *, const void *);

/* Inserts an Edge in the Graph and returns a reference to it. */
Edge *graph_insert_edge(Graph *, Vertex *, Vertex *, const void *);

/* Replaces the value of a Vertex. */
void graph_replace_vertex(Graph *, Vertex *, const void *);

/* Replaces the value of an Edge. */
void graph_replace_edge(Graph *, Edge *, const void *);

/* Returns a copy of the element in a Vertex. */
void *graph_vertex_value(const Graph *, const Vertex *);

/* Returns a copy of the element in an Edge. */
void *graph_edge_value(const Graph *, const Edge *);

/* Returns a reference to the element in a Vertex. */
const void *graph_vertex_value_ro(const Vertex *);

/* Returns a reference to the element in an Edge. */
const void *graph_edge_value_ro(const Edge *);

/* Returns a reference to every Vertex currently in the Graph in the same
order as they were inserted. */
Vertex **graph_vertices(const Graph *);

/* Returns a reference to every Edge currently in the Graph in the same
order as they were inserted. */
Edge **graph_edges(const Graph *);

/* Removes a Vertex of the Graph. */
void graph_remove_vertex(Graph *, Vertex *);

/* Removes an Edge of the Graph. */
void graph_remove_edge(Graph *, Edge *);

/* Returns the end Vertices of an Edge by reference. */
void graph_end_vertices(const Graph *, const Edge *, Vertex **, Vertex **);

/* Returns a list of the incident Edges of a Vertex. */
Edge **graph_incident_edges(const Graph *, const Vertex *);

/* Returns the opposite Vertex. */
Vertex *graph_opposite_vertex(const Graph *, const Vertex *, const Edge *);

/* Returns true if the Vertices are adjacent and false otherwise. */
bool graph_are_adjacent(const Graph *, const Vertex *, const Vertex *);

/* Returns the degree of a Vertex. */
int graph_vertex_degree(const Graph *, const Vertex *);

/* Returns the total number of Vertices currently in the Graph. */
int graph_number_of_vertices(const Graph *);

/* Returns the total number of Edges currently in the Graph. */
int graph_number_of_edges(const Graph *);

/* Prints a representation of the Graph. */
void graph_print_graph(const Graph *g, void (*)(const void *), void (*)(const void *));

/* Prints all the Vertices in the Graph. */
void graph_print_vertices(const Graph *, void (*)(const void *));

/* Prints all the Edges in the Graph. */
void graph_print_edges(const Graph *, void (*)(const void *));

#endif
