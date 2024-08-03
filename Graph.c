// Implementation of the directed Weighted Graph ADT
// Uses an adjacency matrix

//
// Description - This program uses graph ADT to fully store url connections/
// outdegree. The graph uses an adjacency matrix of booleans to store these 
// outdegrees as true and another array to create indexes for each url

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Graph.h"

#define MAX_LENGTH_URL 101

struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    bool **urlConnections; // adjacency matrix storing url connections.
    char **urlIndex;    // index for each url
    int *outDegree;  // outdegree for each url

};

static bool validVertex(Graph g, Vertex v);
int MapUrlId (Graph g, char *url);
void CreateUrlIndex(Graph g, char *url, int index);
void urlOutdegreeCreate(Graph g);
int urlOutdegreeReturn(Graph g, int urlIndex);
bool EdgePresent(int v, int w, Graph g);
char *MapsIdtoURL(Graph g, int urlId);

// Creates graph struct
Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->urlConnections = malloc(nV * sizeof(bool *));
    if (g->urlConnections == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        //calloced so everything is set to false
        g->urlConnections[i] = calloc(nV, sizeof(bool));
        if (g->urlConnections[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    g->urlIndex = malloc(nV * sizeof(char *));
    if (g->urlIndex == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nV; i++) {
        g->urlIndex[i] = malloc(MAX_LENGTH_URL * sizeof(char));
        if (g->urlIndex[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    g->outDegree = malloc(nV * sizeof(int));
    if (g->outDegree == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return g;
}

// Frees graph struct
void GraphFree(Graph g) {
    
    for (int i = 0; i < g->nV; i++) {
        free(g->urlConnections[i]);
    }
    free(g->urlConnections);

    for (int i = 0; i < g->nV; i++) {
        free(g->urlIndex[i]);
    }
    free(g->urlIndex);
    free(g->outDegree);

    free(g);
}

// Returns number of vertices in graph
int GraphNumVertices(Graph g) {
    return g->nV;
}

/**
 * Maps/returns id to URL being looked for and returns index of that url.
 */
int MapUrlId(Graph g, char *url) {

    int holder = 0;
    for (int i = 0; i < g->nV; i++) {

        if (strcmp(g->urlIndex[i], url) == 0) {
            holder = i;
            break;
        }
    }
    return holder;
}

/**
 * Maps/returns url string according to the given url index
 */
char *MapsIdtoURL(Graph g, int urlId) {
    return g->urlIndex[urlId];
}

/**
 * Places url string into a index of the urlIndex array. This index of the 
 * array becomes index of the url
 */
void CreateUrlIndex(Graph g, char *url, int index) {
    strcpy(g->urlIndex[index], url);
}

/**
 * Function calculates the outdegree for every url index
 */
void urlOutdegreeCreate(Graph g) {

    int count = 0;
    for (int i = 0; i < g->nV; i++) {

        for (int j = 0; j < g->nV; j++) {
            // checking if edge is present, representing an outlink
            if (g->urlConnections[i][j] == true) {
                count++;
            }
        }
        g->outDegree[i] = count;
        count = 0;
    }
}

/**
 * Maps/returns outdegree of a url according to the given url index
 */
int urlOutdegreeReturn(Graph g, int urlIndex) {
    return g->outDegree[urlIndex];
}

// Inserts edge into the graph
bool GraphInsertEdge(Graph g, struct edge e) {

    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    // checking if its a self link
    assert(e.v != e.w);

    // if edge is not already there
    if (g->urlConnections[e.v][e.w] == false) {
        g->urlConnections[e.v][e.w] = true;  // edge created
        g->nE++;
        return true;
    } else {
        return false;
    }
}

/**
 * Returns true if edge is present
 */
bool EdgePresent(int v, int w, Graph g) {

    if (g->urlConnections[v][w] == true) {
        return true;
    }
    return false;
}

// checks if vertex is valid
static bool validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}