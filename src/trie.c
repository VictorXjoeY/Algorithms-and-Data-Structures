/* Victor Forbes - 9293394 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

struct Trie{
	int terminal, size;
	Trie **child;
};

Trie *trie_create(){
	Trie *t = (Trie *)malloc(sizeof(Trie));

	t->size = t->terminal = 0;
	t->child = (Trie **)calloc(26, sizeof(Trie *));

	return t;
}

void trie_clear(Trie *t){
	int i;

	for (i = 0; i < 26; i++){
		if (t->child[i]){
			trie_destroy(t->child[i]);
			t->child[i] = NULL;
		}
	}

	t->size = t->terminal = 0;
}

void trie_destroy(Trie *t){
	trie_clear(t);
	free(t->child);
	free(t);
}

void trie_insert(Trie *t, const char *str){
	t->size++;

	if (!(*str)){
		t->terminal++;
		return;
	}

	if (!t->child[*str - 'a']){
		t->child[*str - 'a'] = trie_create();
	}

	trie_insert(t->child[*str - 'a'], str + 1);
}

void trie_erase_aux(Trie *t, const char *str){
	t->size--;

	if (!(*str)){
		t->terminal--;
	}
	else{
		trie_erase_aux(t->child[*str - 'a'], str + 1);
	}

	// Node is empty after removal.
	if (trie_empty(t)){
		free(t->child);
		free(t);
	}
}

void trie_erase(Trie *t, const char *str){
	if (trie_count(t, str)){ // Erases only if the string is in the Trie.
		t->size--;

		if (!strcmp(str, "")){ // Empty string.
			t->terminal--;
		}
		else{
			trie_erase_aux(t->child[*str - 'a'], str + 1);
		}
	}
}

int trie_count(const Trie *t, const char *str){
	if (!(*str)){
		return t->terminal;
	}

	if (!t->child[*str - 'a']){
		return 0;
	}

	return trie_count(t->child[*str - 'a'], str + 1);
}

int trie_size(const Trie *t){
	return t->size;
}

bool trie_empty(const Trie *t){
	return trie_size(t) == 0;
}