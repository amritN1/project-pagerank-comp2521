// Implementation of the searchPagerank.c using a linked list ADT

//
// Description - This program is acts like a search engine in which it
// pagerankList.txt. It uses the linked list ADT to store important values
// such as pagerank and url count to further sort and output highest ranked
// url to stdout.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"

#define MAX_LENGTH_STR 1001

static void findPageRank(List l);

int main(int argc, char **argv) {
   
    List l = ListNew();
    for (int i = 1; i < argc; i++) {    

        FILE *fp = fopen("invertedIndex.txt", "r");  
        if (fp == NULL) {
            fprintf(stderr, "Can't open %s\n", "invertedIndex.exp");
            exit(EXIT_FAILURE);
        }
        char str[MAX_LENGTH_STR];
        while (fgets(str, MAX_LENGTH_STR, fp) != NULL) {
            // remove new line characters
            str[strcspn(str, "\n")] = 0;
            char *compare = strstr(str, argv[i]);
            if (compare != NULL) {
        
                const char s[2] = " ";
                char *token;
                token = strtok(str, s);
               // go through each line/string of file and find each word
               // add it to the list
                while (token != NULL) {
                    
                    token = strtok(NULL, s);
                    if (token != NULL && listCheck(l, token) == false) {
                        ListAppend(l, token);
                    } else if (token != NULL && listCheck(l, token) == true) {
                        listUpdateUrlCount(l, token);
                    }
                }
            }
        }
        fclose(fp);
    }
    findPageRank(l);
    sortUrlCount(l);
    sortPageRank(l);
    outputUrl(l);
    ListFree(l);

    return 0;
}

/**
 * Opens the pagerankList.txt file and reads every line. Upon 
 * reading every line it finds the url according pagerank
 */
static void findPageRank(List l) {

    FILE *fp = fopen("pagerankList.txt", "r"); 

    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", "pagerankList.exp");
        exit(EXIT_FAILURE);
    }

    char str1[MAX_LENGTH_STR];
    while (fgets(str1, MAX_LENGTH_STR, fp) != NULL) {
        // remove new line characters
        str1[strcspn(str1, "\n")] = 0;
        const char s[3] = ", ";
        char *token;
        char *url;
        char *rank;
        token = strtok(str1, s);
        url = token;
        // go through each line/string of file and find url's pagerank
        while (token != NULL) {

            rank = token;
            token = strtok(NULL, s);
        }
        // finds pagerank for a specific url
        matchUrl(l, url, rank);
    }
    fclose(fp);
}


