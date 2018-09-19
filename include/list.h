/* Victor Forbes - 9293394 */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct List List;
typedef struct Node Node;

/* O(1) - Creates an empty List. */
List *list_create(void *(*)(const void *), void (*)(void *));

/* O(N) - Clears every element from the List. */
void list_clear(List *);

/* O(N) - Destroys the List. */
void list_destroy(List *);

/* O(N) - Inserts an element at any position. */
Node *list_insert(List *, const void *, int);

/* O(1) - Pushes an element to the front of the List. */
Node *list_push_front(List *, const void *);

/* O(1) - Pushes an element to the back of the List. */
Node *list_push_back(List *, const void *);

/* O(1) - Erases a Node from the List. */
void list_erase(List *, Node *);

/* O(1) - Pops the element at the front of the List. */
void list_pop_front(List *);

/* O(1) - Pops the element at the back of the List. */
void list_pop_back(List *);

/* O(N) - Returns the Node containing the provided element. */
Node *list_find(const List *, const void *, int (*)(const void *, const void *));

/* O(N) - Returns the Node at the provided position. */
Node *list_at(const List *, int);

/* O(1) - Returns the element at the front of the List. */
Node *list_front(const List *);

/* O(1) - Returns the element at the back of the List. */
Node *list_back(const List *);

/* O(1) - Iterates forwards in the List. */
Node *list_next(const List *, const Node *);

/* O(1) - Iterates backwards in the List. */
Node *list_prev(const List *, const Node *);

/* O(1) - Returns the element inside a Node. */
void *list_get(const List *, const Node *);

/* O(1) - Returns the number of the elements in the List. */
int list_size(const List *);

/* O(1) - Returns true if the List is empty and false otherwise. */
bool list_empty(const List *);

#endif