/* Victor Forbes - 9293394 */

#ifndef STACK_H
#define STACK_H

#include "utils.h"
#include "deque.h"

typedef Deque Stack;

/* Creates an empty Stack. */
Stack *stack_create(void *(*)(const void *), void (*)(void *));

/* Clears every element from the Stack. */
void stack_clear(Stack *);

/* Destroys the Stack. */
void stack_destroy(Stack *);

/* Pushes an element to the back of the Stack. */
void stack_push(Stack *, const void *);

/* Pops the element at the back of the Stack. */
void stack_pop(Stack *);

/* Returns the element at the back of the Stack. */
void *stack_top(const Stack *);

/* Returns the number of the elements in the Stack. */
int stack_size(const Stack *);

/* Returns true if the Stack is empty and false otherwise. */
bool stack_empty(const Stack *);

#endif