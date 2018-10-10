/* Victor Forbes - 9293394 */

#ifndef UTILS_H
#define UTILS_H

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

/* O(1) - Swaps two elements given their address and size. */
void swap(void *, void *, int);

#endif