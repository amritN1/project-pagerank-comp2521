// Interface to the String List ADT

//
// Description - Interface to the String List ADT used in searchPagerank.c

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list *List;

// Creates a new empty list
// Complexity: O(1)
List ListNew(void);

// Frees all memory allocated for the given list
// Complexity: O(n)
void ListFree(List l);

// Adds a string to the end of the list. Makes a copy of the string
// before adding it to the list.
// Complexity: O(1)
void ListAppend(List l, char *s);

// Returns the number of items in the list
// Complexity: O(1)
int  ListSize(List l);

// returns true if url already exists in the linked list
bool listCheck(List l, char *token);

// updates count of the url node if its already present in the list
void listUpdateUrlCount(List l, char *token);

/**
 * Matches the appropriate page url to the corrct url
 * Updates the node's pagerank parameter to url's pagerank
 */
void matchUrl(List l, char *url, char *rank);

/**
 * Function uses bubble sort to sort the linked list in accordance to
 * url count in descending order
 */
void sortUrlCount(List l);

/**
 * Function uses bubble sort to sort the linked list in accordance to
 * url pagerank in descending order
 */
void sortPageRank(List l);

/**
 * Function outputs the top 30 url to stdout
 */
void outputUrl(List l);
////////////////////////////////////////////////////////////////////////

#endif

