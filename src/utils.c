/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void swap(void *a, void *b, int size){
	void *c;

	if (a != b){
		c = malloc(size);
		memcpy(c, a, size);
		memcpy(a, b, size);
		memcpy(b, c, size);
		free(c);
	}
}

void **malloc_matrix(int n, int m, int size){
	void **mat = (void **)malloc(n * sizeof(void *));
	int i;

	for (i = 0; i < n; i++){
		mat[i] = malloc(m * size);
	}

	return mat;
}

void **calloc_matrix(int n, int m, int size){
	void **mat = (void **)malloc(n * sizeof(void *));
	int i;

	for (i = 0; i < n; i++){
		mat[i] = calloc(m, size);
	}

	return mat;
}

void free_matrix(void **mat, int n){
	int i;

	if (mat){
		for (i = 0; i < n; i++){
			free(mat[i]);
		}

		free(mat);
	}
}

int int_compare_ascending(const void *a, const void *b){
	return *((int *)a) - *((int *)b);
}

int int_compare_descending(const void *a, const void *b){
	return *((int *)b) - *((int *)a);
}

int double_compare_ascending(const void *a, const void *b){
	if (*((double *)a) < *((double *)b)){
		return -1;
	}

	if (*((double *)a) > *((double *)b)){
		return 1;
	}

	return 0;
}

int double_compare_descending(const void *a, const void *b){
	if (*((double *)a) > *((double *)b)){
		return -1;
	}

	if (*((double *)a) < *((double *)b)){
		return 1;
	}

	return 0;
}

int string_compare_ascending(const void *a, const void *b){
	return strcmp(*((char **)b), *((char **)a));
}

int string_compare_descending(const void *a, const void *b){
	return strcmp(*((char **)a), *((char **)b));
}

int reference_compare_ascending(const void *a, const void *b){
	if (*((void **)a) < *((void **)b)){
		return -1;
	}

	if (*((void **)a) > *((void **)b)){
		return 1;
	}

	return 0;
}

void print_int(const void *a){
	printf("%d", *((int *)a));
}

void print_double(const void *a){
	printf("%.3lf", *((double *)a));
}

void print_string(const void *a){
	printf("%s", *((char **)a));
}