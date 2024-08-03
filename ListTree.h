// Interface to the String List ADT

//
// Description - Interface to the String List ADT used in invertedIndex.c. Houses important
// functions such as sorting function.

#ifndef LISTTREE_H
#define LISTTREE_H

#include <stdbool.h>

typedef struct listtree *ListTree;

// Creates a new empty list
// Complexity: O(1)
ListTree ListTreeNew(void);

// Frees all memory allocated for the given list
// Complexity: O(n)
void ListTreeFree(ListTree l);

// Adds a string to the end of the list. Makes a copy of the string
// before adding it to the list.
// Complexity: O(1)
void ListTreeAppend(ListTree l, char *s);

// Returns the number of items in the list
// Complexity: O(1)
int  ListTreeSize(ListTree l);

// Sorts the list in ASCII order
// Average complexity: O(n log n)
void ListTreeSort(ListTree l);

// Prints the list, one string per line
void ListTreePrint(ListTree l, FILE *ptr);

/**
 * Returns true if the url being looked for is 
 * already present in the linked list
 */
bool ListTreeSearch(ListTree l, char *fileName);

////////////////////////////////////////////////////////////////////////

#endif
