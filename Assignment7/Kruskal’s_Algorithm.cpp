#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    vector<Edge> edges;
    int nodes;
    Graph(int n) : nodes(n) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    int findParent(int node, vector<int>& parent) {
        if (parent[node] == node)
            return node;
        return findParent(parent[node], parent);
    }

    void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
        int parentU = findParent(u, parent);
        int parentV = findParent(v, parent);
        
        if (rank[parentU] > rank[parentV]) {
            parent[parentV] = parentU;
        } else if (rank[parentU] < rank[parentV]) {
            parent[parentV] = parentU;
        } else {
            parent[parentV] = parentU;
            rank[parentU]++;
        }
    }

    void kruskalMST() {
        vector<Edge> mst;
        vector<int> parent(nodes), rank(nodes, 0);
        for (int i = 0; i < nodes; i++) {
            parent[i] = i;
        }

        // Sorting edges by weight
        for (size_t i = 0; i < edges.size(); ++i) {
            for (size_t j = i + 1; j < edges.size(); ++j) {
                if (edges[i].weight > edges[j].weight) {
                    Edge temp = edges[i];
                    edges[i] = edges[j];
                    edges[j] = temp;
                }
            }
        }

        int mstWeight = 0;
        for (int i = 0; i < edges.size(); i++) {
            Edge edge = edges[i];
            int uParent = findParent(edge.src, parent);
            int vParent = findParent(edge.dest, parent);

            if (uParent != vParent) {
                mst.push_back(edge);
                mstWeight += edge.weight;
                unionSets(uParent, vParent, parent, rank);
            }
        }

        cout << "Kruskal's MST:\n";
        for (int i = 0; i < mst.size(); i++) {
            cout << "Edge: " << mst[i].src << " - " << mst[i].dest << " Weight: " << mst[i].weight << endl;
        }
        cout << "Total Weight: " << mstWeight << endl;
    }
};

int main() {
    int nodes = 5;
    Graph g(nodes);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 25);
    g.addEdge(1, 2, 5);

    g.kruskalMST();

    return 0;
}

