/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "algorithm.h"
#include "priority_queue.h"
#include "utils.h"

/* Retorna o índice do maior elemento em v. */
void *max_element(void *v, int n, int size, int (*compare)(const void *, const void *)){
	int i, j;

	for (i = 1, j = 0; i < n; i++){
		if (compare(v + i * size, v + j * size) > 0){
			j = i;
		}
	}

	return v + j * size;
}

/* Retorna o índice do menor elemento em v. */
void *min_element(void *v, int n, int size, int (*compare)(const void *, const void *)){
	int i, j;

	for (i = 1, j = 0; i < n; i++){
		if (compare(v + i * size, v + j * size) < 0){
			j = i;
		}
	}

	return v + j * size;
}

/* Dá um merge nos vetores a e b de tamanhos n e m e coloca o resultado no vetor c. */
void merge(const void *a, int n, const void *b, int m, void *c, int size, int (*compare)(const void *, const void *)){
	int i, j, k;
	void *aux;

	// Alocando um vetor auxiliar.
	aux = malloc((n + m) * size);

	// Enquanto ainda houver elementos em ambos os vetores.
	for (i = 0, j = 0, k = 0; i < n && j < m; k++){
		if (compare(a + i * size, b + j * size) < 0){
			memcpy(aux + k * size, a + i * size, size);
			i++;
		}
		else{
			memcpy(aux + k * size, b + j * size, size);
			j++;
		}
	}

	// Enquanto ainda houver elementos no vetor a.
	while (i < n){
		memcpy(aux + k * size, a + i * size, size);
		i++;
		k++;
	}

	// Enquanto ainda houver elementos no vetor b.
	while (j < m){
		memcpy(aux + k * size, b + j * size, size);
		j++;
		k++;
	}

	// Copiando o resultado do merge para o vetor c.
	memcpy(c, aux, (n + m) * size);
	free(aux);
}

/* Bubble Sort. */
void bubble_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	bool swapped;
	int i;

	do{
		swapped = false;

		for (i = 0; i < n - 1; i++){
			if (compare(v + i * size, v + (i + 1) * size) > 0){
				swap(v + i * size, v + (i + 1) * size, size);
				swapped = true;
			}
		}

	}while (n > 1 && swapped);
}

/* Selection Sort. */
void selection_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	int i, j;

	for (i = 0; i < n - 1; i++){
		// Buscando o menor elemento para colocar em v[i].
		j = (min_element(v + i * size, n - i, size, compare) - v) / size;
		swap(v + i * size, v + j * size, size);
	}
}

/* Insertion Sort. */
void insertion_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	void *aux;
	int i, j;

	// Memória auxiliar
	aux = malloc(size);

	// Para cada elemento.
	for (i = 1; i < n; i++){
		// Salvando o elemento.
		memcpy(aux, v + i * size, size);

		// Buscando sua posição de inserção. Equivalente ao upper bound de aux.
		for (j = i - 1; j >= 0 && compare(v + j * size, aux) > 0; j--);

		// Shiftando para direita os elementos na range [j + 1, i - 1].
		if (j + 1 <= i - 1){
			memmove(v + (j + 2) * size, v + (j + 1) * size, (i - j - 1) * size);
		}

		// Colocando o elemento na posição correta.
		memcpy(v + (j + 1) * size, aux, size);
	}

	free(aux);
}

/* Retorna uma cópia de uma tupla (size, compare, element). */
void *heap_sort_copy(const void *a){
	int size = *((int *)a); // Recupera o tamanho.
	void *b;

	// Realiza a cópia.
	b = malloc(sizeof(int) + sizeof(int(*)(const void *, const void *)) + size);
	memcpy(b, a, sizeof(int) + sizeof(int(*)(const void *, const void *)) + size);

	return b;
}

/* Destrói uma tupla (size, compare, element). */
void heap_sort_destroy(void *a){
	free(a);
}

/* Compara uma tupla (size, compare, element). */
int heap_sort_compare(const void *a, const void *b){
	int (*compare)(const void *, const void *) = *((int(**)(const void *, const void *))(a + sizeof(int))); // Recupera a função de comparação.

	// Retorna a comparação dos elementos.
	return compare(a + sizeof(int) + sizeof(int(*)(const void *, const void *)), b + sizeof(int) + sizeof(int(*)(const void *, const void *)));
}

/* Heap Sort. */
void heap_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	PriorityQueue *pq;
	void *aux;
	int i;

	// Criando uma Priority Queue para guardar tuplas (size, compare, element).
	pq = priority_queue_create(heap_sort_copy, heap_sort_destroy, heap_sort_compare);

	// Alocando uma variável auxiliar para montar as tuplas.
	aux = malloc(sizeof(int) + sizeof(int(*)(const void *, const void *)) + size);
	*((int *)aux) = size;
	*((int(**)(const void *, const void *))(aux + sizeof(int))) = compare;

	// Inserindo todos os elementos da Priority Queue.
	for (i = 0; i < n; i++){
		memcpy(aux + sizeof(int) + sizeof(int(*)(const void *, const void *)), v + i * size, size);
		priority_queue_push(pq, aux);
	}

	heap_sort_destroy(aux);

	// Inserindo todos os elementos de volta no vetor.
	for (i = n - 1; i >= 0; i--){
		aux = priority_queue_top(pq);
		priority_queue_pop(pq);

		memcpy(v + i * size, aux + sizeof(int) + sizeof(int(*)(const void *, const void *)), size);
		heap_sort_destroy(aux);
	}

	priority_queue_destroy(pq);
}

/* Função recursiva que realiza o Merge Sort. */
void recursive_merge_sort(void *v, int l, int r, int size, int (*compare)(const void *, const void *)){
	int m = (l + r) / 2;

	if (l < r){
		recursive_merge_sort(v, l, m, size, compare);
		recursive_merge_sort(v, m + 1, r, size, compare);
		merge(v + l * size, m - l + 1, v + (m + 1) * size, r - m, v + l * size, size, compare);
	}
}

/* Merge Sort. */
void merge_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	recursive_merge_sort(v, 0, n - 1, size, compare);
}

/* Particiona o vetor considerando um pivot. */
void *partition(void *v, int n, int size, int (*compare)(const void *, const void *)){
	int i, j;

	// Escolhendo o elemento do meio como o pivot e o posicionando no final.
	swap(v + ((n - 1) / 2) * size, v + (n - 1) * size, size);

	// Particionando.
	for (i = 0, j = 0; j < n - 1; j++){
		if (compare(v + j * size, v + (n - 1) * size) < 0){
			swap(v + i * size, v + j * size, size);
			i++;
		}
	}

	// Posicionando o pivot na posição correta.
	swap(v + i * size, v + (n - 1) * size, size);

	return v + i * size;
}

/* Função recursiva que realiza o Quick Sort. */
void recursive_quick_sort(void *v, int l, int r, int size, int (*compare)(const void *, const void *)){
	int p;

	if (l < r){
		p = (partition(v + l * size, r - l + 1, size, compare) - v) / size;
		recursive_quick_sort(v, l, p - 1, size, compare);
		recursive_quick_sort(v, p + 1, r, size, compare);
	}
}

/* Quick Sort. */
void quick_sort(void *v, int n, int size, int (*compare)(const void *, const void *)){
	recursive_quick_sort(v, 0, n - 1, size, compare);
}

/* Busca Binária que retorna o Lower Bound. */
void *lower_bound(void *v, int n, int size, int (*compare)(const void *, const void *), void *key){
	int l, r, m;

	l = 0;
	r = n - 1;

	while (l < r){
		m = (l + r) / 2;

		if (compare(v + m * size, key) < 0){
			l = m + 1;
		}
		else{
			r = m;
		}
	}

	return compare(v + l * size, key) < 0 ? v + n * size : v + l * size;
}

/* Busca Binária que retorna o Upper Bound. */
void *upper_bound(void *v, int n, int size, int (*compare)(const void *, const void *), void *key){
	int l, r, m;

	l = 0;
	r = n - 1;

	while (l < r){
		m = (l + r) / 2;

		if (compare(key, v + m * size) < 0){
			r = m;
		}
		else{
			l = m + 1;
		}
	}

	return compare(key, v + l * size) < 0 ? v + l * size : v + n * size;
}