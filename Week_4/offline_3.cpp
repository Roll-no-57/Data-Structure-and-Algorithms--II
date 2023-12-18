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
    vector<pair<int,int>> reachable;

    // Assumed the graph is 0 based indexed and undirected
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    
    int threshold;
    cin >> threshold;

    floyedWarshall(graph, n);
    

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] <= threshold)
            {
                count++;
                
            }
        }
        reachable.push_back({count, i});
    }

    sort(reachable.begin(), reachable.end());

    cout << ++reachable[0].second << " ";
    for (int i = 1; i < n; i++)
    {
        if (reachable[i].first == reachable[0].first)
            cout << ++reachable[i].second << " ";
    }



    return 0;
}

/*
test case 1:
4 4
1 2 3
2 3 1
2 4 4
3 4 1
4
output : 1 4

test case 2:
4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9
4
output : 1 2 3 4

test case 3:
4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9
3
output : 1 3

test case 4:
5 8
1 2 2
1 3 4
1 5 8
2 3 3
2 4 5
2 5 2
3 4 1
4 5 1
4
outout : 1 4

test case 5:
5 6
1 2 2
1 5 8
2 3 3
2 5 2
3 4 1
4 5 1
2
output : 1


*/