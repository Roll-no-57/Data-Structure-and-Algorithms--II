#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
int n, m, a, b, l, h, s, d;
struct Edge
{
    int u, v, w = INF;
};
vector<Edge> edges;
vector<int> dist, distFromB;

void bellmanFord(int src)
{
    dist[src] = 0;
    distFromB[b] = 0;
    for (int i = 0; i < n; i++)
    {
        for (Edge &e : edges)
        {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;
            
            if (distFromB[e.u] != INF && distFromB[e.u] + e.w < distFromB[e.v])
                distFromB[e.v] = distFromB[e.u] + e.w;
        }
    }
}

int main()
{
    cin >> n >> m;
    dist.resize(n, INF);
    distFromB.resize(n, INF);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--; // 0-based
        edges.push_back({u, v, w});
    }
    cin >> a >> b >> l >> h >> s >> d;
    a--, b--, s--, d--; // 0-based

    bellmanFord(s);

    int distAB = dist[b] - dist[a];
    int distBA = distFromB[a];

    if (distAB < l || h < (-distBA)) // (i) no improvement possible (ii) any number between range [l, h] will create negative cycle
        cout << "impossible" << endl;
    else // answer exists
        cout << max(l, -distBA) << ' ' << dist[d] - distAB + max(l, -distBA) << endl;

    return 0;
}