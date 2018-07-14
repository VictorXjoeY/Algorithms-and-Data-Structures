/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "list.h"

struct Node{
	Node *prev; // Ponteiro para o nó anterior.
	Node *next; // Ponteiro para o nó seguinte.
	void *element; // Valor armazenado no nó.
};

struct List{
	Node *front; // Ponteiro para o primeiro nó da lista.
	Node *back; // Ponteiro para o último nó da lista.
	int size; // Quantidade de nós na lista.
	int element_size; // Tamanho de cada elemento armazenado em um nó.
};

/* Creates a node. */
Node *list_node_create(const void *, int);

/* Destroys a node from the List. */
void list_node_destroy(Node *);

List *list_create(int element_size){
	List *l = (List *)malloc(sizeof(List));

	// Inicializando atributos da Lista.
	l->element_size = element_size;
	l->front = l->back = NULL;
	l->size = 0;

	return l;
}

void list_clear(List *l){
	Node *aux = l->back;

	// Enquanto houver nós.
	while (aux){
		aux = aux->prev;
		list_node_destroy(l->back);
		l->back = aux;
	}
}

void list_destroy(List *l){
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
		l->back->next = list_node_create(element, l->element_size);
		l->back->next->prev = l->back;

		// Atualizando o ponteiro para o último nó.
		l->back = l->back->next;
	}
	else{
		// Inicializando o ponteiro para o último nó.
		l->front = l->back = list_node_create(element, l->element_size);
	}

	// Incrementando o contador de nós.
	l->size++;

	return l->back;
}

void *list_get_element(const List *l, const Node *n){
	// Alocando uma nova região da memória.
	void *element = malloc(l->element_size);

	// Armazenando o valor do nó nessa região.
	memcpy(element, n->element, l->element_size);

	// Retornando o endereço dessa região.
	return element;
}

Node *list_get_next_node(const List *l, const Node *n){
	// Se o último parâmetro não for NULL.
	if (n){
		// Retorna o nó anterior a ele.
		return n->prev;
	}

	// Retorna o último nó da Lista.
	return l->back;
}

void list_remove(List *l, Node *n){
	// Linkando o nó anterior e o nó seguinte.
	if (n->prev and n->next){ // Se houver nó anterior e nó seguinte (nó intermediário).
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	else if (n->prev){ // Se houver apenas nó anterior (último nó).
		l->back = n->prev;
		n->prev->next = NULL;
	}
	else if (n->next){ // Se houver apenas nó seguinte (primeiro nó).
		n->next->prev = NULL;
	}
	else{ // Se não houver nem nó anterior nem nó seguinte (único nó).
		l->back = NULL;
	}

	// Apagando o nó.
	list_node_destroy(n);

	// Decrementando o contador de nós.
	l->size--;
}

bool list_empty(const List *l){
	return !l->size;
}

int list_size(const List *l){
	return l->size;
}

Node *list_node_create(const void *element, int element_size){
	Node *n = (Node *)malloc(sizeof(Node));

	// Armazenando o elemento no nó.
	n->element = malloc(element_size);
	memcpy(n->element, (void **)element, element_size);

	// Inicializando os ponteiros com NULL.
	n->next = NULL;
	n->prev = NULL;

	return n;
}

void list_node_destroy(Node *n){
	// Liberando o elemento e o nó.
	free(n->element);
	free(n);
}