#include <utility>
#include <bits/stdc++.h>
#include "graph_generator.h"

using namespace std;

class Network
{
private:
    unsigned short vertex_count = 0;
    //vector<string> vertex_string_representation;

    vector<vector<unsigned short>> adjacency_matrix;

    bool bfs(unsigned short vertexS, unsigned short vertexT, vector<unsigned short> &parent)
    {
        vector<bool> visited(vertex_count);

        queue<unsigned short> vertexQueue;
        vertexQueue.push(vertexS);
        visited[vertexS] = true;
        parent[vertexS] = -1;

        while (!vertexQueue.empty())
        {
            int vertexU = vertexQueue.front();
            vertexQueue.pop();

            for (int vertexV = 0; vertexV < vertex_count; vertexV++)
            {
                if (!visited[vertexV] && adjacency_matrix[vertexU][vertexV] > 0)
                {
                    //cout << "visiting " << vertexV << ",";
                    vertexQueue.push(vertexV);
                    parent[vertexV] = vertexU;
                    visited[vertexV] = true;
                }
            }
        }

        //cout << "returning- " << visited[vertexT] << endl;

        return visited[vertexT];
    }

public:
    explicit Network(unsigned short vertex_count) : vertex_count(vertex_count), adjacency_matrix(
                                                                                    vector<vector<unsigned short>>(vertex_count, vector<unsigned short>(vertex_count)))
    {
        this->vertex_count = vertex_count;
        //vertex_string_representation.resize(vertex_count);
    }

    void add_vertex_string_representation(int index, string str)
    {
        //vertex_string_representation[index] = std::move(str);
    }

    void add_edge(unsigned short from, unsigned short to, unsigned short capacity)
    {
        if (from >= vertex_count || to >= vertex_count)
        {
            return;
        }

        adjacency_matrix[from][to] = capacity;
    }

    int maxFlow(unsigned short vertexS, unsigned short vertexT)
    {
        unsigned int maxFlow = 0;
        vector<unsigned short> parent(vertex_count);
        unsigned short vertexU = 0;
        unsigned short vertexV = 0;

        while (bfs(vertexS, vertexT, parent))
        {
            string pathString;

            unsigned short bottleneckFlow = USHRT_MAX;
            for (vertexV = vertexT; vertexV != vertexS; vertexV = parent[vertexV])
            {
                vertexU = parent[vertexV];
                bottleneckFlow = min(bottleneckFlow, adjacency_matrix[vertexU][vertexV]);

                //                pathString.insert(0, to_string(vertexV));
                //                pathString.insert(0, " --> ");
            }

            //            pathString.insert(0, "S");

            //            cout << "Augmentation path: " << pathString << "\t";
            //            cout << " bottleneck (min flow on path added to max flow) = " << bottleneckFlow << endl;

            for (vertexV = vertexT; vertexV != vertexS; vertexV = parent[vertexV])
            {
                vertexU = parent[vertexV];
                adjacency_matrix[vertexU][vertexV] -= bottleneckFlow;
                adjacency_matrix[vertexV][vertexU] += bottleneckFlow;
            }

            maxFlow += bottleneckFlow;
        }

        return maxFlow;
    }
};

int main(int argc, char **argv)
{
    auto start = chrono::high_resolution_clock::now();

    if (argc < 1)
    {
        cout << "Input Filename is required" << endl;
        return 0;
    }

    ifstream file;
    file.open(argv[1]);

    if (!file)
    {
        cout << "Error reading file!";
        return 0;
    }

    int vertexCount = atoi(argv[2]);

    int vertexS = 0;
    int vertexT = vertexCount - 1;

    Network network(vertexCount);

    string line;
    unsigned short source, destination, capacity;

    while (file)
    {
        getline(file, line);
        if (line.empty())
        {
            continue;
        }

        std::stringstream linestream(line);
        linestream >> source >> destination >> capacity;

        //cout << source << "\t" << destination << "\t" << capacity << endl;

        network.add_edge(source, destination, capacity);
    }

    file.close();

    int maxflow;

    maxflow = network.maxFlow(vertexS, vertexT);

    auto duration = chrono::duration_cast<chrono::milliseconds>(start - chrono::high_resolution_clock::now());

    cout << "Network maxflow: " << maxflow << " duration -" << duration.count() << " ms" << endl;

    return 0;
}
