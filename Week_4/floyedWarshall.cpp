#include <bits/stdc++.h>
using namespace std;

void floyedWarshall(vector<vector<int>> &graph, int n)
{
    // for all the intermediate nodes
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    graph[i][j] = 0;
                else 
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

void print(vector<vector<int>> &graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(n, 1e9));

    // Assumed the graph is 0 based indexed and undirected
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--,v--;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    //before floyed warshall
    cout<<"before floyed warshall\n";
    print(graph, n);

    floyedWarshall(graph, n);

    //after floyed warshall
    cout<<"after floyed warshall\n";
    print(graph, n);

    return 0;
}