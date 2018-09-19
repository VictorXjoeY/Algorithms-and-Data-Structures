/* Victor Forbes - 9293394 */

#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "utils.h"

typedef struct Node Node;
typedef struct GraphList GraphList;

/* Creates a GraphList for elements of size "element_size". */
GraphList *graph_list_create(int);

/* Erases every element in the GraphList. */
void graph_list_clear(GraphList *);

/* Destroys the GraphList. */
void graph_list_destroy(GraphList *);

/* Inserts an element in the GraphList and returns a reference to it. */
Node *graph_list_insert(GraphList *, const void *);

/* Returns the a copy of the element in a Node. */
void *graph_list_get_element(const GraphList *, const Node *);

/* Returns the read-only version of the element in a Node. */
const void *graph_list_get_element_ro(const GraphList *, const Node *);

/* Iterates through the GraphList Nodes. Returns NULL if it reaches the end of the
GraphList. Returns the first Node if the last parameter is NULL. */
Node *graph_list_get_next_node(const GraphList *, const Node *);

/* Removes a Node from the GraphList. */
void graph_list_remove(GraphList *, Node *);

/* Returns true if the GraphList is empty and false otherwise. */
bool graph_list_empty(const GraphList *);

/* Returns the amount of elements currently in the GraphList. */
int graph_list_size(const GraphList *);

#endif