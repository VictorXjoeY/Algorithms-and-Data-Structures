/* Victor Forbes - 9293394 */

#ifndef LIST_H
#define LIST_H

#include "utils.h"

typedef struct List List;
typedef struct Node Node;

/* Creates an empty List. */
List *list_create(void *(*)(const void *), void (*)(void *));

/* Clears every element from the List. */
void list_clear(List *);

/* Destroys the List. */
void list_destroy(List *);

/* Inserts an element at any position. */
Node *list_insert(List *, void *, int);

/* Pushes an element to the front of the List. */
Node *list_push_front(List *, const void *);

/* Pushes an element to the back of the List. */
Node *list_push_back(List *, const void *);

/* Erases a Node from the List. */
void list_erase(List *, Node *);

/* Pops the element at the front of the List. */
void list_pop_front(List *);

/* Pops the element at the back of the List. */
void list_pop_back(List *);

/* Returns the Node containing the provided element. */
Node *list_find(const List *, const void *, int (*)(const void *, const void *));

/* Returns the Node at the provided position. */
Node *list_at(const List *, int);

/* Returns the element at the front of the List. */
Node *list_front(const List *);

/* Returns the element at the back of the List. */
Node *list_back(const List *);

/* Iterates forwards in the List. */
Node *list_next(const List *, const Node *);

/* Iterates backwards in the List. */
Node *list_prev(const List *, const Node *);

/* Returns the element inside a Node. */
void *list_get(const List *, const Node *);

/* Returns the number of the elements in the List. */
int list_size(const List *);

/* Returns true if the List is empty and false otherwise. */
bool list_empty(const List *);

#endif