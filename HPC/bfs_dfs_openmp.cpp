#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v); // Undirected graph
    }

    void parallelDFS(int startVertex)
    {
        vector<bool> visited(V, false);
        double start_time = omp_get_wtime();

        cout << "Depth-First Search (DFS): ";

#pragma omp parallel
        {
#pragma omp single
            dfsUtil(startVertex, visited);
        }

        double end_time = omp_get_wtime();
        cout << "\nDFS Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";
    }

private:
    void dfsUtil(int v, vector<bool> &visited)
    {
        bool doVisit = false;
// only 1 thread updates/reads visited[v]..avoids race conditions
#pragma omp critical
        {
            if (!visited[v])
            {
                visited[v] = true;
                cout << v << " ";
                doVisit = true;
            }
        }

        if (!doVisit)
            return;

#pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int n = adj[v][i];
#pragma omp task
            dfsUtil(n, visited);
        }

#pragma omp taskwait
    }

public:
    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        omp_lock_t qLock;

        omp_init_lock(&qLock);

        double start_time = omp_get_wtime();

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "Breadth-First Search (BFS): ";

        while (!q.empty())
        {
            int size = q.size();

#pragma omp parallel for
            for (int i = 0; i < size; ++i)
            {
                int v;

                omp_set_lock(&qLock);
                if (!q.empty())
                {
                    v = q.front();
                    q.pop();
                    cout << v << " ";
                }
                else
                {
                    omp_unset_lock(&qLock);
                    continue;
                }
                omp_unset_lock(&qLock);

                for (int j = 0; j < adj[v].size(); ++j)
                {
                    int n = adj[v][j];
                    bool notVisited = false;

#pragma omp critical
                    {
                        if (!visited[n])
                        {
                            visited[n] = true;
                            notVisited = true;
                        }
                    }

                    if (notVisited)
                    {
                        omp_set_lock(&qLock);
                        q.push(n);
                        omp_unset_lock(&qLock);
                    }
                }
            }
        }

        double end_time = omp_get_wtime();
        cout << "\nBFS Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";

        omp_destroy_lock(&qLock);
    }
};

int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter each edge in the format 'u v' (0-based indexing):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int startVertex;
    cout << "Enter the starting vertex for DFS and BFS: ";
    cin >> startVertex;

    cout << "\n";
    g.parallelDFS(startVertex);
    g.parallelBFS(startVertex);

    return 0;
}
