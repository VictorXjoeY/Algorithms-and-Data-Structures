/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct Node{
	Node *prev, *next;
	void *element;
};

struct List{
	void *(*copy)(const void *);
	void (*destroy)(void *);
	Node *front, *back;
	int size;
};

List *list_create(void *(*copy)(const void *), void (*destroy)(void *)){
	List *l = (List *)malloc(sizeof(List));

	l->front = l->back = NULL;
	l->destroy = destroy;
	l->copy = copy;
	l->size = 0;

	return l;
}

void list_clear(List *l){
	while (!list_empty(l)){
		list_pop_back(l);
	}
}

void list_destroy(List *l){
	list_clear(l);
	free(l);
}

/* Creates a Node containing a copy of the provided element. */
Node *node_create(void *(*copy)(const void *), const void *element){
	Node *n = (Node *)malloc(sizeof(Node));

	n->prev = n->next = NULL;
	n->element = copy(element);

	return n;
}

/* Destroys a given Node. */
void node_destroy(void (*destroy)(void *), Node *n){
	destroy(n->element);
	free(n);
}

Node *list_insert(List *l, const void *element, int pos){
	Node *u, *v;

	if (0 <= pos && pos <= list_size(l)){
		if (pos == 0){
			return list_push_front(l, element);
		}
		
		if (pos == list_size(l)){
			return list_push_back(l, element);
		}

		u = node_create(l->copy, element);
		v = list_at(l, pos - 1);

		u->prev = v;
		u->next = v->next;

		v->next = u;
		u->next->prev = u;

		return u;
	}

	return NULL;
}

Node *list_push_front(List *l, const void *element){
	if (list_empty(l)){
		l->front = l->back = node_create(l->copy, element);
	}
	else{
		l->front->prev = node_create(l->copy, element);
		l->front->prev->next = l->front;
		l->front = l->front->prev;
	}

	l->size++;

	return l->front;
}

Node *list_push_back(List *l, const void *element){
	if (list_empty(l)){
		l->front = l->back = node_create(l->copy, element);
	}
	else{
		l->back->next = node_create(l->copy, element);
		l->back->next->prev = l->back;
		l->back = l->back->next;
	}

	l->size++;

	return l->back;
}

void list_erase(List *l, Node *n){
	if (l->front == n){
		list_pop_front(l);
	}
	else if (l->back == n){
		list_pop_back(l);
	}
	else{
		n->prev->next = n->next;
		n->next->prev = n->prev;
		node_destroy(l->destroy, n);
	}
}

void list_pop_front(List *l){
	if (list_size(l) == 1){
		node_destroy(l->destroy, l->front);
		l->front = l->back = NULL;
	}
	else{
		l->front = l->front->next;
		node_destroy(l->destroy, l->front->prev);
		l->front->prev = NULL;
	}

	l->size--;
}

void list_pop_back(List *l){
	if (list_size(l) == 1){
		node_destroy(l->destroy, l->back);
		l->front = l->back = NULL;
	}
	else{
		l->back = l->back->prev;
		node_destroy(l->destroy, l->back->next);
		l->back->next = NULL;
	}

	l->size--;
}

Node *list_find(const List *l, const void *element, int (*compare)(const void *, const void *)){
	Node *n = l->front;

	while (n){
		if (!compare(n->element, element)){
			return n;
		}

		n = n->next;
	}

	return NULL;
}

int list_count(const List *l, const void *element, int (*compare)(const void *, const void *)){
	Node *n = l->front;
	int c = 0;

	while (n){
		if (!compare(n->element, element)){
			c++;
		}

		n = n->next;
	}

	return c;
}

Node *list_at(const List *l, int pos){
	Node *n = l->front;

	if (0 <= pos && pos < list_size(l)){
		while (pos){
			n = n->next;
			pos--;
		}

		return n;
	}

	return NULL;
}

Node *list_front(const List *l){
	return l->front;
}

Node *list_back(const List *l){
	return l->back;
}

Node *list_next(const List *l, const Node *n){
	return n->next;
}

Node *list_prev(const List *l, const Node *n){
	return n->prev;
}

void *list_get(const List *l, const Node *n){
	return l->copy(n->element);
}

int list_size(const List *l){
	return l->size;
}

bool list_empty(const List *l){
	return list_size(l) == 0;
}
