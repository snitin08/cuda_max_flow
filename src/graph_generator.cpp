#include <bits/stdc++.h>
#include "graph_generator.h"

using namespace std;

// Define the number of runs for the test data
// generated
#define RUN 1

// Define the maximum number of vertices of the graph
#define MAX_VERTICES 0

// Define the maximum number of edges
#define MAX_EDGES INT_MAX

// Define the maximum weight of edges
#define MAXWEIGHT 100

void Graph_Generator::generate(int nVertices)
{

    set<pair<int, int>> container;
    set<pair<int, int>>::iterator it;

    srand(time(nullptr));

    int NUM;     // Number of Vertices
    int NUMEDGE; // Number of Edges

    for (int i = 1; i <= RUN; i++)
    {

        NUM = nVertices;

        NUMEDGE = ((NUM * (NUM - 1)) / 2) * 0.5;

        for (int j = 1; j <= NUMEDGE; j++)
        {
            int a = rand() % NUM;
            int b = rand() % NUM;
            pair<int, int> p = make_pair(a, b);
            pair<int, int> rev_p = make_pair(b, a);

            // Search for a random "new" edge every time
            // Note - In a tree the edge (a, b) is same
            // as the edge (b, a)
            while (a == NUM - 1 || b == 0 || a == b || container.find(p) != container.end() ||
                   container.find(rev_p) != container.end())
            {
                a = rand() % NUM;
                b = rand() % NUM;
                p = make_pair(a, b);
                rev_p = make_pair(b, a);
            }
            container.insert(p);
        }

        for (it = container.begin(); it != container.end(); ++it)
        {
            int wt = rand() % MAXWEIGHT;
            printf("%d %d %d\n", it->first, it->second, wt);
        }

        container.clear();
        //printf("\n");
    }
}

int main(int argc, char **argv)
{
    Graph_Generator graphGenerator;
    graphGenerator.generate(atoi(argv[1]));
}