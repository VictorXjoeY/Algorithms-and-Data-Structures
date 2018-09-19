#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "deque.h"
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"

void *int_copy(const void *a){
	int *b = (int *)malloc(sizeof(int)); // Allocates memory for an int.
	*b = *((int *)a); // Copies int.
	return b; // Returns the copy's address.
}

void int_destroy(void *a){
	free(a);
}

int int_compare(const void *a, const void *b){
	return *((int *)a) - *((int *)b);
}

void list_test(){
	int *p, x;
	List *l;

	l = list_create(&int_copy, &int_destroy);

	x = 3;
	list_push_back(l, &x);
	x = 4;
	list_push_back(l, &x);
	x = 7;
	list_push_back(l, &x);

	p = (int *)list_get(l, list_front(l));
	printf("Na frente da List tem %d\n", *p);
	int_destroy(p);
	
	p = (int *)list_get(l, list_back(l));
	printf("Atras da List tem %d\n", *p);
	int_destroy(p);

	list_pop_front(l);

	p = (int *)list_get(l, list_front(l));
	printf("Agora na frente da List tem %d\n", *p);
	int_destroy(p);

	list_destroy(l);
}

void deque_test(){
	int *p, x;
	Deque *d;

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

void queue_test(){
	int *p, x;
	Queue *q;

	q = queue_create(&int_copy, &int_destroy);

	x = 3;
	queue_push(q, &x);
	x = 4;
	queue_push(q, &x);
	x = 7;
	queue_push(q, &x);

	p = queue_front(q);
	printf("Na frente da Queue tem %d\n", *p);
	int_destroy(p);

	queue_pop(q);

	p = queue_front(q);
	printf("Agora na frente da Queue tem %d\n", *p);
	int_destroy(p);

	queue_destroy(q);
}

void stack_test(){
	int *p, x;
	Stack *s;

	s = stack_create(&int_copy, &int_destroy);

	x = 3;
	stack_push(s, &x);
	x = 4;
	stack_push(s, &x);
	x = 7;
	stack_push(s, &x);

	p = stack_top(s);
	printf("No topo da Stack tem %d\n", *p);
	int_destroy(p);

	stack_pop(s);

	p = stack_top(s);
	printf("Agora no topo da Stack tem %d\n", *p);
	int_destroy(p);

	stack_destroy(s);
}

void priority_queue_test(){
	int *v, *p, n, i;
	PriorityQueue *pq;

	pq = priority_queue_create(int_copy, int_destroy, int_compare);

	// Randomizing array.
	n = 1000;
	v = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++){
		v[i] = rand() % 100;
	}

	// Inserting in random order.
	for (i = 0; i < n; i++){
		// printf("%d ", v[i]);
		priority_queue_push(pq, v + i);
	}

	// printf("\n");

	qsort(v, n, sizeof(int), int_compare);

	for (i = n - 1; i >= 0; i--){
		p = priority_queue_top(pq);
		priority_queue_pop(pq);

		// printf("%d ", *p);

		if (v[i] != *p){
			printf("ERROR\n");
		}

		int_destroy(p);
	}

	// printf("\n");

	free(v);
	priority_queue_destroy(pq);
}

int main(int argc, char *argv[]){
	// list_test();
	// deque_test();
	// queue_test();
	// stack_test();
	priority_queue_test();

	return 0;
}