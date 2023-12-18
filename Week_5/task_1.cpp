/*
offline 4:
task 1: find the maximum inflow at a node other than source and sink
task 2: find the maximum flow from source to sink

Author : Mosharaf Hossain Apurbo
Roll: 2105057
Date : 06-01-2023

*/

#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

// n is the number of nodes and m is the number of edges , s is the source and t is the sink
int n, m;
int s, t;

// capacity stores the capacity of each edge and adj stores the adjacent nodes of each node and inflow stores the inflow of each node
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> inflow;

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

            if (cur != t)
                inflow[cur] += bottleneckFlow;

            cur = prev;
        }
    }

    return flow;
}

void dfs(int s, vector<int> &s_cut, vector<int> &vis)
{
    vis[s] = 1;
    s_cut.push_back(s);

    for (auto next : adj[s])
    {
        if (!vis[next] && capacity[s][next] > 0)
        {
            dfs(next, s_cut, vis);
        }
    }
    return;
}

void print(vector<int> &v)
{
    std::cout << "{";
    for (int i = 0; i < v.size(); i++)
    {
        if (i == v.size() - 1)
        {
            std::cout << (v[i]+1);
            break;
        }
        std::cout << (v[i]+1) << ",";
    }
    std::cout << "}";
}
void printAdj()
{
    std::cout << "adj" << std::endl;
    for (auto x : adj)
    {
        for (auto y : x)
        {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void printCapacity()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << capacity[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void printMaxInflow()
{
    int mxInFlow = -1e9;
    int mxInFlowNode;
    for (int i = 0; i < n; i++)
    {
        if (inflow[i] > mxInFlow)
        {
            mxInFlow = inflow[i];
            mxInFlowNode = i + 1;
        }
    }
    std::cout << mxInFlowNode << " " << mxInFlow << std::endl;
}

int main()
{
    // taking input from a file
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;

    // initializing the capacity and adj and inflow vector
    capacity = vector<vector<int>>(n, vector<int>(n, 0));
    adj = vector<vector<int>>(n);
    inflow = vector<int>(n, 0);

    // taking input the edges and their capacity
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = c;
    }

    // taking input the source and sink
    cin >> s >> t;
    s--, t--;

    // <----------------------------Subtask_1------------------------------------>

    // calculating the maxflow from source to sink using ford fulkerson algorithm
    int mxflow =  maxflow(s, t) ;
    // printing maximum inflow
    printMaxInflow();



    // <----------------------------Subtask_2------------------------------------>
    vector<int> s_cut;
    vector<int> t_cut;
    vector<int> vis(n, 0);

    // finding the mincut using ford fulkerson algorithm
    dfs(s, s_cut, vis);

    // calculating the t_cut from s_cut
    sort(s_cut.begin(), s_cut.end());
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (s_cut[j] == i)
        {
            j++;
        }
        else
        {
            t_cut.push_back(i);
        }
    }
    sort(t_cut.begin(), t_cut.end());



    // printing the s_cut and t_cut
    cout << "[";
    print(s_cut);
    cout << ",";
    print(t_cut);
    cout << "]" << endl;

    // printing the maxflow
    cout << mxflow << endl;

    return 0;
}

/*
test case :1
6 9
1 2 7
1 3 4
3 2 3
3 4 2
2 5 5
2 4 3
4 5 3
4 6 5
5 6 8
1 6
output :2 8
[{1,2,3},{4,5,6}]
10


test case :2
6 9
1 2 16
1 3 13
3 2 4
2 4 12
3 5 14
4 3 9
5 4 7
4 6 20
5 6 4
1 6
output :4 19
[{1,2,3,5},{4,6}]
23


test case :3
6 8
1 2 5
1 4 4
4 2 3
2 3 6
3 6 5
3 5 8
5 6 2
4 5 1
1 6
output : 2 6
[{1,2,4},{3,5,6}]
7


*/