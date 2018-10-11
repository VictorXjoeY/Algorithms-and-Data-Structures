/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"
#include "utils.h"

#define ROOT 0
#define LEFT(x) (2 * x + 1)
#define RIGHT(x) (2 * x + 2)
#define PARENT(x) ((x - 1) / 2)

struct PriorityQueueNode{
	void *element;
	int pos;
};

struct PriorityQueue{
	int (*compare)(const void *, const void *);
	void *(*copy)(const void *);
	void (*destroy)(void *);
	PriorityQueueNode **v;
	int size;
};

PriorityQueueNode *priority_queue_node_create(void *(*copy)(const void *), const void *element, int pos){
	PriorityQueueNode *n = (PriorityQueueNode *)malloc(sizeof(PriorityQueueNode));

	n->element = copy(element);
	n->pos = pos;

	return n;	
}

void priority_queue_node_destroy(void (*destroy)(void *), PriorityQueueNode *n){
	destroy(n->element);
	free(n);
}

PriorityQueue *priority_queue_create(void *(*copy)(const void *), void (*destroy)(void *), int (*compare)(const void *, const void *)){
	PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

	pq->compare = compare;
	pq->destroy = destroy;
	pq->copy = copy;
	pq->v = NULL;
	pq->size = 0;

	return pq;
}

void priority_queue_clear(PriorityQueue *pq){
	int i;

	for (i = 0; i < pq->size; i++){
		priority_queue_node_destroy(pq->destroy, pq->v[i]);
	}

	free(pq->v);

	pq->v = NULL;
	pq->size = 0;
}

void priority_queue_destroy(PriorityQueue *pq){
	priority_queue_clear(pq);
	free(pq->v);
	free(pq);
}

void priority_queue_bubble_up(PriorityQueue *pq, int pos){
	while (pos != ROOT && pq->compare(pq->v[PARENT(pos)]->element, pq->v[pos]->element) < 0){
		// Swapping nodes and positions.
		swap(pq->v + pos, pq->v + PARENT(pos), sizeof(PriorityQueueNode *));
		swap(&pq->v[pos]->pos, &pq->v[PARENT(pos)]->pos, sizeof(int));

		// Updating current position.
		pos = PARENT(pos);
	}
}

void priority_queue_bubble_down(PriorityQueue *pq, int pos){
	int child;

	while ((LEFT(pos) < pq->size && pq->compare(pq->v[pos]->element, pq->v[LEFT(pos)]->element) < 0) || (RIGHT(pos) < pq->size && pq->compare(pq->v[pos]->element, pq->v[RIGHT(pos)]->element) < 0)){
		if (LEFT(pos) < pq->size && RIGHT(pos) < pq->size){ // Has both children.
			if (pq->compare(pq->v[LEFT(pos)]->element, pq->v[RIGHT(pos)]->element) < 0){ // Right child is greater.
				child = RIGHT(pos);
			}
			else{ // Left child is greater.
				child = LEFT(pos);
			}
		}
		else if (LEFT(pos) < pq->size){ // Has only left child.
			child = LEFT(pos);
		}
		else{ // Has only right child.
			child = RIGHT(pos);
		}

		// Swapping nodes and positions.
		swap(pq->v + pos, pq->v + child, sizeof(PriorityQueueNode *));
		swap(&pq->v[pos]->pos, &pq->v[child]->pos, sizeof(int));

		// Updating current position.
		pos = child;
	}
}

void priority_queue_replace_key(PriorityQueue *pq, PriorityQueueNode *n, const void *element){
	if (pq->compare(element, n->element) < 0){ // New element is lesser.
		pq->destroy(n->element);
		n->element = pq->copy(element);
		priority_queue_bubble_down(pq, n->pos);
	}
	else{ // New element is greater.
		pq->destroy(n->element);
		n->element = pq->copy(element);
		priority_queue_bubble_up(pq, n->pos);
	}
}

PriorityQueueNode *priority_queue_push(PriorityQueue *pq, const void *element){
	PriorityQueueNode *n;

	// Inserting at the end.
	pq->v = (PriorityQueueNode **)realloc(pq->v, (pq->size + 1) * sizeof(PriorityQueueNode *));
	n = pq->v[pq->size] = priority_queue_node_create(pq->copy, element, pq->size);
	pq->size++;

	// Bubbling up.
	priority_queue_bubble_up(pq, pq->size - 1);

	return n;
}

void priority_queue_pop(PriorityQueue *pq){
	if (!priority_queue_empty(pq)){
		priority_queue_node_destroy(pq->destroy, pq->v[ROOT]);
		pq->size--;

		if (priority_queue_empty(pq)){ // Empty Priority Queue after pop.
			free(pq->v);
			pq->v = NULL;
		}
		else{
			// Swapping root with last element.
			swap(pq->v + ROOT, pq->v + pq->size, sizeof(PriorityQueueNode *));

			// Resing array.
			pq->v = (PriorityQueueNode **)realloc(pq->v, pq->size * sizeof(PriorityQueueNode *));

			// Bubbling down the new root.
			priority_queue_bubble_down(pq, ROOT);
		}
	}
}

void *priority_queue_top(const PriorityQueue *pq){
	if (!priority_queue_empty(pq)){
		return pq->copy(pq->v[ROOT]->element);
	}

	return NULL;
}

int priority_queue_size(const PriorityQueue *pq){
	return pq->size;
}

bool priority_queue_empty(const PriorityQueue *pq){
	return priority_queue_size(pq) == 0;
}