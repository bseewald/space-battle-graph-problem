#include <stdio.h>
#include "graph.h"
#include "dfs.h"

int nVertex = 0;
int nEdges = 0;
int nLeaves = 0;
int totalTime = 0;

int* DFS(struct Graph *graph, int graphVertex, int *space_battle_results){
    
    for(int i=0; i<4; i++)
        space_battle_results[i] = 0;
    space_battle_results[4] = 64000;

    for(int i=1; i<graphVertex; i++){
        if(graph->visited[i] == 0){
            DFS_Visit(graph, i);
            
            printf("%d %d %d \n", nVertex, nEdges, nLeaves);
            // Check ships
            if(nVertex == nEdges){
                // Transport
                space_battle_results[3] += 1;
            }
            else if((nEdges/2) == (nVertex - 1)){
                if(nLeaves == 2){
                    // Recon
                    space_battle_results[0] += 1;
                }
                else{
                    // Frigata
                    space_battle_results[1] += 1;
                }
            }  
            else{
                // Bomb
                space_battle_results[2] += 1;
            }  
            
            // TODO: Calcular tempo de vantagem
            // tNew = calcSpaceShipTime();
            // if(tNew < space_battle_results[4]){
            //     space_battle_results[4] = tNew;
            // }
        }
        nVertex = nEdges = nLeaves = 0;
    }
    
    // Ships
    printf("\nSHIPS:\n");
    for(int i=0; i<4; i++){
        printf("%d ", space_battle_results[i]);
    }
    printf("\n%d\n", space_battle_results[4]);
    
    return space_battle_results;
}

void DFS_Visit(struct Graph *graph, int vertex) {

    int nNeighbors = 0;

    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    totalTime += 1;
    graph->timeDiscovery[vertex] = totalTime;
    graph->visited[vertex] = 1; // Gray

    while(temp != NULL) {
        nNeighbors +=1;
        int connectedVertex = temp->vertex;
        if(graph->visited[connectedVertex] == 0) {
            DFS_Visit(graph, connectedVertex);
        }
        temp = temp->next;
    }
    totalTime += 1;
    nVertex +=1;
    nEdges += nNeighbors;
    if(nNeighbors == 1)
        nLeaves +=1;

    graph->timeClose[vertex] = totalTime;
    graph->visited[vertex] = 2; // Black
}