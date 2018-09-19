/* Victor Forbes - 9293394 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

typedef struct PriorityQueue PriorityQueue;
typedef struct PriorityQueueNode PriorityQueueNode;

/* O(1) - Creates an empty Priority Queue. */
PriorityQueue *priority_queue_create(void *(*)(const void *), void (*)(void *), int (*)(const void *, const void *));

/* O(N) - Clears every element from the Priority Queue. */
void priority_queue_clear(PriorityQueue *);

/* O(N) - Destroys the Priority Queue. */
void priority_queue_destroy(PriorityQueue *);

/* O(Log(N)) - Inserts an element in the Priority Queue. */
PriorityQueueNode *priority_queue_push(PriorityQueue *, const void *);

/* O(Log(N)) - Replaces the element at given node in the Priority Queue. */
void priority_queue_replace_key(PriorityQueue *, PriorityQueueNode *, const void *);

/* O(Log(N)) - Pops the element at the top of the Priority Queue. */
void priority_queue_pop(PriorityQueue *);

/* O(1) - Returns the maximum element in the Priority Queue. */
void *priority_queue_top(const PriorityQueue *);

/* O(1) - Returns the number of the elements in the Priority Queue. */
int priority_queue_size(const PriorityQueue *);

/* O(1) - Returns true if the Priority Queue is empty and false otherwise. */
bool priority_queue_empty(const PriorityQueue *);

#endif