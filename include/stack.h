/* Victor Forbes - 9293394 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "deque.h"

typedef Deque Stack;

/* O(1) - Creates an empty Stack. */
Stack *stack_create(void *(*)(const void *), void (*)(void *));

/* O(N) - Clears every element from the Stack. */
void stack_clear(Stack *);

/* O(N) - Destroys the Stack. */
void stack_destroy(Stack *);

/* O(1) - Pushes an element to the back of the Stack. */
void stack_push(Stack *, const void *);

/* O(1) - Pops the element at the back of the Stack. */
void stack_pop(Stack *);

/* O(1) - Returns the element at the back of the Stack. */
void *stack_top(const Stack *);

/* O(1) - Returns the number of the elements in the Stack. */
int stack_size(const Stack *);

/* O(1) - Returns true if the Stack is empty and false otherwise. */
bool stack_empty(const Stack *);

#endif