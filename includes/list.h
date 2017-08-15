/* Victor Forbes - 9293394 */

#ifndef LIST_H
#define LIST_H

#include "utils.h"

typedef struct Node Node;
typedef struct List List;

/* Creates a List for elements of size "element_size". */
List *list_new(int);

/* Erases every element in the List. */
void list_clear(List *);

/* Destroys the List. */
void list_delete(List *);

/* Inserts an element in the List and returns a reference to it. */
Node *list_insert(List *, const void *);

/* Returns the a copy of the element in a Node. */
void *list_get_element(const List *, const Node *);

/* Returns the read-only version of the element in a Node. */
const void *list_get_element_ro(const List *, const Node *);

/* Iterates through the List Nodes. Returns NULL if it reaches the end of the
List. Returns the first Node if the last parameter is NULL. */
Node *list_get_next_node(const List *, const Node *);

/* Removes a Node from the List. */
void list_remove(List *, Node *);

/* Returns true if the List is empty and false otherwise. */
bool list_empty(const List *);

/* Returns the amount of elements currently in the List. */
int list_size(const List *);

#endif