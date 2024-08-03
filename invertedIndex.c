// Implementation of the invertedIndex.c using a binary search tree (BST) and 
// linked list ADTs

//
// Description - This program produces a inverted intex database for every url 
// that exists for a word/string. Uses BST in which every node consists of a 
// word and a pointer to a linked list contains all the urls that contain 
// such word.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "BSTree.h"
#include "ListTree.h"

#define MAX_LENGTH_STR 1001
#define MAX_LENGTH_URL 101

const char *const START_MARKER = "#start";
const char *const MARKER = "Section-2";
const char *const END_MARKER = "#end";

static char *addTxt(char str[]);
static Tree processLine(char *line, Tree t, char *fileName);
static char *normalise(char *word); 
static char *lowerCaseWord(char *word);


int main(void) {

    Tree t = newTree();
    FILE *fp = fopen("collection.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", "collection.txt");
        exit(EXIT_FAILURE);
    }

    char str[MAX_LENGTH_URL];
    while (fscanf(fp, "%s", str) != EOF) {
        // append .txt to url so it can be opened
        char *fileName = addTxt(str);
        FILE *url = fopen(fileName, "r");
        
        bool inBetween = false;
        char buffer[MAX_LENGTH_STR];
        char prev[MAX_LENGTH_URL] = " ";
       
        while (fscanf(url, "%s", buffer) != EOF) {  
            // check if previous words and current word is part of delimiting lines
            // to turn on bool variable
            if (strcmp(buffer, MARKER) == 0 && strcmp(prev, START_MARKER) == 0) {
                inBetween = true;
            }
            // check if previous words and current word is part of delimiting lines
            // to turn off bool variable
            if (strcmp(buffer, MARKER) == 0 && strcmp(prev, END_MARKER) == 0) {
                inBetween = false;
                break;
            }

            if (inBetween == true) {
                t = processLine(buffer, t, str);
            }
            strcpy(prev, buffer);
        }  
        free(fileName);
        fclose(url);
    }
    fclose(fp);

    FILE *fptr = fopen("invertedIndex.txt", "w");
    printTree(t, fptr);
    freeTree(t);
    fclose(fptr);

    return 0;
}

/**
 * Function normalises word so that certain punctuation marks don't 
 * exist at the end of a word
 */
static char *normalise(char *word) {

    for (int i = strlen(word) - 1; i >= 0; i--) {
        // if word has the following puncuation at the end of string
        // place null terminator
        if (!(word[i] == '.' || word[i] ==','|| 
            word[i] == ':' || word[i] == ';' || 
            word[i] == '?' || word[i] == '*')) {

            break;
        } else {
            word[i] = '\0';
        }
    }
    return lowerCaseWord(word);
}

/**
 * Function converts every upper cuase word to lowercase
 */
static char *lowerCaseWord(char *word) {

    for (int i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

/**
 * Function normalises word so that certain punctuation marks don't 
 * exist at the end of a word
 */
static Tree processLine(char *line, Tree t, char *fileName) {

    if (strcmp(line, START_MARKER) != 0 && strcmp(line, END_MARKER) != 0 && 
        strcmp(line, MARKER) != 0) {
        
        char *normalisedWord = normalise(line);
        // only if string/word is not empty should it be inserted in tree
        if (normalisedWord[0] != '\0') {
           
            char *copyWord = malloc(sizeof(char) * (strlen(normalisedWord) + 1));
            strcpy(copyWord, normalisedWord);
            t = TreeInsert(t, copyWord, fileName);
        }
    }
    return t;
}

/**
 * Function appends .txt to the end of the url
 */
static char *addTxt(char str[]) {

    char *fileExtension = ".txt";
    size_t len = strlen(str) + strlen(fileExtension) + 1;
    char *fullFile = malloc(len);
    // appends .txt to url and places new string in variable
    snprintf(fullFile, len, "%s%s", str, fileExtension);

    return fullFile;
}