#include "deque.h"
#include "queue.h"
#include "utils.h"

Queue *queue_create(void *(*copy)(const void *), void (*destroy)(void *)){
	return deque_create(copy, destroy);
}

void queue_clear(Queue *q){
	deque_clear(q);
}

void queue_destroy(Queue *q){
	deque_destroy(q);
}

void queue_push(Queue *q, const void *element){
	deque_push_back(q, element);
}

void queue_pop(Queue *q){
	deque_pop_front(q);
}

void *queue_front(const Queue *q){
	return deque_front(q);
}

int queue_size(const Queue *q){
	return deque_size(q);
}

bool queue_empty(const Queue *q){
	return deque_empty(q);
}
