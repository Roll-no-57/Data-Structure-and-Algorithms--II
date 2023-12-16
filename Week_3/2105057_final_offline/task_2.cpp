/*
Name : Mosharaf Hossain Apurbo
Roll : 2105057
Offline-2
*/


#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> edges;
    vector<int> dist;
    vector<int> parent;
    int V, M, A, B, L, H, S, D;
    vector<int> result;
    vector<int> Weight;
    vector<int> originalPath;

    Solution(vector<vector<int>> &edges, vector<int> &dist, vector<int> &parent, int N, int M, int A, int B, int L, int H, int S, int D)
    {
        this->parent = parent;
        this->edges = edges;
        this->dist = dist;
        this->A = A;
        this->B = B;
        this->L = L;
        this->H = H;
        this->S = S;
        this->D = D;
        this->V = N;
        this->M = M;
        for (int i = L; i <= H; i++)
        {

            if (i != 0)
            {
                Weight.push_back(i);
            }
        }
    }

    vector<int> bellman_ford()
    {
        // Code here
        vector<int> dist(V + 1, 1e8);
        dist[S] = 0;
        vector<int> tempParent(V + 1, -1);
        tempParent[S] = -1;
        
        for (int i = 0; i < V - 1; i++)
        {
            for (auto it : edges)
            {
                int u = it[0];
                int v = it[1];
                int w = it[2];

                if (dist[u] + w < dist[v] && dist[u] != 1e8)
                {
                    dist[v] = dist[u] + w;
                    tempParent[v] = u;
                }
            }
        }
        parent = tempParent;
        // check if there is any negative cycle
        for (auto it : edges)
        {
            int u = it[0];
            int v = it[1];
            int w = it[2];

            if (dist[u] + w < dist[v] && dist[u] != 1e8)
                return {-1};
        }

        return dist;
    }

    bool isNegCycle()
    {
        // run bellman ford to find the shortest distance
        // dist = bellman_ford();
        if (dist.size() == 1)
            return true;
        else
            return false;
    }

    int shortestDistance()
    {
        // run bellman ford to find the shortest distance
        dist = bellman_ford();
        return dist[D];
    }

    pair<int, int> findMinEdgeWeight()
    {
        // run a binary search to find the minimum edge weight
        int left = 0;
        int right = Weight.size() - 1;
        int mid;

        // vector<vector<int>> newEdges = edges;
        int originalShortestPath = shortestDistance();
        originalPath = parent;

        while (left <= right)
        {
            mid = (left + right) / 2;

            // create a new graph with the new edge weight
            edges.push_back({A, B, Weight[mid]});
            int newShortestPath = shortestDistance();

            if (!isNegCycle() && newShortestPath < originalShortestPath)
            {
                right = mid - 1;
                result.push_back(Weight[mid]);
            }
            else if ((!isNegCycle() && newShortestPath == originalShortestPath))
            {
                right = mid - 1;
                if (parent != originalPath)
                    result.push_back(Weight[mid]);
            }
            else
            {
                left = mid + 1;
            }

            edges.pop_back();
        }

        pair<int, int> ans;
        auto mn = min_element(result.begin(), result.end());
        if (result.size() == 0)
        {
            ans.first = 0;
            ans.second = 0;
        }
        else
        {
            ans.first = *mn;
            edges.push_back({A, B, *mn});
            ans.second = shortestDistance();
        }

        return ans;
    }
};

int main()
{

    int N, M;
    cin >> N >> M;

    vector<vector<int>> edges(M);
    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    int A, B;
    cin >> A >> B;

    int L, H;
    cin >> L >> H;

    int S, D;
    cin >> S >> D;

    vector<int> dist(N + 1, 1e8);
    vector<int> parent(N + 1, -1);
    Solution sol(edges, dist, parent, N, M, A, B, L, H, S, D);

    if (sol.findMinEdgeWeight().first == 0)
    {
        cout << "impossible\n";
    }
    else
    {
        cout << sol.findMinEdgeWeight().first << " " << sol.findMinEdgeWeight().second << endl;
    }

    return 0;
}

/*
test case:1
4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
-50 50
1 3
output:-50 -30

test case 2:
5 6
1 2 1
2 3 2
3 5 1
3 4 2
4 5 5
1 4 3
4 2
-10 5
1 5
output:-4 2

4 4
1 2 10
2 3 12
3 4 -5
4 1 -5
2 4
5 10
1 4
output : 5 15

4 4
1 2 10
2 3 12
3 4 -5
4 1 -5
2 4
-10 10
1 4
output : -5 5

4 4
1 2 10
2 3 12
3 4 -5
4 1 15
2 4
-40 -30
1 4
output : impossible

4 4
1 2 10
2 3 10
1 4 20
4 2 30
4 3
1 20
1 3
output : impossible

*/