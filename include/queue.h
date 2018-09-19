/* Victor Forbes - 9293394 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "deque.h"

typedef Deque Queue;

/* O(1) - Creates an empty Queue. */
Queue *queue_create(void *(*)(const void *), void (*)(void *));

/* O(N) - Clears every element from the Queue. */
void queue_clear(Queue *);

/* O(N) - Destroys the Queue. */
void queue_destroy(Queue *);

/* O(1) - Pushes an element to the back of the Queue. */
void queue_push(Queue *, const void *);

/* O(1) - Pops the element at the front of the Queue. */
void queue_pop(Queue *);

/* O(1) - Returns the element at the front of the Queue. */
void *queue_front(const Queue *);

/* O(1) - Returns the number of the elements in the Queue. */
int queue_size(const Queue *);

/* O(1) - Returns true if the Queue is empty and false otherwise. */
bool queue_empty(const Queue *);

#endif