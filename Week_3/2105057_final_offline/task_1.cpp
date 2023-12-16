/*
Name : Mosharaf Hossain Apurbo
Roll : 2105057
Offline-2
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

const int MXN = 110;
const int MXM = 1100;
const int MXC = 110;

//all global variables
int n, m;


vector<int> G[MXN];
vector<int> p(MXN);
vector<vector<int>> d(MXN, vector<int>(MXC, INF));
vector<vector<int>> vis(MXN, vector<int>(MXC, 0));

//edge class
struct Edge
{
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0)
    {
        this->u = u,
        this->v = v,
        this->w = w;
    }
};

vector<Edge> E;

//add edge to the graph
void addedge(int u, int v, int w)
{
    E.push_back(Edge(u, v, w));
    G[u].push_back(E.size() - 1);
}

//vertex class
struct Vertex
{
    int v;
    int d, r;
    Vertex() {}
    Vertex(int v, int d, int r)
    {
        this->v = v, this->d = d, this->r = r;
    }

    bool operator<(const Vertex &oth) const
    {
        return d > oth.d;
    }
};


int extendedDijstra(int c, int s, int t)
{

    priority_queue<Vertex> pq;
    d[s][0] = 0;

    pq.push(Vertex(s, d[s][0], 0));

    while (!pq.empty())
    {
        int u = pq.top().v, r = pq.top().r;
        pq.pop();

        if (u == t)
            return d[u][r];
        if (vis[u][r])
            continue;
        else
            vis[u][r] = 1;

      

        for (int i = 0; i < G[u].size(); i++)
        {
            Edge &e = E[G[u][i]];
            int v = e.v;
            if (r < e.w || vis[v][r - e.w])
                continue;
            if (d[v][r - e.w] > d[u][r])
            {
                d[v][r - e.w] = d[u][r], pq.push(Vertex(v, d[v][r - e.w], r - e.w));
            }
        }
          if (r < c)
        {
            d[u][r + 1] = d[u][r] + p[u], pq.push(Vertex(u, d[u][r + 1], r + 1));
        }
    }
    return INF;
}

int main()
{
    int capa;
    cin >> n >> m >> capa;
    for (int i = 0; i < n; i++)
        cin >> p[i];

    E.clear();
    for (int i = 1; i <= n; i++)
        G[i].clear();

    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        u--, v--;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    int ans = extendedDijstra(capa, s, t);
    if (ans < INF)
        printf("%d\n", ans);
    else
        printf("impossible\n");
}


/*
test case:1
5 5 10
10 10 20 12 13
1 2 9
1 3 8
2 3 1
2 4 11
3 4 7
1 4
output:170

test case 2:
4 4 8
10 12 11 13
1 2 5
1 3 11
2 4 12
3 4 7
1 4
output:impossible

test case 3:
5 5 10
1 10 2 12 13
1 2 9
1 3 8
2 3 1
2 4 11
3 4 7
 1 4
output: 20

test case 4:
5 5 10
1 10 2 12 13
1 2 9
1 3 8
2 3 1
2 4 1
3 4 7
1 4
output: 10

test case 5:
4 5 9
5 3 6 2
1 2 1
2 3 3
1 3 5
3 4 1
1 4 6
1 4
output: 17
*/
