/* Victor Forbes - 9293394 */

#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "utils.h"

typedef struct Node Node;
typedef struct GraphList GraphList;

/* Creates a GraphList for elements of size "element_size". */
GraphList *list_create(int);

/* Erases every element in the GraphList. */
void list_clear(GraphList *);

/* Destroys the GraphList. */
void list_destroy(GraphList *);

/* Inserts an element in the GraphList and returns a reference to it. */
Node *list_insert(GraphList *, const void *);

/* Returns the a copy of the element in a Node. */
void *list_get_element(const GraphList *, const Node *);

/* Returns the read-only version of the element in a Node. */
const void *list_get_element_ro(const GraphList *, const Node *);

/* Iterates through the GraphList Nodes. Returns NULL if it reaches the end of the
GraphList. Returns the first Node if the last parameter is NULL. */
Node *list_get_next_node(const GraphList *, const Node *);

/* Removes a Node from the GraphList. */
void list_remove(GraphList *, Node *);

/* Returns true if the GraphList is empty and false otherwise. */
bool list_empty(const GraphList *);

/* Returns the amount of elements currently in the GraphList. */
int list_size(const GraphList *);

#endif