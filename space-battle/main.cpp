#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/time.h>
#include "graph.h"
#include "dfs.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 1) {
        cout << "\nNo file names entered. Exiting...\n";
        return -1;
    }
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    ifstream infile(argv[1]); // Open file
    
    if (infile.is_open() && infile.good()) {
        int totalEdges, combatStations, teleportAmountAvaliable, n, m;
        
        infile >> n >> m; // First line
        combatStations = n;
        totalEdges = teleportAmountAvaliable = m;

        int *space_battle_results = (int*)malloc(5 * sizeof(int));
        struct Graph *graph = createGraph(combatStations);
        
        while (infile >> n >> m)
        {
            if(totalEdges > 0){
                // Adjacency list
                addEdge(graph, n, m);
                totalEdges--;
            }
            else{
                DFS(graph, combatStations, space_battle_results);
                break;
            }
        }
        infile.close();

        ofstream outfile(argv[2]);
        if(outfile.is_open()){
        //     outfile << space_battle_results[0] << space_battle_results[1] << space_battle_results[2] << space_battle_results[3];
        //     outfile << "\n";
        //     outfile << space_battle_results[4];
            outfile.close();
        }

        free(space_battle_results);
        free(graph);

        gettimeofday(&stop, NULL);
        printf("\nExecution time: %d milliseconds\n", stop.tv_usec - start.tv_usec);
    } else {
        cout << "\nFailed to open file..\n";
    }
    return 0;
}