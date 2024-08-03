// Binary Search Tree ADT implementation 

//
// Description - This program is the BST ADT which is used to store words in it's
// node. It is used to store a complete databse of words in all urls listed.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "BSTree.h"
#include "ListTree.h"

#define data(tree)  ((tree)->word)
#define left(tree)  ((tree)->left) 
#define right(tree) ((tree)->right)

typedef struct Node {
   char *word;
   Tree left, right;
   ListTree urlList;
} Node;

// make a new node containing data
Tree newNode(Item word, Item url) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = word;
   
   left(new) = right(new) = NULL;
   new->urlList = ListTreeNew();
   ListTreeAppend(new->urlList, url);
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {

   if (t == NULL) {
      return;
   }
   freeTree(left(t));
   freeTree(right(t));

   ListTreeFree(t->urlList);
   free(t->word);
   free(t);
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, Item fileName) {
   if (t == NULL)
      t = newNode(it, fileName);
   else if (strcmp(it, data(t)) == 0) {
      // if url doesnt already exist in the linked list append it
      if (ListTreeSearch(t->urlList, fileName) == false) {
         ListTreeAppend(t->urlList, fileName);
      }
      free(it);
      ListTreeSort(t->urlList);

   } else if (strcmp(it, data(t)) < 0)
      left(t) = TreeInsert(left(t), it, fileName);
   else if (strcmp(it, data(t)) > 0)
      right(t) = TreeInsert(right(t), it, fileName);
   return t;
}

/**
 * Function prints contents of tree in which word is printed and next to it are 
 * the list of urls the word is present it
 */
void printTree(Tree t, FILE *ptr) {

   if (t == NULL) {
      return;
   }

   printTree(left(t), ptr);
   fprintf(ptr,"%s ",t->word);
   ListTreePrint(t->urlList, ptr);
   printTree(right(t), ptr);
}











