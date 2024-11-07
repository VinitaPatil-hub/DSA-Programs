#include <iostream>

using namespace std;

const int INF = 1000000; // Large constant to represent infinity
const int MAX_NODES = 5; // Adjust based on the number of nodes

class Graph {
public:
    int nodes;
    int adjMatrix[MAX_NODES][MAX_NODES];

    Graph(int n) : nodes(n) {
        // Initialize adjacency matrix with 0
        for (int i = 0; i < MAX_NODES; ++i) {
            for (int j = 0; j < MAX_NODES; ++j) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void primMST() {
        int key[MAX_NODES];      // To store the minimum weight edge for each node
        bool inMST[MAX_NODES];   // Track nodes included in the MST
        int parent[MAX_NODES];   // Array to store the MST

        // Initialize all keys as infinity and inMST as false
        for (int i = 0; i < nodes; ++i) {
            key[i] = INF;
            inMST[i] = false;
        }

        key[0] = 0;  // Start with the first node by setting its key to 0
        parent[0] = -1;  // The root node doesn't have a parent

        for (int count = 0; count < nodes - 1; ++count) {
            // Find the node with the minimum key value not yet included in MST
            int minKey = INF, minIndex;
            for (int v = 0; v < nodes; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }

            int u = minIndex;  // Pick the node to be included in MST
            inMST[u] = true;   // Include this node in the MST

            // Update the key values of adjacent vertices not yet in MST
            for (int v = 0; v < nodes; ++v) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print the constructed MST
        cout << "Prim's MST:\n";
        for (int i = 1; i < nodes; ++i) {
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << adjMatrix[i][parent[i]] << endl;
        }
    }
};

int main() {
    int nodes = 5;
    Graph g(nodes);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.primMST();

    return 0;
}

