// Implementation of the pagerank.c using a Graph ADT

//
// Description - This program uses a simple iteration of the famous pagerank
// formula to calculate the pagerank of each url file listed. A graph structure
// is built to allow understanding of outdegree and indegree of each url.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"

#define MAX_LENGTH_URL 101
#define MAX_LENGTH_STR 1001

const char *const START_MARKER = "#start";
const char *const MARKER = "Section-1";
const char *const END_MARKER = "#end";

struct urlInfo {
    double PageRank;
    char *url;
    int outdegree;
};

static char *addTxt(char str[]);
static int numUrls();
static void urlIndexed(Graph g);
static void processLine(char *toUrl, char *fromUrl, Graph g);
static double outgoingLinkSums(int index, double currentPr[], Graph g);
static double diffCalc(double currentPr[], double nextPr[], int nV);
static void sortUrlArray(struct urlInfo urlInfoArray[], int size);
static void printOutUrlInfo(struct urlInfo urlInfoArray[], int size);

int main(int argc, char **argv) {
    
    int numUrl = numUrls();
    Graph g = GraphNew(numUrl);
    // creates indexes for each url 
    urlIndexed(g);

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

        bool inBetween = true;
        char buffer[MAX_LENGTH_URL];
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
                processLine(buffer, str, g);
            }
            strcpy(prev, buffer);
        }
        free(fileName);
        fclose(url);
    }
    fclose(fp);

    // records the outdegree for each url according to url index
    urlOutdegreeCreate(g);

    double nV = GraphNumVertices(g);
    // array to store pageranks
    double *currentPr = malloc(nV * sizeof(double));
    if (currentPr == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    double *nextPr = malloc(nV * sizeof(double));
    // array to store pageranks
    if (nextPr == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // iteration 0 
    for (int i = 0; i < nV; i++) {
        currentPr[i] = 1 / nV;
    }

    int iteration = 0;
    char *ptr;
    double diffPr = strtod(argv[2], &ptr);
    double diff = diffPr;
    double dampF = strtod(argv[1], &ptr);
    int maxIt = strtod(argv[3], &ptr);

    while (iteration < maxIt && diff >= diffPr) {

        for (int indicator = 0; indicator < nV; indicator++) {
            // sum of set of pages with outgoing link to index (indicator) of url
            double outgoingLinkSum = outgoingLinkSums(indicator, currentPr, g);
            // calcualting page rank for t+1 iteration
            nextPr[indicator] = ((1 - dampF) / nV) + (dampF * outgoingLinkSum);
        }

        diff = diffCalc(currentPr, nextPr, nV);
        //transfering information from present iteration to past iteration array
        for (int j = 0; j < nV; j++) {
            currentPr[j] = nextPr[j];
        }
        iteration++;
    }
    // array of structs for each url so it can be sorted easily
    struct urlInfo urlInfoArray[GraphNumVertices(g)];
    for (int j = 0; j < nV; j++) {

        struct urlInfo url;
        url.PageRank = currentPr[j];
        url.url = MapsIdtoURL(g, j);
        url.outdegree = urlOutdegreeReturn(g, j);
        urlInfoArray[j] = url;
        
    }

    sortUrlArray(urlInfoArray, nV);
    printOutUrlInfo(urlInfoArray, nV);

    free(currentPr);
    free(nextPr);
    GraphFree(g);

    return 0;
}

/**
 * Sorts th urlInfoArray array in descending order of pagerank
 * using bubble sort
 */
static void sortUrlArray(struct urlInfo urlInfoArray[], int size) {

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (urlInfoArray[j].PageRank < urlInfoArray[j + 1].PageRank) {
                // Swap logic without a separate function
                struct urlInfo temp = urlInfoArray[j];
                urlInfoArray[j] = urlInfoArray[j + 1];
                urlInfoArray[j + 1] = temp;
            }
        }
    }
}

/**
 * Prints all the parameters according to assingment specifications to 
 * stdout
 */
static void printOutUrlInfo(struct urlInfo urlInfoArray[], int size) {

    FILE *fptr = fopen("pagerankList.txt", "w");

    for (int i = 0; i < size; i++) {
        fprintf(fptr, "%s, %d, %.7lf\n", urlInfoArray[i].url, 
                urlInfoArray[i].outdegree, urlInfoArray[i].PageRank);
    }
    fclose(fptr);
}

/**
 * Function finds the set of of pages with outgoing links to passed in url index.
 * The value for this page/url is calculated and added to the next page's value
 * until set of pages haas been all calculated for
 */
static double outgoingLinkSums(int index, double currentPr[], Graph g) {

    double holder = 0;
    double value = 0;
    for (int i = 0; i < GraphNumVertices(g); i++) {

        for (int j = 0; j < GraphNumVertices(g); j++) {
            // checks for self loops 
            if (i != index && j == index) {
                // checks if there is an outgoing link from a given url index to 
                // specified url (passed into function)
                if (EdgePresent(i, j, g) == true) {
                    value = currentPr[i] / urlOutdegreeReturn(g, i);
                    holder = value + holder;
                }
            }
        }
    }
    return holder;
}

/**
 * Function calculated the new diffrence by subtracting the next iteration 
 * pagerank from current iteration pagerank
 */
static double diffCalc(double currentPr[], double nextPr[], int nV) {

    double val = 0;
    double holder = 0;

    for (int i = 0; i < nV; i++) {
        val = fabs(nextPr[i] - currentPr[i]);
        //summation for each diff for each index
        holder = val + holder;
    }
    return holder;
}

/**
 * If both urls are valid, function adds an edge with vertices being the
 * index of both urls.
 */
static void processLine(char *toUrl, char *fromUrl, Graph g) {

    // check if urls are part of delimiting lines
    if (strcmp(toUrl, START_MARKER) != 0 && strcmp(toUrl, END_MARKER) != 0 && 
        strcmp(toUrl, MARKER) != 0) {

        int toUrlIndex = MapUrlId(g, toUrl);
        int fromUrlIndex = MapUrlId(g, fromUrl);
        // checks for no self loops 
        if (toUrlIndex != fromUrlIndex) {
            
            struct edge e;
            e.v = fromUrlIndex;
            e.w = toUrlIndex;
            GraphInsertEdge(g, e);
        }
    }
}

/**
 * Function returns the amount of urls in file collection.txt
 */
static int numUrls() {

    FILE *ptr = fopen("collection.txt", "r");

    if (ptr == NULL) {
        fprintf(stderr, "Can't open %s\n", "collection.txt");
        exit(EXIT_FAILURE);
    }
    
    int count = 0;
    char url[MAX_LENGTH_URL];
    while (fscanf(ptr, "%s", url) != EOF) {
        count++;
    }
    fclose(ptr);
    return count;
}

// create index for url
/**
 * Function creates an index for the url vy adding string to urlIndex array in 
 * graph struct 
 */
static void urlIndexed(Graph g) {

    FILE *ptr = fopen("collection.txt", "r");

    if (ptr == NULL) {
        fprintf(stderr, "Can't open %s\n", "collection.txt");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    char url[MAX_LENGTH_URL];

    while (fscanf(ptr, "%s", url) != EOF) {
        CreateUrlIndex(g, url, i);
        i++;
    }
    fclose(ptr);
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