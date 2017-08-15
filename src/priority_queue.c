/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "priority_queue.h"

#define parent(x) ((x - 1) / 2)
#define left_child(x) ((2 * x) + 1)
#define right_child(x) ((2 * x) + 2)

struct PQNode{
	void *element;
	int position;
};

struct PriorityQueue{
	PQNode **v;
	int size;
	int element_size;
	int (*compare)(const void *, const void *);
};

/* Creates a node. */
PQNode *priority_queue_node_new(const void *, int, int);

/* Erases a node from the Priority Queue. */
void priority_queue_node_delete(PQNode *);

PriorityQueue *priority_queue_new(int element_size, int (*compare)(const void *, const void *)){
	PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

	pq->element_size = element_size;
	pq->compare = compare;
	pq->v = NULL;
	pq->size = 0;

	return pq;
}

void priority_queue_clear(PriorityQueue *pq){
	int i;

	for (i = 0; i < pq->size; i++){
		priority_queue_node_delete(pq->v[i]);
	}

	free(pq->v);

	pq->v = NULL;
	pq->size = 0;
}

void priority_queue_delete(PriorityQueue *pq){
	priority_queue_clear(pq);
	free(pq->v);
	free(pq);
}

PQNode *priority_queue_push(PriorityQueue *pq, const void *element){
	int pos = pq->size;

	pq->size++;
	pq->v = (PQNode **)realloc(pq->v, pq->size * sizeof(PQNode *));
	pq->v[pos] = priority_queue_node_new(element, pq->element_size, pos);

	while (pos > 0 and pq->compare(pq->v[pos]->element, pq->v[parent(pos)]->element) > 0){
		pq->v[pos]->position = parent(pos);
		pq->v[parent(pos)]->position = pos;

		swap(pq->v, sizeof(PQNode *), pos, parent(pos));

		pos = parent(pos);
	}

	return pq->v[pos];
}

void *priority_queue_front(const PriorityQueue *pq){
	void *element = NULL;

	if (pq->size){
		element = malloc(pq->element_size);
		memcpy(element, pq->v[0]->element, pq->element_size);
	}

	return element;
}

const void *priority_queue_front_ro(const PriorityQueue *pq){
	return pq->size ? pq->v[0]->element : NULL;
}

void priority_queue_pop(PriorityQueue *pq){
	int pos, newpos;

	if (pq->size){		
		priority_queue_node_delete(pq->v[0]);
		pq->size--;

		if (pq->size){
			pq->v[0] = pq->v[pq->size];
			pq->v = (PQNode **)realloc(pq->v, pq->size * sizeof(PQNode *));

			newpos = pos = 0;

			do{
				pq->v[pos]->position = newpos;
				pq->v[newpos]->position = pos;
				
				swap(pq->v, sizeof(PQNode *), pos, newpos);

				pos = newpos;

				if (left_child(pos) < pq->size and pq->compare(pq->v[left_child(pos)]->element, pq->v[newpos]->element) > 0){
					newpos = left_child(pos);
				}

				if (right_child(pos) < pq->size and pq->compare(pq->v[right_child(pos)]->element, pq->v[newpos]->element) > 0){
					newpos = right_child(pos);
				}
			}while (newpos != pos);
		}
		else{
			free(pq->v);
			pq->v = NULL;
		}
	}
}

void priority_queue_replace_key(PriorityQueue *pq, const PQNode *ref, const void *element){
	int pos = ref->position;

	memcpy(pq->v[pos]->element, element, pq->element_size);

	while (parent(pos) >= 0 and pq->compare(pq->v[pos]->element, pq->v[parent(pos)]->element) > 0){
		pq->v[pos]->position = parent(pos);
		pq->v[parent(pos)]->position = pos;

		swap(pq->v, sizeof(PQNode *), pos, parent(pos));

		pos = parent(pos);
	}
}

bool priority_queue_empty(const PriorityQueue *pq){
	return !pq->size;
}

int priority_queue_size(const PriorityQueue *pq){
	return pq->size;
}

PQNode *priority_queue_node_new(const void *element, int element_size, int position){
	PQNode *n = (PQNode *)malloc(sizeof(PQNode));

	n->element = malloc(element_size);
	memcpy(n->element, element, element_size);

	n->position = position;

	return n;
}

void priority_queue_node_delete(PQNode *n){
	free(n->element);
	free(n);
}