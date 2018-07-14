/* Victor Forbes - 9293394 */

#ifndef DEQUE_H
#define DEQUE_H

#include "utils.h"
#include "list.h"

typedef List Deque;

/* Creates an empty Deque. */
Deque *deque_create(void *(*)(const void *), void (*)(void *));

/* Clears every element from the Deque. */
void deque_clear(Deque *);

/* Destroys the Deque. */
void deque_destroy(Deque *);

/* Pushes an element to the front of the Deque. */
void deque_push_front(Deque *, const void *);

/* Pushes an element to the back of the Deque. */
void deque_push_back(Deque *, const void *);

/* Pops the element at the front of the Deque. */
void deque_pop_front(Deque *);

/* Pops the element at the back of the Deque. */
void deque_pop_back(Deque *);

/* Returns the element at the front of the Deque. */
void *deque_front(const Deque *);

/* Returns the element at the back of the Deque. */
void *deque_back(const Deque *);

/* Returns the number of the elements in the Deque. */
int deque_size(const Deque *);

/* Returns true if the Deque is empty and false otherwise. */
bool deque_empty(const Deque *);

#endif