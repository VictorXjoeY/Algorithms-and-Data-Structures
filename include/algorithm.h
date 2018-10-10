/* Victor Forbes - 9293394 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

/* O(N) Max Element. */
void *max_element(void *, int , int, int (*)(const void *, const void *));

/* O(N) Min Element. */
void *min_element(void *, int , int, int (*)(const void *, const void *));

/* O(N) Merge. */
void merge(const void *, int n, const void *, int, void *, int, int (*)(const void *, const void *));

/* O(N^2) Bubble Sort. */
void bubble_sort(void *, int, int, int (*)(const void *, const void *));

/* O(N^2) Selection Sort. */
void selection_sort(void *, int, int, int (*)(const void *, const void *));

/* O(N^2) Insertion Sort. */
void insertion_sort(void *, int, int, int (*)(const void *, const void *));

/* O(N * Log(N)) Merge Sort. */
void merge_sort(void *, int, int, int (*)(const void *, const void *));

/* O(N * Log(N)) Heap Sort. */
void heap_sort(void *, int, int, int (*)(const void *, const void *));

/* O(N * Log(N)) Quick Sort. */
void quick_sort(void *, int, int, int (*)(const void *, const void *));

/* O(Log(N)) Busca Binária que retorna o Lower Bound. */
void *lower_bound(void *, int, int, int (*)(const void *, const void *), void *);

/* O(Log(N)) Busca Binária que retorna o Upper Bound. */
void *upper_bound(void *, int, int, int (*)(const void *, const void *), void *);

#endif