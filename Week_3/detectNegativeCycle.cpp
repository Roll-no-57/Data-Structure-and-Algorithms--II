#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;
const int INF = 1000000000;

void solve() {
    vector<int> d(n, INF);
    vector<int> p(n, -1);
    int x;

    for (int i = 0; i < n - 1; ++i) {
        x = -1;
        for (Edge e : edges) {
            if (d[e.a] + e.cost < d[e.b]) {
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if (x == -1) {
        cout << "No negative cycle found.";
    } else {
        for (int i = 0; i < n; ++i)
            x = p[x];

        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        cout << "Negative cycle: ";
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
    }
}

int main() {
    cout << "Enter the number of nodes (n) and edges (m): ";
    cin >> n >> m;

    cout << "Enter the edges (a, b, cost):" << endl;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].a >> edges[i].b >> edges[i].cost;
    }

    solve();

    return 0;
}
/*
Input:
4 5
3 4 2
3 1 3
1 2 2
4 2 2
2 3 -10

*/