/* Victor Forbes - 9293394 */

#ifndef STACK_H
#define STACK_H

#include "utils.h"

typedef struct Stack Stack;

/* Creates a Stack for elements of size "element_size". */
Stack *stack_create(int);

/* Erases every element in the Stack. */
void stack_clear(Stack *);

/* Destroys Stack. */
void stack_destroy(Stack *);

/* Inserts an element on top of the Stack. */
void stack_push(Stack *, const void *);

/* Returns a copy of the element that is on top of the Stack. */
void *stack_top(const Stack *);

/* Returns a reference to the element that is on top of the Stack. */
const void *stack_top_ro(const Stack *);

/* Erases the top element from the Stack. */
void stack_pop(Stack *);

/* Returns true if the Stack is empty and false otherwise. */
bool stack_empty(const Stack *);

/* Returns the amount of elements currently in the Stack. */
int stack_size(const Stack *);

#endif