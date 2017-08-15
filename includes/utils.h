/* Victor Forbes - 9293394 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

#define true 1
#define false 0

#define and &&
#define or ||
#define not !

typedef unsigned char bool;

char *read_stretch(FILE *, char *);

void swap(void *, int, int, int);

void **malloc_matrix(int, int, int);

void **calloc_matrix(int, int, int);

void free_matrix(void **, int);

int int_compare_ascending(const void *, const void *);

int int_compare_descending(const void *, const void *);

int double_compare_ascending(const void *, const void *);

int double_compare_descending(const void *, const void *);

int string_compare_ascending(const void *, const void *);

int string_compare_descending(const void *, const void *);

/* Função de comparação para checar se a e b são o mesmo "objeto". */
int reference_compare_ascending(const void *, const void *);

void print_int(const void *);

void print_double(const void *);

void print_string(const void *);

#endif