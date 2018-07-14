/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "stack.h"

typedef struct Node Node;

struct Node{
	void *element;
	Node *next;
	Node *prev;
};

struct Stack{
	Node *top;
	int size;
	int element_size;
};

/* Creates a node. */
Node *stack_node_create(const void *, int);

/* Erases a node from the Stack. */
void stack_node_destroy(Node *);

Stack *stack_create(int element_size){
	Stack *s = (Stack *)malloc(sizeof(Stack));

	s->element_size = element_size;
	s->top = NULL;
	s->size = 0;

	return s;
}

void stack_clear(Stack *s){
	while (s->size){
		stack_pop(s);
	}
}

void stack_destroy(Stack *s){
	stack_clear(s);
	free(s);
}

void stack_push(Stack *s, const void *element){
	if (s->size){
		s->top->next = stack_node_create(element, s->element_size);
		s->top->next->prev = s->top;
		s->top = s->top->next;
	}
	else{
		s->top = stack_node_create(element, s->element_size);
	}

	s->size++;
}

void *stack_top(const Stack *s){
	void *element = NULL;

	if (s->size){
		element = malloc(s->element_size);
		memcpy(element, s->top->element, s->element_size);
	}

	return element;
}

const void *stack_top_ro(const Stack *s){
	return s->size ? s->top->element : NULL;
}

void stack_pop(Stack *s){
	if (s->size){
		if (s->top->prev){
			s->top = s->top->prev;
			stack_node_destroy(s->top->next);
		}
		else{
			stack_node_destroy(s->top);
			s->top = NULL;
		}

		s->size--;
	}
}

bool stack_empty(const Stack *s){
	return !s->size;
}

int stack_size(const Stack *s){
	return s->size;
}

Node *stack_node_create(const void *element, int element_size){
	Node *n = (Node *)malloc(sizeof(Node));

	n->element = malloc(element_size);
	memcpy(n->element, element, element_size);

	n->next = NULL;
	n->prev = NULL;

	return n;
}

void stack_node_destroy(Node *n){
	free(n->element);
	free(n);
}