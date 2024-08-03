
// Implementation of the pagerank.c using a Graph ADT
// COMP2521 24T0 Assignment

//
// Description - This program is the interface to the Undirected Weighted Graph ADT where vertices
// are the urls present. This file is used in pagerank.c to insert outgoing links into the graph as well
// as other functions including creating url index. In this graph self loops are not allowed.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;
typedef int Vertex;

// edges are pairs of vertices (urls) (end-points)
struct edge {
  Vertex v;
  Vertex w;
};

/**
 * Creates a new instance of a graph
 */
Graph GraphNew(int nV);

/**
 * Frees all memory associated with the given graph
 */
void GraphFree(Graph g);

/**
 * Returns the number of vertices in the graph
 */
int GraphNumVertices(Graph g);

/**
 * Inserts  an  edge into a graph. Does nothing if there is already an
 * edge between `e.v` and `e.w`. Returns true if successful, and false
 * if there was already an edge.
  */
bool GraphInsertEdge(Graph g, struct edge e);

/**
 * Maps/returns id to URL being looked for and returns index of that url.
 */
int MapUrlId (Graph g, char *url);

/**
 * Maps/returns url string according to the given url index
 */
char *MapsIdtoURL(Graph g, int urlId);

/**
 * Places url string into a index of the urlIndex array. This index of the 
 * array becomes index of the url
 */
void CreateUrlIndex(Graph g, char *url, int index);

/**
 * Function calculates the outdegree for every url index
 */
void urlOutdegreeCreate(Graph g);

/**
 * Maps/returns outdegree of a url according to the given url index
 */
int urlOutdegreeReturn(Graph g, int urlIndex);

/**
 * Returns true if edge is present
 */
bool EdgePresent(int v, int w, Graph g);

//////////////////////////////////////////////////////////////////////////

#endif