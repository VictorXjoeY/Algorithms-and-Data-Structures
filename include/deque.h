/* Victor Forbes - 9293394 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include "list.h"

typedef List Deque;

/* O(1) - Creates an empty Deque. */
Deque *deque_create(void *(*)(const void *), void (*)(void *));

/* O(N) - Clears every element from the Deque. */
void deque_clear(Deque *);

/* O(N) - Destroys the Deque. */
void deque_destroy(Deque *);

/* O(1) - Pushes an element to the front of the Deque. */
void deque_push_front(Deque *, const void *);

/* O(1) - Pushes an element to the back of the Deque. */
void deque_push_back(Deque *, const void *);

/* O(1) - Pops the element at the front of the Deque. */
void deque_pop_front(Deque *);

/* O(1) - Pops the element at the back of the Deque. */
void deque_pop_back(Deque *);

/* O(1) - Returns the element at the front of the Deque. */
void *deque_front(const Deque *);

/* O(1) - Returns the element at the back of the Deque. */
void *deque_back(const Deque *);

/* O(1) - Returns the number of the elements in the Deque. */
int deque_size(const Deque *);

/* O(1) - Returns true if the Deque is empty and false otherwise. */
bool deque_empty(const Deque *);

#endif