/*
offline 4:
task : find the maximum matching for a matrimonial site

Author : Mosharaf Hossain Apurbo
Roll: 2105057
Date : 06-01-2023

*/

#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

// n is the number of nodes and m is the number of edges
int n;

// capacity stores the capacity of each edge and adj stores the adjacent nodes of each node
vector<vector<int>> capacity;
vector<vector<int>> adj;
// bfs function to find the augmenting path and the bottleneck flow of that path
int bfs(int s, int t, vector<int> &parent)
{

    // filling the parent array with -1 because I will find the augmenting path again and again
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    // queue to store the nodes
    queue<pair<int, int>> q;
    q.push({s, INF});

    // looping until the queue is empty
    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        // looping through all the adjacent nodes of the current node
        for (int next : adj[cur])
        {
            // if a adjacent node is not visited yet and the capacity of the edge is not 0 then we will find a path
            // to that node
            if (parent[next] == -1 && capacity[cur][next])
            {
                parent[next] = cur;

                // finding the minimum flow in the path
                int new_flow = min(flow, capacity[cur][next]);

                // if the next node is the sink then we will return the minflow in the path
                if (next == t)
                {
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }

    // if there is no path then we will return 0
    return 0;
}

int maxflow(int s, int t)
{

    // parent stores the parent of each node in the augmenting path found by bfs
    vector<int> parent(n);
    int bottleneckFlow;
    int flow = 0;

    while (bottleneckFlow = bfs(s, t, parent))
    {

        int cur = t;
        // adding the bottleneckFlow to the flow to get the maxflow
        flow += bottleneckFlow;

        while (cur != s)
        {
            int prev = parent[cur];

            // updating the capacity of the edge and its reverse edge
            capacity[prev][cur] -= bottleneckFlow;
            capacity[cur][prev] += bottleneckFlow;

            cur = prev;
        }
    }

    return flow;
}

int main()
{

    // taking input from a file
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tman, twoman;
    cin >> tman >> twoman;

    vector<vector<int>> man;
    vector<vector<int>> woman;

    // for the index of the node
    int node = 0;

    for (int i = 0; i < tman; i++)
    {
        int h, a, d;
        cin >> h >> a >> d;
        man.push_back({h, a, d, ++node});
    }

    for (int i = 0; i < twoman; i++)
    {
        int h, a, d;
        cin >> h >> a >> d;
        woman.push_back({h, a, d, ++node});
    }

    int totalNode = tman + twoman + 2;
    n = totalNode;

    capacity = vector<vector<int>>(n, vector<int>(n, 0));
    adj = vector<vector<int>>(n);

    // inserting the edges from source node to all the mans node
    for (int i = 0; i < tman; i++)
    {
        adj[0].push_back(man[i][3]);
        adj[man[i][3]].push_back(0);
        capacity[0][man[i][3]] = 1;
    }

    // inserting the edges from all the mans node to all the womans node
    for (int i = 0; i < tman; i++)
    {
        for (int j = 0; j < twoman; j++)
        {
            if (abs(man[i][0] - woman[j][0]) <= 10 && abs(man[i][1] - woman[j][1]) <= 5 && (man[i][2] == woman[j][2]))
            {
                adj[man[i][3]].push_back(woman[j][3]);
                adj[woman[j][3]].push_back(man[i][3]);

                // the capacity from man to woman is set to 1
                capacity[man[i][3]][woman[j][3]] = 1;
            }
        }
    }

    node++;
    // inserting the edges from all the womans node to sink node
    for (int i = 0; i < twoman; i++)
    {
        adj[node].push_back(woman[i][3]);
        adj[woman[i][3]].push_back(node);

        capacity[woman[i][3]][node] = 1;
    }

    cout << maxflow(0, node) << endl;

    return 0;
}

/*
test case :1
2 2
70 30 0
60 20 0
71 25 0
71 35 0

output : 1

test case :2

2 2
70 30 0
60 20 0
70 25 0
70 35 0

output : 2


*/