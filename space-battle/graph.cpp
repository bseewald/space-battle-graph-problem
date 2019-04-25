#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct node* createNode(int v)
{
    struct node* newNode = (node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int vertex)
{
    struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
    graph->numVertex = vertex;
    graph->adjLists = (node**)malloc(vertex * sizeof(struct node*));
 
    int i;
    for (i = 0; i < vertex; i++)
        graph->adjLists[i] = NULL;
 
    return graph;
}
 
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->numVertex; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}