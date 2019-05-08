#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dfs.h"
#include "advantage.h"

// Global variables
int nVertex = 0;
int nEdges = 0;
int nLeaves = 0;
int totalTime = 0;

// Recursive algorithm
int* DFS(struct Graph *graph, int graphVertex, int *space_battle_results, int *space_battle_teleport_jumps){

    int shipTime;
    int vertexNodesVisited = 1;
    int *vertexNodes = (int*)malloc(graphVertex+1 * sizeof(int));

    // Initialize values
    for(int i=0; i<=graphVertex; i++){
        vertexNodes[i] = 0;
    }

    for(int i=0; i<4; i++){
        space_battle_results[i] = 0;
    }
    space_battle_results[4] = 64000;

    // For each vertex on graph
    for(int i=1; i<graphVertex; i++){
        if(graph->visited[i] == 0){ // White vertex
            DFS_Visit(graph, i, vertexNodes, vertexNodesVisited);

            //printf("%d %d %d \n", nVertex, nEdges, nLeaves);

            // Check ships
            if(nVertex == (nEdges/2)){
                // Transport
                space_battle_results[3] += 1;
                // shipTime = mstTransport(graph, space_battle_teleport_jumps, vertexNodes);
            }
            else if((nEdges/2) == (nVertex - 1)){
                if(nLeaves == 2){
                    // Recon
                    space_battle_results[0] += 1;
                    shipTime = mstRecon(graph, graphVertex, space_battle_teleport_jumps, vertexNodes, vertexNodesVisited);
                    printf("TIME: %d\n", shipTime);
                }
                else{
                    // Frigata
                    space_battle_results[1] += 1;
                    //shipTime = mstFrigata();
                }
            }
            else{
                // Bomb
                space_battle_results[2] += 1;
                //shipTime = mstBomb();
            }

            // Advantage time
            // if(shipTime < space_battle_results[4]){
            //     space_battle_results[4] = shipTime;

            //     // Lowest time possible -- Testar!
            //     if(shipTime == 0){
            //         break;
            //     }
            // }

            vertexNodesVisited++;
        }
        nVertex = nEdges = nLeaves = 0;
    }

    // Ships
    // printf("\nSHIPS:\n");
    // for(int i=0; i<4; i++){
    //     printf("%d ", space_battle_results[i]);
    // }
    // printf("\n%d\n", space_battle_results[4]);

    free(vertexNodes);
    return space_battle_results;
}

int* DFS_Visit(struct Graph *graph, int vertex, int *vertexNodes, int vertexNodesVisited) {

    int nNeighbors = 0;

    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    totalTime += 1;
    graph->timeDiscovery[vertex] = totalTime;
    graph->visited[vertex] = 1; // Gray vertex
    vertexNodes[vertex] = vertexNodesVisited;

    while(temp != NULL) {
        nNeighbors +=1;
        int connectedVertex = temp->vertex;
        if(graph->visited[connectedVertex] == 0) {
            DFS_Visit(graph, connectedVertex, vertexNodes, vertexNodesVisited);
        }
        temp = temp->next;
    }
    totalTime += 1;
    nVertex +=1;
    nEdges += nNeighbors;
    if(nNeighbors == 1)
        nLeaves +=1;

    graph->timeClose[vertex] = totalTime;
    graph->visited[vertex] = 2; // Black vertex

    return vertexNodes;
}