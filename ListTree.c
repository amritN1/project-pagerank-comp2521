// Implementation of the String List ADT

//
// Description - This program is the linked list ADT which is used to store urls 
// in it's node. It is used to store a complete databse of all urls the words
// are from.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListTree.h"

struct node {
    char *s;
    struct node *next;
};

struct listtree {
    struct node *head;
    struct node *tail;
    int size;
};

static struct node *newNode(char *s);
static char *myStrdup(char *s);
static int qsortStrcmp(const void *ptr1, const void *ptr2);

// Creates a new empty list
ListTree ListTreeNew(void) {
    ListTree l = malloc(sizeof(*l));
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
void ListTreeFree(ListTree l) {
    struct node *curr = l->head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp->s);
        free(temp);
    }
    free(l);
}

// Adds a string to the end of the list
void ListTreeAppend(ListTree l, char *s) {
    struct node *n = newNode(s);
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;
}

// Creates a new node to be added the linked list
static struct node *newNode(char *s) {
    struct node *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    n->s = myStrdup(s);
    n->next = NULL;
    return n;
}

// Copies realevant string to be inserted in the string field of new node
static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Returns the number of items in the list
int ListTreeSize(ListTree l) {
    return l->size;
}

// Sorts the list in ASCII order using quick sort
void ListTreeSort(ListTree l) {
    char **items = malloc(l->size * sizeof(char *));
    if (items == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    for (struct node *curr = l->head; curr != NULL; curr = curr->next) {
        items[i++] = curr->s;
    }
    qsort(items, l->size, sizeof(char *), qsortStrcmp);
    i = 0;
    for (struct node *curr = l->head; curr != NULL; curr = curr->next) {
        curr->s = items[i++];
    }
    free(items);
}

static int qsortStrcmp(const void *ptr1, const void *ptr2) {
    char *s1 = *(char **)ptr1;
    char *s2 = *(char **)ptr2;
    return strcmp(s1, s2);
}

// Prints the list, one string per line
void ListTreePrint(ListTree l, FILE *ptr) {
    for (struct node *n = l->head; n != NULL; n = n->next) {
        fprintf(ptr, "%s ", n->s);
    }
    fprintf(ptr, "\n");
}

/**
 * Returns true if the url being looked for is 
 * already present in the linked list
 */
bool ListTreeSearch(ListTree l, char *fileName) {

    struct node *curr = l->head;
    while (curr != NULL) {

        if (strcmp(curr->s, fileName) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}



