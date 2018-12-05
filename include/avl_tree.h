/* Victor Forbes - 9293394 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

typedef struct AVLTree AVLTree;

/* O(1) - Creates an empty AVL Tree. */
AVLTree *avl_tree_create();

/* O(N) - Clears every element from the AVL Tree. */
void avl_tree_clear(AVLTree *);

/* O(N) - Destroys the AVL Tree. */
void avl_tree_destroy(AVLTree *);

/* O(Log(N)) - Inserts an element into the AVL Tree. */
void avl_tree_insert(AVLTree *, int);

/* O(Log(N)) - Erases an element from the AVL Tree. */
void avl_tree_erase(AVLTree *, int);

/* O(Log(N)) - Returns 1 in case the value is in the AVL Tree and 0 otherwise. */
int avl_tree_count(const AVLTree *, int);

/* O(1) - Returns the number of elements in the AVL Tree. */
int avl_tree_size(const AVLTree *);

/* O(1) - Returns true if the AVL Tree is empty and false otherwise. */
bool avl_tree_empty(const AVLTree *);

#endif