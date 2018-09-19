#include <stdbool.h>
#include "deque.h"
#include "list.h"

Deque *deque_create(void *(*copy)(const void *), void (*destroy)(void *)){
	return list_create(copy, destroy);
}

void deque_clear(Deque *d){
	list_clear(d);
}

void deque_destroy(Deque *d){
	list_destroy(d);
}

void deque_push_front(Deque *d, const void *element){
	list_push_front(d, element);
}

void deque_push_back(Deque *d, const void *element){
	list_push_back(d, element);
}

void deque_pop_front(Deque *d){
	list_pop_front(d);
}

void deque_pop_back(Deque *d){
	list_pop_back(d);
}

void *deque_front(const Deque *d){
	return list_get(d, list_front(d));
}

void *deque_back(const Deque *d){
	return list_get(d, list_back(d));
}

int deque_size(const Deque *d){
	return list_size(d);
}

bool deque_empty(const Deque *d){
	return list_empty(d);
}
