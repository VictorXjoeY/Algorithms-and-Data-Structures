/* Victor Forbes - 9293394 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl_tree.h"
#include "utils.h"

typedef struct AVLTreeNode AVLTreeNode;

struct AVLTreeNode{
	AVLTreeNode *left, *right;
	int value, height;
};

struct AVLTree{
	AVLTreeNode *root;
	int size;
};

AVLTree *avl_tree_create(){
	return (AVLTree *)calloc(1, sizeof(AVLTree));
}

/* O(1) - Creates an AVL Tree Node. */
AVLTreeNode *avltreenode_create(int value){
	AVLTreeNode *n = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));

	n->left = n->right = NULL;
	n->value = value;
	n->height = 0;

	return n;
}

/* O(1) - Destroys an AVL Tree Node. */
void avltreenode_destroy(AVLTreeNode *n){
	free(n);
}

/* O(N) - Clears an AVL Tree recursively. */
void avl_tree_clear_recursive(AVLTreeNode *cur){
	if (!cur){
		return;
	}

	// Freeing Nodes in post-order.
	avl_tree_clear_recursive(cur->left);
	avl_tree_clear_recursive(cur->right);
	avltreenode_destroy(cur);
}

void avl_tree_clear(AVLTree *avl){
	avl_tree_clear_recursive(avl->root);
	avl->root = NULL;
	avl->size = 0;
}

void avl_tree_destroy(AVLTree *avl){
	avl_tree_clear(avl);
	free(avl);
}

/* O(1) - Returns the height of a Node. */
int height(AVLTreeNode *cur){
	return cur ? cur->height : -1;
}

/* O(1) - Returns the balance factor of a Node. */
int balance_factor(AVLTreeNode *cur){
	return cur ? height(cur->right) - height(cur->left) : 0;
}

/* O(1) - Right Rotation. */
AVLTreeNode *right_rotation(AVLTreeNode *a){
	AVLTreeNode *b = a->left;

	// Rotating to the right.
	a->left = b->right;
	b->right = a;

	// Updating heights.
	a->height = 1 + max(height(a->left), height(a->right));
	b->height = 1 + max(height(b->left), height(b->right));

	return b;
}

/* O(1) - Left Rotation. */
AVLTreeNode *left_rotation(AVLTreeNode *a){
	AVLTreeNode *b = a->right;

	// Rotating to the left.
	a->right = b->left;
	b->left = a;

	// Updating heights.
	a->height = 1 + max(height(a->left), height(a->right));
	b->height = 1 + max(height(b->left), height(b->right));

	return b;
}

/* O(1) - Left Right Rotation. */
AVLTreeNode *left_right_rotation(AVLTreeNode *a){
	a->left = left_rotation(a->left); // Rotating to the left.
	return right_rotation(a); // Rotating to the right.
}

/* O(1) - Right Left Rotation. */
AVLTreeNode *right_left_rotation(AVLTreeNode *a){
	a->right = right_rotation(a->right); // Rotating to the right.
	return left_rotation(a); // Rotating to the left.
}

/* O(1) - Balances a Node if it's not balanced. */
AVLTreeNode *balance(AVLTreeNode *cur){
	if (!cur){ // NULL Node is already balanced.
		return NULL;
	}

	if (balance_factor(cur) == -2){ // Left-heavy.
		if (balance_factor(cur->left) <= 0){ // Right Rotation.
			cur = right_rotation(cur);
		}
		else{ // Left Right Rotation.
			cur = left_right_rotation(cur);
		}
	}
	else if (balance_factor(cur) == 2){ // Right-heavy.
		if (balance_factor(cur->right) >= 0){ // Left Rotation.
			cur = left_rotation(cur);
		}
		else{ // Right Left Rotation.
			cur = right_left_rotation(cur);
		}
	}

	// Updating current Node's height.
	cur->height = 1 + max(height(cur->left), height(cur->right));

	return cur;
}

/* O(Log(N)) - Inserts an element into the AVL Tree recursively. */
AVLTreeNode *avl_tree_insert_recursive(AVLTree *avl, AVLTreeNode *cur, int value){
	if (!cur){ // Element is not in the tree, inserts it.
		avl->size++;
		return avltreenode_create(value);
	}

	if (value < cur->value){ // Inserts into current Node's left subtree.
		cur->left = avl_tree_insert_recursive(avl, cur->left, value);
	}
	else if (value > cur->value){ // Inserts into current Node's right subtree.
		cur->right = avl_tree_insert_recursive(avl, cur->right, value);
	}

	// Re-balancing current node.
	cur = balance(cur);

	return cur;
}

void avl_tree_insert(AVLTree *avl, int value){
	avl->root = avl_tree_insert_recursive(avl, avl->root, value);
}

/* O(Log(N)) - Erases an element from the AVL Tree recursively. */
AVLTreeNode *avl_tree_erase_recursive(AVLTree *avl, AVLTreeNode *cur, int value){
	AVLTreeNode *aux;

	if (!cur){ // Element is not in the tree.
		return NULL;
	}

	if (value < cur->value){ // Erases the element from current Node's left subtree.
		cur->left = avl_tree_erase_recursive(avl, cur->left, value);
	}
	else if (value > cur->value){ // Erases the element from current Node's right subtree.
		cur->right = avl_tree_erase_recursive(avl, cur->right, value);
	}
	else{ // Found element to be erased.
		aux = cur;

		if (cur->left && cur->right){ // Current Node has 2 children.
			// Retrieving the greatest element from the left subtree.
			// HERE WE COULD CHOOSE TO REMOVE FROM THE LEFT SUBTREE OR THE RIGHT SUBTREE ACCORDING TO THEIR HEIGHT IN ORDER TO OPTIMIZE DELETION A LITTLE BIT.
			aux = aux->left;

			while (aux->right){
				aux = aux->right;
			}

			// Swaps the current Node's value with its predecessor and now we should erase it from the left subtree.
			swap(&cur->value, &aux->value, sizeof(int));
			cur->left = avl_tree_erase_recursive(avl, cur->left, value);
		}
		else if (cur->left){ // Current Node has only the left child.
			avl->size--;
			cur = cur->left;
			avltreenode_destroy(aux);
		}
		else if (cur->right){ // Current Node has only the right child.
			avl->size--;
			cur = cur->right;
			avltreenode_destroy(aux);
		}
		else{ // Current Node is a leaf.
			avl->size--;
			cur = NULL;
			avltreenode_destroy(aux);
		}
	}

	// Re-balancing current Node.
	cur = balance(cur);

	return cur;
}

void avl_tree_erase(AVLTree *avl, int value){
	avl->root = avl_tree_erase_recursive(avl, avl->root, value);
}

/* O(Log(N)) - Returns 1 in case the value is in the AVL Tree and 0 otherwise (recursively). */
int avl_tree_count_recursive(const AVLTreeNode *cur, int value){
	if (!cur){
		return 0;
	}

	if (value < cur->value){ // Busca na sub-árvore da esquerda.
		return avl_tree_count_recursive(cur->left, value);
	}
	
	if (value > cur->value){ // Busca na sub-árvore da direita.
		return avl_tree_count_recursive(cur->right, value);
	}

	// Chave encontrada.
	return 1;
}

int avl_tree_count(const AVLTree *avl, int value){
	return avl_tree_count_recursive(avl->root, value);
}

int avl_tree_size(const AVLTree *avl){
	return avl->size;
}

bool avl_tree_empty(const AVLTree *avl){
	return avl_tree_size(avl) == 0;
}