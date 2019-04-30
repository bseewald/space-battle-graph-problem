#include <iostream>
#include <fstream>
// #include <string.h>
#include <inttypes.h>
// #include <sys/time.h>
#include "graph.h"
#include "dfs.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 1) {
        cout << "\nNo file names entered. Exiting...\n";
        return -1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    ifstream infile(argv[1]); // Open file

    if (infile.is_open() && infile.good()) {
        int totalEdges, combatStations, teleportAmountAvaliable, n, m;

        infile >> n >> m; // Read first line
        combatStations = n;
        totalEdges = teleportAmountAvaliable = m;

        int *space_battle_teleport_jumps = (int*)malloc(n+1 * sizeof(int)); // Starts from index zero
        int *space_battle_results = (int*)malloc(5 * sizeof(int));
        struct Graph *graph = createGraph(combatStations);

        while (infile >> n >> m)
        {
            // Read M lines
            if(totalEdges > 0){
                addEdge(graph, n, m); // Create adjacency list
                totalEdges--;
            }
            else{
                // Read N lines
                space_battle_teleport_jumps[n] = m;
            }
        }
        infile.close();

        // DFS algorithm on graph
        DFS(graph, combatStations, space_battle_results, space_battle_teleport_jumps);

        ofstream outfile(argv[2]);
        if(outfile.is_open()){ // Write output file
            outfile << space_battle_results[0] << " " << space_battle_results[1] << " "
                    << space_battle_results[2] << " " << space_battle_results[3];
            outfile << "\n";
            outfile << space_battle_results[4];
            outfile.close();
        }

        free(space_battle_teleport_jumps);
        free(space_battle_results);
        free(graph);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        uint64_t delta = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        printf("\nExecution time: %" PRIu64 " microseconds\n", delta);
    } else {
        cout << "\nFailed to open file..\n";
    }
    return 0;
}