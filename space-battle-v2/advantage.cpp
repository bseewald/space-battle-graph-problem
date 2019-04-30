#include <stdlib.h>
#include <stdio.h>
#include "advantage.h"
#include "graph.h"

// int mstTransport(){
//     // n-b+a = caminho 1
//     // b-a = caminho 2
//     // menor entre os dois
// };

int mstRecon(struct Graph *graph, int graphVertex, int *space_battle_teleport_jumps, int *vertexNodes, int vertexNodesVisited){
    // depth
    int shipTime = 0;
    for(int i=0; i<graphVertex; i++){
        if(vertexNodes[i] == vertexNodesVisited){
            printf("[%d] %d [%d] %d\n", i, graph->timeDiscovery[i], space_battle_teleport_jumps[i], graph->timeDiscovery[space_battle_teleport_jumps[i]]);
            shipTime += abs(graph->timeDiscovery[i] - graph->timeDiscovery[space_battle_teleport_jumps[i]]);
        }
    }
    return shipTime;
};

// int mstFrigata(){
//     //LCA
// };

// int mstBomb(){
//     //BFS color
// };