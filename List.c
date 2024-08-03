// Implementation of the String List ADT

// Description - Linked list ADT to store inforamtion about url and the words
// contained inside the url. Also used to sort in accoradance to pagerank and 
// url count in descanding order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

struct node {
    char *url;
    int urlCount;
    double pagerank;
    struct node *next;
};

struct list {
    struct node *head;
    struct node *tail;
    int size;
};

static struct node *newNode(char *s);
static char *myStrdup(char *s);
bool listCheck(List l, char *token);
void listUpdateUrlCount(List l, char *token);
void matchUrl(List l, char *url, char *token);
void sortUrlCount(List l);
void sortPageRank(List l);
void outputUrl(List l);

////////////////////////////////////////////////////////////////////////

// Creates a new empty list
List ListNew(void) {
    List l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

// Frees all memory allocated for the given list
void ListFree(List l) {
    struct node *curr = l->head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp->url);
        free(temp);
    }
    free(l);
}

// Adds a string to the end of the list
void ListAppend(List l, char *s) {
    struct node *n = newNode(s);
    n->urlCount++;
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;
}

// Creates a new node to be added to the linked list
static struct node *newNode(char *s) {
    struct node *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->url = myStrdup(s);
    n->next = NULL;
    n->urlCount = 0;
    n->pagerank = 0.0;
    return n;
}

// Copies realevant string to be inserted in the url field of new node
static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Returns the number of items in the list
int ListSize(List l) {
    return l->size;
}

/**
 * Returns true if the url being looked for is 
 * already present in the linked list
 */
bool listCheck(List l, char *token) {

    struct node *curr = l->head;
    while (curr != NULL) {
        // comparing the current node's url paremter and url passed in
        if (strcmp(curr->url,token) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/**
 * Updates count of the url node if its alread present in the list
 */
void listUpdateUrlCount(List l, char *token) {

    struct node *curr = l->head;
    while (curr != NULL) {
        if (strcmp(curr->url,token) == 0) {
            curr->urlCount++;
        }
        curr = curr->next;
    }
}

/**
 * Matches the appropriate page url to the corrct url
 * Updates the node's pagerank parameter to url's pagerank
 */
void matchUrl(List l, char *url, char *rank) {

    struct node *curr = l->head;
    char *ptr;
    while (curr != NULL) {
        
        if (strcmp(curr->url,url) == 0) {
            // converts string into a floatiny type number
            curr->pagerank = strtod(rank, &ptr);
        }
        curr = curr->next;
    }
}

/**
 * Function uses bubble sort to sort the linked list in accordance to
 * url count in descending order
 */
void sortUrlCount(List l) {

    int count = l->size;
    for (int i = 0; i < count - 1; i++) {
        struct node *curr = l->head;
        struct node *prev = NULL;

        while (curr != NULL && curr->next != NULL) {
            
            if (curr->urlCount < curr->next->urlCount) {
                // Swap values using a temporary variable
                if (curr == l->head) {

                    struct node *temp1 = curr;
                    struct node *temp2 = curr->next->next;
                    l->head = curr->next;
                    l->head->next = temp1;
                    temp1->next = temp2;

                } else if (curr->next == l->tail) {

                    struct node *temp = curr->next;
                    prev->next = temp;
                    temp->next = curr;
                    curr->next = NULL;
                    l->tail = curr;
    
                } else {
                    
                    struct node *temp1 = curr->next;
                    struct node *temp2 = curr->next->next;
                    prev->next = temp1;
                    temp1->next = curr;
                    curr->next = temp2;
                }
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

/**
 * Function uses bubble sort to sort the linked list in accordance to
 * url pagerank in descending order
 */
void sortPageRank(List l) {
    
    int count = l->size;
    for (int i = 0; i < count - 1; i++) {
        struct node *curr = l->head;
        struct node *prev = NULL;

        while (curr != NULL && curr->next != NULL) {

            if (curr->urlCount == curr->next->urlCount &&
                curr->pagerank < curr->next->pagerank) {
                // Swap values using a temporary variable
                if (curr == l->head) {

                    struct node *temp1 = curr;
                    struct node *temp2 = curr->next->next;
                    l->head = curr->next;
                    l->head->next = temp1;
                    temp1->next = temp2;

                } else if (curr->next == l->tail) {

                    struct node *temp = curr->next;
                    prev->next = temp;
                    temp->next = curr;
                    curr->next = NULL;
                    l->tail = curr;
    
                } else {
                    
                    struct node *temp1 = curr->next;
                    struct node *temp2 = curr->next->next;
                    prev->next = temp1;
                    temp1->next = curr;
                    curr->next = temp2;
                }
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

/**
 * Function outputs the top 30 url to stdout
 */
void outputUrl(List l) {

    int i = 0;
    struct node *curr  = l->head;
    while (curr != NULL && i < 30) {

        printf("%s\n", curr->url);
        curr = curr->next;
        i++;
    }
}


