#include <iostream>
#include <queue>

#define INF 999999 // A large number to represent infinity

using namespace std;

const int MAX_VERTICES = 100; // Maximum number of landmarks (vertices)

// Structure for the graph edges
struct Edge {
    int destination;
    int weight;
    Edge* next;
};

// Graph represented using an adjacency list
class Graph {
    int V; // Number of vertices
    Edge* adj[MAX_VERTICES]; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            adj[i] = NULL; // Initialize adjacency list
        }
    }

    // Add an edge between u and v with a specified weight
    void addEdge(int u, int v, int weight) {
        Edge* newEdge = new Edge{v, weight, adj[u]};
        adj[u] = newEdge;
    }

    // Dijkstra's algorithm to find shortest path from source
    void dijkstra(int src) {
        bool visited[MAX_VERTICES] = {false};
        int dist[MAX_VERTICES];

        // Initialize distances to "infinity"
        for (int i = 0; i < V; i++) {
            dist[i] = INF;
        }
        dist[src] = 0;

        // Priority queue for the minimum distance (distance, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            // Traverse neighbors
            for (Edge* e = adj[u]; e != NULL; e = e->next) {
                int v = e->destination;
                int weight = e->weight;

                // Relaxation step
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Print the shortest distance from source to each vertex
        cout << "Vertex\tDistance from Source " << src << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF)
                cout << i << "\tINF" << endl;
            else
                cout << i << "\t" << dist[i] << endl;
        }
    }
};

int main() {
    int V = 5; // Number of landmarks

    // Initialize graph with the number of vertices
    Graph g(V);

    // Add edges (landmarks and distances between them)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);

    int src = 0; // Starting landmark
    g.dijkstra(src);

    return 0;
}

