/* Victor Forbes - 9293394 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "utils.h"

typedef struct PriorityQueue PriorityQueue;
typedef struct PQNode PQNode;

/* Creates a Priority Queue for elements of size "element_size". */
PriorityQueue *priority_queue_new(int, int (*)(const void *, const void *));

/* Erases every element in the Priority Queue. */
void priority_queue_clear(PriorityQueue *);

/* Destroys the Priority Queue. */
void priority_queue_delete(PriorityQueue *);

/* Inserts an element in the Priority Queue. */
PQNode *priority_queue_push(PriorityQueue *, const void *);

/* Replaces the priority of an element in the Priority Queue. */
void priority_queue_replace_key(PriorityQueue *, const PQNode *, const void *);

/* Returns a copy of the element that is on the front of the Priority Queue. */
void *priority_queue_front(const PriorityQueue *);

/* Returns a reference to the element that is on the front of the Priority Queue. */
const void *priority_queue_front_ro(const PriorityQueue *);

/* Erases the back element from the Priority Queue. */
void priority_queue_pop(PriorityQueue *);

/* Returns true if the Priority Queue is empty and false otherwise. */
bool priority_queue_empty(const PriorityQueue *);

/* Returns the amount of elements currently in the Priority Queue. */
int priority_queue_size(const PriorityQueue *);

#endif