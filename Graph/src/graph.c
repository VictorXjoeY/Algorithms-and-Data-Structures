/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "graph_list.h"
#include "graph.h"

// Vértice.
struct Vertex{
	int id; // Id do vértice.
	GraphList *adjacent; // GraphLista de arestas incidentes.
	Vertex *prev; // Ponteiro para o vértice anterior.
	Vertex *next; // Ponteiro para o próximo vértice.
	void *value; // Valor armazenado no vértice.
};

// Aresta.
struct Edge{
	int id; // Id da aresta.
	Vertex *vertex1; // Vértice final 1.
	Vertex *vertex2; // Vértice final 2.
	GraphList *reference_list1; // GraphLista de adjacência do primeiro vértice final na qual sua referência se encontra.
	GraphList *reference_list2; // GraphLista de adjacência do segundo vértice final na qual sua referência se encontra.
	Node *reference1; // Referência direta para o nó da lista do primeiro vértice.
	Node *reference2; // Referência direta para o nó da lista do segundo vértice.
	Edge *prev; // Ponteiro para a aresta anterior.
	Edge *next; // Ponteiro para a próxima aresta.
	void *value; // Valor armazenado na aresta.
};

// Grafo.
struct Graph{
	Vertex *first_vertex; // Ponteiro para o primeiro vértice adicionado à lista de vértices.
	Vertex *last_vertex; // Ponteiro para o último vértice adicionado à lista de vértices.
	Edge *first_edge; // Ponteiro para a primeira aresta adicionada à lista de arestas.
	Edge *last_edge; // Ponteiro para a última aresta adicionada à lista de arestas.
	int vertex_value_size; // Tamanho do valor armazenado em cada vértice.
	int edge_value_size; // Tamanho do valor armazenado em cada aresta.
	int vertex_id; // Variável utilizada para gerar automaticamente os Ids dos vértices.
	int edge_id; // Variável utilizada para gerar automaticamente os Ids das arestas.
	int n; // Quantidade de vértices no Grafo.
	int m; // Quantidade de arestas no Grafo.
};

/* Cria um novo Vértice. */
Vertex *graph_vertex_new(int, const void *, int);

/* Cria uma nova Aresta. */
Edge *graph_edge_new(int, Vertex *, Vertex *, const void *, int);

Graph *graph_new(int vertex_value_size, int edge_value_size){
	Graph *g = (Graph *)malloc(sizeof(Graph));

	// Gravando os tamanhos dos valores armazenados nos vértices/arestas.
	g->vertex_value_size = vertex_value_size;
	g->edge_value_size = edge_value_size;

	// Inicializando atributos do Grafo.
	g->first_vertex = NULL;
	g->last_vertex = NULL;
	g->first_edge = NULL;
	g->last_edge = NULL;
	g->vertex_id = 0;
	g->edge_id = 0;
	g->n = 0;
	g->m = 0;

	return g;
}

void graph_clear(Graph *g){
	Vertex *aux_vertex = g->last_vertex;
	Edge *aux_edge = g->last_edge;

	// Removendo arestas.
	while (aux_edge){
		aux_edge = aux_edge->prev;
		graph_remove_edge(g, g->last_edge);
		g->last_edge = aux_edge;
	}

	// Removendo vértices.
	while (aux_vertex){
		aux_vertex = aux_vertex->prev;
		graph_remove_vertex(g, g->last_vertex);
		g->last_vertex = aux_vertex;
	}
}

void graph_delete(Graph *g){
	// Removendo vértices e arestas.
	graph_clear(g);

	// Liberando memória alocada para armazenar o Grafo.
	free(g);
}

Vertex *graph_insert_vertex(Graph *g, const void *o){
	// Gerando um novo id.
	g->vertex_id++;

	// Se já houver algum vértice no Grafo.
	if (g->n){
		// Linkando o novo vértice.
		g->last_vertex->next = graph_vertex_new(g->vertex_id, o, g->vertex_value_size);
		g->last_vertex->next->prev = g->last_vertex;

		// Atualizando o ponteiro para o último vértice.
		g->last_vertex = g->last_vertex->next;
	}
	else{
		// Inicializando os ponteiros para o primeiro e último vértice.
		g->first_vertex = graph_vertex_new(g->vertex_id, o, g->vertex_value_size);
		g->last_vertex = g->first_vertex;
	}

	// Incrementando contador de vértices.
	g->n++;

	return g->last_vertex;
}

Edge *graph_insert_edge(Graph *g, Vertex *v, Vertex *w, const void *o){
	// Gerando um novo id.
	g->edge_id++;

	// Se já houver alguma aresta no Grafo.
	if (g->m){
		// Linkando a nova aresta.
		g->last_edge->next = graph_edge_new(g->edge_id, v, w, o, g->edge_value_size);
		g->last_edge->next->prev = g->last_edge;

		// Atualizando o ponteiro para a última aresta.
		g->last_edge = g->last_edge->next;
	}
	else{
		// Inicializando os ponteiros para a primeira e última aresta.
		g->first_edge = graph_edge_new(g->edge_id, v, w, o, g->edge_value_size);
		g->last_edge = g->first_edge;
	}

	// Incrementando contador de arestas.
	g->m++;

	return g->last_edge;
}

void graph_replace_vertex(Graph *g, Vertex *v, const void *x){
	// Sobrescrevendo o antigo valor armazenado no vértice v.
	memcpy(v->value, x, g->vertex_value_size);
}

void graph_replace_edge(Graph *g, Edge *e, const void *x){
	// Sobrescrevendo o antigo valor armazenado na aresta e.
	memcpy(e->value, x, g->edge_value_size);
}

void *graph_vertex_value(const Graph *g, const Vertex *v){
	// Alocando uma nova região de memória.
	void *element = malloc(g->vertex_value_size);

	// Armazenando o valor do vértice nessa região.
	memcpy(element, v->value, g->vertex_value_size);

	// Retornando o endereço dessa região.
	return element;
}

void *graph_edge_value(const Graph *g, const Edge *e){
	// Alocando uma nova região de memória.
	void *element = malloc(g->edge_value_size);

	// Armazenando o valor da aresta nessa região.
	memcpy(element, e->value, g->edge_value_size);

	// Retornando o endereço dessa região.
	return element;
}

const void *graph_vertex_value_ro(const Vertex *v){
	// Retornando o endereço da região da memória que armazena o valor do vértice.
	return v->value;
}

const void *graph_edge_value_ro(const Edge *e){
	// Retornando o endereço da região da memória que armazena o valor da aresta.
	return e->value;
}

Vertex **graph_vertices(const Graph *g){
	Vertex **v = NULL;
	int i;

	// Se houver algum vértice.
	if (g->n){
		// Alocando um vetor de vértices.
		v = (Vertex **)malloc(g->n * sizeof(Vertex *));

		// Inicializando o primeiro elemento do vetor.
		v[0] = g->first_vertex;

		// Armazenando os vértices.
		for (i = 1; i < g->n; i++){
			v[i] = v[i - 1]->next;
		}
	}

	return v;
}


Edge **graph_edges(const Graph *g){
	Edge **e = NULL;
	int i;

	// Se houver alguma aresta.
	if (g->m){
		// Alocando um vetor de arestas.
		e = (Edge **)malloc(g->m * sizeof(Edge *));

		// Inicializando o primeiro elemento do vetor.
		e[0] = g->first_edge;

		// Armazenando as arestas.
		for (i = 1; i < g->m; i++){
			e[i] = e[i - 1]->next;
		}
	}

	return e;
}

void graph_remove_vertex(Graph *g, Vertex *v){
	Node *next = graph_list_get_next_node(v->adjacent, NULL);
	Node *prev;

	// Enquanto tiver aresta.
	while (next){
		prev = next;
		next = graph_list_get_next_node(v->adjacent, next);

		// Removendo a aresta.
		graph_remove_edge(g, *((Edge **)graph_list_get_element_ro(v->adjacent, prev)));
	}

	// Deletando a lista de arestas incidentes.
	graph_list_destroy(v->adjacent);

	// Linkando o vértice anterior e o vértice seguinte.
	if (v->prev and v->next){ // Se houver vértice anterior e vértice seguinte (vértice intermediário).
		v->prev->next = v->next;
		v->next->prev = v->prev;
	}
	else if (v->prev){ // Se houver apenas vértice anterior (último vértice).
		g->last_vertex = v->prev;
		v->prev->next = NULL;
	}
	else if (v->next){ // Se houver apenas vértice seguinte (primeiro vértice).
		g->first_vertex = v->next;
		v->next->prev = NULL;
	}
	else{ // Se não houver nem vértice anterior nem vértice seguinte (único vértice).
		g->first_vertex = NULL;
		g->last_vertex = NULL;
	}

	// Liberando memória alocada para armazenar o valor e o vértice.
	free(v->value);
	free(v);

	// Decrementando o contador de vértices.
	g->n--;
}

void graph_remove_edge(Graph *g, Edge *e){
	// Removendo as referências para a aresta nas listas de adjacência dos vértices finais.
	graph_list_remove(e->reference_list1, e->reference1);
	graph_list_remove(e->reference_list2, e->reference2);

	// Linkando a aresta anterior e a aresta seguinte.
	if (e->prev and e->next){ // Se houver aresta anterior e aresta seguinte (aresta intermediária).
		e->prev->next = e->next;
		e->next->prev = e->prev;
	}
	else if (e->prev){ // Se houver apenas aresta anterior (última aresta).
		g->last_edge = e->prev;
		e->prev->next = NULL;
	}
	else if (e->next){ // Se houver apenas aresta seguinte (primeira aresta).
		g->first_edge = e->next;
		e->next->prev = NULL;
	}
	else{ // Se não houver nem aresta anterior nem aresta seguinte (única aresta).
		g->first_edge = NULL;
		g->last_edge = NULL;
	}

	// Liberando memória alocada para armazenar o valor e a aresta.
	free(e->value);
	free(e);

	// Decrementando o contador de arestas.
	g->m--;
}

void graph_end_vertices(const Graph *g, const Edge *e, Vertex **v, Vertex **w){
	// Gravando os vértices finais nos ponteiros.
	*v = e->vertex1;
	*w = e->vertex2;
}

Edge **graph_incident_edges(const Graph *g, const Vertex *v){
	Node *aux = NULL;
	Edge **e = NULL;
	int n, i;

	// Obtendo a quantidade de arestas incidentes nesse vértice.
	n = graph_vertex_degree(g, v);

	// Se houver alguma aresta incidente.
	if (n){
		// Alocando um vetor de arestas.
		e = (Edge **)malloc(n * sizeof(Edge *));

		// Armazenando as arestas.
		for (i = 0; i < n; i++){
			aux = graph_list_get_next_node(v->adjacent, aux);
			e[i] = *((Edge **)graph_list_get_element_ro(v->adjacent, aux));
		}
	}

	return e;
}

Vertex *graph_opposite_vertex(const Graph *g, const Vertex *v, const Edge *e){
	// Retornando o vértice final de "e" que é diferente de v.
	return (e->vertex1 == v ? e->vertex2 : e->vertex1);
}

bool graph_are_adjacent(const Graph *g, const Vertex *v, const Vertex *w){
	Node *aux = NULL;
	Edge *e;

	// Percorrendo a lista de arestas incidentes do vértice com menor grau.
	if (graph_vertex_degree(g, v) < graph_vertex_degree(g, w)){
		while ((aux = graph_list_get_next_node(v->adjacent, aux))){
			// Recuperando aresta.
			e = *((Edge **)graph_list_get_element_ro(v->adjacent, aux));

			// Verificando se o vértice final oposto nessa aresta é o vértice w.
			if (graph_opposite_vertex(g, v, e) == w){
				return true;
			}
		}
	}
	else{
		while ((aux = graph_list_get_next_node(w->adjacent, aux))){
			// Recuperando aresta.
			e = *((Edge **)graph_list_get_element_ro(w->adjacent, aux));

			// Verificando se o vértice final oposto nessa aresta é o vértice v.
			if (graph_opposite_vertex(g, w, e) == v){
				return true;
			}
		}
	}

	// Não são adjacentes.
	return false;
}

int graph_vertex_degree(const Graph *g, const Vertex *v){
	// Retornando o tamanho da lista de adjacências do vértice.
	return graph_list_size(v->adjacent);
}

int graph_number_of_vertices(const Graph *g){
	// Retornando o valor do contador de vértices.
	return g->n;
}

int graph_number_of_edges(const Graph *g){
	// Retornando o valor do contador de arestas.
	return g->m;
}

void graph_print_graph(const Graph *g, void (*print_vertex)(const void *), void (*print_edge)(const void *)){
	// Imprimindo os vértices.
	graph_print_vertices(g, print_vertex);

	// Imprimindo as arestas.
	graph_print_edges(g, print_edge);
}

void graph_print_vertices(const Graph *g, void (*print_vertex)(const void *)){
	Vertex *aux = g->first_vertex;
	int i;

	// Imprimindo a quantidade de vértices.
	printf("%d\n", g->n);

	// Imprimindo os vértices.
	for (i = 0; i < g->n; i++){
		// Imprimindo o Id do vértice.
		printf("%d ", aux->id);

		// Imprimindo o valor do vértice.
		print_vertex(aux->value);
		printf("\n");

		// Indo para o próximo vértice.
		aux = aux->next;
	}
}

void graph_print_edges(const Graph *g, void (*print_edge)(const void *)){
	Edge *aux = g->first_edge;
	Vertex *v, *w;
	int i;

	// Imprimindo a quantidade de arestas.
	printf("%d\n", g->m);

	// Imprimindo as arestas.
	for (i = 0; i < g->m; i++){
		// Recuperando os vértices finais da aresta atual.
		graph_end_vertices(g, aux, &v, &w);

		// Imprimindo o Id da aresta e os Ids de seus vértices finais (em ordem crescente).
		printf("%d %d %d ", aux->id, MIN(v->id, w->id), MAX(v->id, w->id));

		// Imprimindo o valor da aresta.
		print_edge(aux->value);
		printf("\n");

		// Indo para a próxima aresta.
		aux = aux->next;
	}
}

Vertex *graph_vertex_new(int id, const void *value, int vertex_value_size){
	Vertex *v = (Vertex *)malloc(sizeof(Vertex));

	// Criando uma nova lista de adjacência.
	v->adjacent = graph_list_create(sizeof(Edge *));

	// Atribuindo um Id ao vértice.
	v->id = id;

	// Armazenando o valor no vértice.
	v->value = malloc(vertex_value_size);
	memcpy(v->value, value, vertex_value_size);

	// Inicializando seus ponteiros com NULL.
	v->next = NULL;
	v->prev = NULL;

	return v;
}

Edge *graph_edge_new(int id, Vertex *v, Vertex *w, const void *value, int edge_value_size){
	Edge *e = (Edge *)malloc(sizeof(Edge));

	// Atribuindo um Id à aresta.
	e->id = id;

	// Atribuindo as listas de adjacências.
	e->reference_list1 = v->adjacent;
	e->reference_list2 = w->adjacent;

	// Inserindo e atribuindo as referências.
	e->reference1 = graph_list_insert(v->adjacent, &e);
	e->reference2 = graph_list_insert(w->adjacent, &e);

	// Armazenando o valor na aresta.
	e->value = malloc(edge_value_size);
	memcpy(e->value, value, edge_value_size);

	// Atribuindo os ponteiros para os vértices finais.
	e->vertex1 = v;
	e->vertex2 = w;

	// Inicializando seus ponteiros com NULL.
	e->next = NULL;
	e->prev = NULL;

	return e;
}
