/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "graph_list.h"

/* Nó da graph_lista. */
struct Node{
	Node *prev; // Ponteiro para o nó anterior.
	Node *next; // Ponteiro para o nó seguinte.
	void *element; // Valor armazenado no nó.
};

struct GraphList{
	Node *last; // Ponteiro para o último nó da graph_lista.
	int size; // Quantidade de nós/elementos na graph_lista.
	int element_size; // Tamanho de cada elemento armazenado em um nó.
};

/* Creates a node. */
Node *graph_list_node_create(const void *, int);

/* Erases a node from the GraphList. */
void graph_list_node_destroy(Node *);

GraphList *graph_list_create(int element_size){
	GraphList *l = (GraphList *)malloc(sizeof(GraphList));

	// Inicializando atributos da GraphLista.
	l->element_size = element_size;
	l->last = NULL;
	l->size = 0;

	return l;
}

void graph_list_clear(GraphList *l){
	Node *aux = l->last;

	// Enquanto houver nós.
	while (aux){
		aux = aux->prev;
		graph_list_node_destroy(l->last);
		l->last = aux;
	}
}

void graph_list_destroy(GraphList *l){
	if (l){
		// Removendo todos os nós.
		graph_list_clear(l);

		// Liberando a GraphLista.
		free(l);
	}
}

Node *graph_list_insert(GraphList *l, const void *element){
	// Se já houver algum nó na GraphLista.
	if (l->size){
		// Linkando o novo nó.
		l->last->next = graph_list_node_create(element, l->element_size);
		l->last->next->prev = l->last;

		// Atualizando o ponteiro para o último nó.
		l->last = l->last->next;
	}
	else{
		// Inicializando o ponteiro para o último nó.
		l->last = graph_list_node_create(element, l->element_size);
	}

	// Incrementando o contador de nós.
	l->size++;

	return l->last;
}

void *graph_list_get_element(const GraphList *l, const Node *n){
	// Alocando uma nova região da memória.
	void *element = malloc(l->element_size);

	// Armazenando o valor do nó nessa região.
	memcpy(element, n->element, l->element_size);

	// Retornando o endereço dessa região.
	return element;
}

const void *graph_list_get_element_ro(const GraphList *l, const Node *n){
	// Retornando o endereço da região da memória que armazena o valor do vértice.
	return n->element;
}

Node *graph_list_get_next_node(const GraphList *l, const Node *n){
	// Se o último parâmetro não for NULL.
	if (n){
		// Retorna o nó anterior a ele.
		return n->prev;
	}

	// Retorna o último nó da GraphLista.
	return l->last;
}

void graph_list_remove(GraphList *l, Node *n){
	// Linkando o nó anterior e o nó seguinte.
	if (n->prev and n->next){ // Se houver nó anterior e nó seguinte (nó intermediário).
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	else if (n->prev){ // Se houver apenas nó anterior (último nó).
		l->last = n->prev;
		n->prev->next = NULL;
	}
	else if (n->next){ // Se houver apenas nó seguinte (primeiro nó).
		n->next->prev = NULL;
	}
	else{ // Se não houver nem nó anterior nem nó seguinte (único nó).
		l->last = NULL;
	}

	// Apagando o nó.
	graph_list_node_destroy(n);

	// Decrementando o contador de nós.
	l->size--;
}

bool graph_list_empty(const GraphList *l){
	return !l->size;
}

int graph_list_size(const GraphList *l){
	return l->size;
}

Node *graph_list_node_create(const void *element, int element_size){
	Node *n = (Node *)malloc(sizeof(Node));

	// Armazenando o elemento no nó.
	n->element = malloc(element_size);
	memcpy(n->element, (void **)element, element_size);

	// Inicializando os ponteiros com NULL.
	n->next = NULL;
	n->prev = NULL;

	return n;
}

void graph_list_node_destroy(Node *n){
	// Liberando o elemento e o nó.
	free(n->element);
	free(n);
}