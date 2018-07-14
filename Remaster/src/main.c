#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "deque.h"
#include "stack.h"
#include "queue.h"

// Int copy.
void *int_copy(const void *a){
	int *b = (int *)malloc(sizeof(int)); // Allocates memory for an int.

	*b = *((int *)a); // Copies int.

	return b; // Returns the copy's address.
}

// Int destructor.
void int_destroy(void *a){
	free(a);
}

void deque_test(){
	Deque *d;
	int *p;
	int x;

	d = deque_create(&int_copy, &int_destroy);

	x = 3;
	deque_push_back(d, &x);
	x = 4;
	deque_push_back(d, &x);
	x = 7;
	deque_push_back(d, &x);

	p = (int *)deque_front(d);
	printf("Na frente do Deque tem %d\n", *p);
	int_destroy(p);
	
	p = (int *)deque_back(d);
	printf("Atras do Deque tem %d\n", *p);
	int_destroy(p);

	deque_pop_front(d);

	p = (int *)deque_front(d);
	printf("Agora na frente do Deque tem %d\n", *p);
	int_destroy(p);

	deque_destroy(d);
}

void stack_test(){
	Stack *s;
	int *p;
	int x;

	s = stack_create(&int_copy, &int_destroy);

	x = 3;
	stack_push(s, &x);
	x = 4;
	stack_push(s, &x);
	x = 7;
	stack_push(s, &x);

	p = stack_top(s);
	printf("No topo tem %d\n", *p);
	int_destroy(p);

	stack_pop(s);

	p = stack_top(s);
	printf("Agora no topo tem %d\n", *p);
	int_destroy(p);

	stack_destroy(s);
}

void queue_test(){
	Queue *q;
	int *p;
	int x;

	q = queue_create(&int_copy, &int_destroy);

	x = 3;
	queue_push(q, &x);
	x = 4;
	queue_push(q, &x);
	x = 7;
	queue_push(q, &x);

	p = queue_front(q);
	printf("Na frente tem %d\n", *p);
	int_destroy(p);

	queue_pop(q);

	p = queue_front(q);
	printf("Agora na frente tem %d\n", *p);
	int_destroy(p);

	queue_destroy(q);
}

int main(int argc, char *argv[]){
	List *l;
	Node *n;
	int x;

	l = list_create(&int_copy, &int_destroy);

	x = 3;
	list_push_back(l, &x);
	x = 4;
	list_push_back(l, &x);
	x = 7;
	list_push_back(l, &x);

	for (n = list_front(l); n != NULL; n = list_next(l, n)){
		printf("%d\n", *(int *)list_get(l, n));
	}

	list_destroy(l);

	// deque_test();
	// stack_test();
	// queue_test();

	return 0;
}