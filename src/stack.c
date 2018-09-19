#include <stdbool.h>
#include "deque.h"
#include "stack.h"

Stack *stack_create(void *(*copy)(const void *), void (*destroy)(void *)){
	return deque_create(copy, destroy);
}

void stack_clear(Stack *s){
	deque_clear(s);
}

void stack_destroy(Stack *s){
	deque_destroy(s);
}

void stack_push(Stack *s, const void *element){
	deque_push_back(s, element);
}

void stack_pop(Stack *s){
	deque_pop_back(s);
}

void *stack_top(const Stack *s){
	return deque_back(s);
}

int stack_size(const Stack *s){
	return deque_size(s);
}

bool stack_empty(const Stack *s){
	return deque_empty(s);
}
