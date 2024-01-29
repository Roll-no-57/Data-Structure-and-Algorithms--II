#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2 ;
    queue<int> q;
    q.push(s);
    q.pop()


    int new_flow = INF;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next])
            {
                parent[next] = cur;
                new_flow = min(new_flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(next);
            }
        }
    }

    return 0;
}

int maxflow(int s, int t)
{
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent))
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {

            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;

        }
    }

    return flow;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m;
    cin >> n >> m;
    capacity = vector<vector<int>>(n, vector<int>(n, 0));
    adj = vector<vector<int>>(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = c;
    }

    cout << maxflow(0, n - 1) << endl;

    return 0;
}

/*
test case :1
6 9
0 1 7
0 2 4
2 1 3
2 3 2
1 4 5
1 3 3
3 4 3
3 5 5
4 5 8
output : 10

test case :2
6 9
0 1 2
0 2 8
1 2 2
2 3 6
1 4 7
1 3 3
4 3 2
3 5 4
4 5 8
output : 6
*/
