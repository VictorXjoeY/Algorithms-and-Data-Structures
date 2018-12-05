/* Victor Forbes - 9293394 - This Data Structure works for lowercase strings. */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct Trie Trie;

/* O(1) - Creates an empty Trie. */
Trie *trie_create();

/* O(|S|) - Clears every element from the Trie. */
void trie_clear(Trie *);

/* O(|S|) - Destroys the Trie. */
void trie_destroy(Trie *);

/* O(|S|) - Inserts a string into the Trie. */
void trie_insert(Trie *, const char *);

/* O(|S|) - Erases a string from the Trie. */
void trie_erase(Trie *, const char *);

/* O(|S|) - Counts the number of occurrences of a string in the Trie. */
int trie_count(const Trie *, const char *);

/* O(1) - Returns the number of elements in the Trie. */
int trie_size(const Trie *);

/* O(1) - Returns true if the Trie is empty and false otherwise. */
bool trie_empty(const Trie *);

#endif