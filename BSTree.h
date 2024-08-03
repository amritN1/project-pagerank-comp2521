// Binary Search Tree ADT interface 

//
// Description - This program is the BST ADT implementation which is used in 
// invertedIndex.c. It houses important function that allow tree insertion and 
// to print information held within the tree.

#include <stdbool.h>

typedef char *Item;      // item is just a key

typedef struct Node *Tree;

// create an empty Tree
Tree newTree();        

// free memory associated with Tree
void freeTree(Tree);   

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, Item fileName); 

/**
 * Function prints contents of tree in which word is printed and next to it are 
 * the list of urls the word is present it
 */
void printTree(Tree t, FILE *ptr);