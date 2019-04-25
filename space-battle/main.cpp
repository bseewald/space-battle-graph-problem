#include <fstream>
#include <string.h>
#include <iostream>
#include "graph.h"

using namespace std; 

int main(int argc, char* argv[])
{ 
    if (argc < 1) {
        cout << "\nNo file names entered. Exiting...\n";
        return -1;
    }
    ifstream infile(argv[1]); // Open file
    
    if (infile.is_open() && infile.good()) {
        cout << "File is now open!\n";

        int combatStations, teleportAmountAvaliable, n, m;
        while (infile >> n >> m)
        {
            combatStations = n;
            teleportAmountAvaliable = m;
            struct Graph* graph = createGraph(combatStations);
            // TODO: continuar ...   
        }
        infile.close();

        ofstream outfile(argv[2]);
        if(outfile.is_open()){
            // Escrever R, F, B e T
            //          V
            // outfile << ;
            outfile.close();
        }
    } else {
        cout << "\nFailed to open file..\n";
    }
    return 0;
}