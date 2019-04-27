#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct node* createNode(int v)
{
    struct node *newNode = (node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertex)
{
    struct Graph *graph = (Graph*)malloc(sizeof(struct Graph));

    graph->numVertex = vertex;
    graph->visited = (int*)malloc(vertex * sizeof(int));
    graph->timeDiscovery = (int*)malloc(vertex * sizeof(int));
    graph->timeClose = (int*)malloc(vertex * sizeof(int));
    graph->adjLists = (node**)malloc(vertex * sizeof(struct node*));

    int i;
    for (i = 0; i < vertex; i++){
        graph->visited[i] = 0; // White
        graph->timeDiscovery[i] = 0;
        graph->timeClose[i] = 0;
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    //src to dest
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    //dest to src
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