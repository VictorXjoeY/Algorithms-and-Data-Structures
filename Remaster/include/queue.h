/* Victor Forbes - 9293394 */

#ifndef QUEUE_H
#define QUEUE_H

#include "utils.h"
#include "deque.h"

typedef Deque Queue;

/* Creates an empty Queue. */
Queue *queue_create(void *(*)(const void *), void (*)(void *));

/* Clears every element from the Queue. */
void queue_clear(Queue *);

/* Destroys the Queue. */
void queue_destroy(Queue *);

/* Pushes an element to the back of the Queue. */
void queue_push(Queue *, const void *);

/* Pops the element at the front of the Queue. */
void queue_pop(Queue *);

/* Returns the element at the front of the Queue. */
void *queue_front(const Queue *);

/* Returns the number of the elements in the Queue. */
int queue_size(const Queue *);

/* Returns true if the Queue is empty and false otherwise. */
bool queue_empty(const Queue *);

#endif