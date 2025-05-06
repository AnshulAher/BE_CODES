#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

vector<vector<int>> tree;
vector<bool> visited;

// Parallel BFS using queue
void parallelBFS(int root) {
    int n = tree.size();
    visited.assign(n, false);
    queue<int> q;
    visited[root] = true;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < level_size; i++) {
            int node;

            #pragma omp critical
            {
                node = q.front(); q.pop();
                cout << node << " ";
            }

            for (int child : tree[node]) {
                if (!visited[child]) {
                    #pragma omp critical
                    {
                        if (!visited[child]) {
                            visited[child] = true;
                            q.push(child);
                        }
                    }
                }
            }
        }
    }
}

// Parallel DFS using stack
void parallelDFS(int root) {
    int n = tree.size();
    visited.assign(n, false);
    stack<int> s;
    s.push(root);
    visited[root] = true;

    while (!s.empty()) {
        int node;

        #pragma omp critical
        {
            node = s.top(); s.pop();
            cout << node << " ";
        }

        // Push children in reverse to maintain order
        #pragma omp parallel for
        for (int i = tree[node].size() - 1; i >= 0; i--) {
            int child = tree[node][i];
            if (!visited[child]) {
                #pragma omp critical
                {
                    if (!visited[child]) {
                        visited[child] = true;
                        s.push(child);
                    }
                }
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter number of nodes: ";
    cin >> nodes;

    tree.resize(nodes);
    cout << "Enter number of edges (for tree = nodes - 1): ";
    cin >> edges;

    cout << "Enter " << edges << " edges (parent child):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u); // undirected edge
    }

    int root;
    cout << "Enter root node: ";
    cin >> root;

    cout << "\nParallel BFS:\n";
    parallelBFS(root);

    cout << "\n\nParallel DFS:\n";
    parallelDFS(root);

    cout << endl;
    return 0;
}

// Time Complexity - O(V+E) for both DFS and BFS
// Space Complexity - O(V) for both DFS and BFS
