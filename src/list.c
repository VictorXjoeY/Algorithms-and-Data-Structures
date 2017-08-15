/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "list.h"

// Nó da lista.
struct Node{
	Node *previous; // Ponteiro para o nó anterior.
	Node *next; // Ponteiro para o nó seguinte.
	void *element; // Valor armazenado no nó.
};

struct List{
	Node *last; // Ponteiro para o último nó da lista.
	int size; // Quantidade de nós/elementos na lista.
	int element_size; // Tamanho de cada elemento armazenado em um nó.
};

/* Creates a node. */
Node *list_node_new(const void *, int);

/* Erases a node from the List. */
void list_node_delete(Node *);

List *list_new(int element_size){
	List *l = (List *)malloc(sizeof(List));

	// Inicializando atributos da Lista.
	l->element_size = element_size;
	l->last = NULL;
	l->size = 0;

	return l;
}

void list_clear(List *l){
	Node *aux = l->last;

	// Enquanto houver nós.
	while (aux){
		aux = aux->previous;
		list_node_delete(l->last);
		l->last = aux;
	}
}

void list_delete(List *l){
	if (l){
		// Removendo todos os nós.
		list_clear(l);

		// Liberando a Lista.
		free(l);
	}
}

Node *list_insert(List *l, const void *element){
	// Se já houver algum nó na Lista.
	if (l->size){
		// Linkando o novo nó.
		l->last->next = list_node_new(element, l->element_size);
		l->last->next->previous = l->last;

		// Atualizando o ponteiro para o último nó.
		l->last = l->last->next;
	}
	else{
		// Inicializando o ponteiro para o último nó.
		l->last = list_node_new(element, l->element_size);
	}

	// Incrementando o contador de nós.
	l->size++;

	return l->last;
}

void *list_get_element(const List *l, const Node *n){
	// Alocando uma nova região da memória.
	void *element = malloc(l->element_size);

	// Armazenando o valor do nó nessa região.
	memcpy(element, n->element, l->element_size);

	// Retornando o endereço dessa região.
	return element;
}

const void *list_get_element_ro(const List *l, const Node *n){
	// Retornando o endereço da região da memória que armazena o valor do vértice.
	return n->element;
}

Node *list_get_next_node(const List *l, const Node *n){
	// Se o último parâmetro não for NULL.
	if (n){
		// Retorna o nó anterior a ele.
		return n->previous;
	}

	// Retorna o último nó da Lista.
	return l->last;
}

void list_remove(List *l, Node *n){
	// Linkando o nó anterior e o nó seguinte.
	if (n->previous and n->next){ // Se houver nó anterior e nó seguinte (nó intermediário).
		n->previous->next = n->next;
		n->next->previous = n->previous;
	}
	else if (n->previous){ // Se houver apenas nó anterior (último nó).
		l->last = n->previous;
		n->previous->next = NULL;
	}
	else if (n->next){ // Se houver apenas nó seguinte (primeiro nó).
		n->next->previous = NULL;
	}
	else{ // Se não houver nem nó anterior nem nó seguinte (único nó).
		l->last = NULL;
	}

	// Apagando o nó.
	list_node_delete(n);

	// Decrementando o contador de nós.
	l->size--;
}

bool list_empty(const List *l){
	return !l->size;
}

int list_size(const List *l){
	return l->size;
}

Node *list_node_new(const void *element, int element_size){
	Node *n = (Node *)malloc(sizeof(Node));

	// Armazenando o elemento no nó.
	n->element = malloc(element_size);
	memcpy(n->element, (void **)element, element_size);

	// Inicializando os ponteiros com NULL.
	n->next = NULL;
	n->previous = NULL;

	return n;
}

void list_node_delete(Node *n){
	// Liberando o elemento e o nó.
	free(n->element);
	free(n);
}