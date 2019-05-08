#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdlib.h>
#include "graph.h"
#include "dfs.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "\nMissing filenames. Exiting...\n";
        return -1;
    }

    ifstream infile(argv[1]); // Open file

    if (infile.is_open() && infile.good()) {
        int totalEdges, combatStations, teleportAmountAvaliable, n, m;

        infile >> n >> m; // Read first line
        combatStations = n;
        totalEdges = teleportAmountAvaliable = m;

        int *space_battle_results = (int*)malloc(5 * sizeof(int));

        // Considering first vertex as 1 not 0, so +1 position required
        struct Graph *graph = createGraph(combatStations + 1);

        while (infile >> n >> m)
        {
            // Read M lines
            if(totalEdges > 0){
                addEdge(graph, n, m); // Create adjacency list
                totalEdges--;
            }
            else{
                // DFS algorithm on graph
                DFS(graph, combatStations, space_battle_results);
                break;
            }
        }
        infile.close();

        ofstream outfile(argv[2]);
        if(outfile.is_open()){ // Write output file
            outfile << space_battle_results[0] << " " << space_battle_results[1] << " "
                    << space_battle_results[2] << " " << space_battle_results[3];
            outfile << "\n";
            outfile << space_battle_results[4];
            outfile.close();
        }

        free(space_battle_results);
        free(graph);
    } else {
        cout << "\nFailed to open file\n";
    }
    return 0;
}
