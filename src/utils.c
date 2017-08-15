/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/* Checks if the string "str" contains the character "c". */
bool contains(char *, char);

char *read_stretch(FILE *fp, char *limits){
    char *stretch = NULL;
    int i = 0;

    do{
        stretch = (char *)realloc(stretch, (i + 1) * sizeof(char));
        fscanf(fp, "%c", stretch + i);
        i++;
    }while (!feof(fp) && !contains(limits, stretch[i - 1]));

    stretch[i - 1] = '\0';

    return stretch;
}

void swap(void *v, int size, int x, int y){
	void *aux;

	if (x != y){
		aux = malloc(size);
		memcpy(aux, v + x * size, size);
		memcpy(v + x * size, v + y * size, size);
		memcpy(v + y * size, aux, size);
		free(aux);
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

bool contains(char *str, char c){
	while (*str and *str != c){
		str++;
	}

	return *str == c;
}