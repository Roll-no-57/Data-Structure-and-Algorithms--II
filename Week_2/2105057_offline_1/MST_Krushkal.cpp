
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int N;
    class UnionFind
    {
    public:
        vector<int> parent;
        vector<int> rank;

        UnionFind(int n)
        {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++)
            {
                parent[i] = i;
            }
        }

        int find(int u)
        {
            if (u == parent[u])
            {
                return u;
            }
            return parent[u] = find(parent[u]);
        }
        
        void Union(int u, int v)
        {
            int parent_u = find(u);
            int parent_v = find(v);

            if (parent_u == parent_v)
                return;

            if (rank[parent_u] < rank[parent_v])
                parent[parent_u] = parent_v;
            else if (rank[parent_u] > rank[parent_v])
                parent[parent_v] = parent_u;
            else
            {
                parent[parent_u] = parent_v;
                rank[parent_v]++;
            }
        }
    };

    int krushkals(vector<vector<int>> &edges, int skip_edge, int force_edge)
    {

        int sum = 0;
        UnionFind uni(N);

        if (force_edge != -1)
        {
            sum += edges[force_edge][2];
            uni.Union(edges[force_edge][0], edges[force_edge][1]);
        }

        for (int i = 0; i < edges.size(); i++)
        {

            if (i == skip_edge)
                continue;

            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            int idx = edges[i][3];

            if (uni.find(u) != uni.find(v))
            {
                sum += w;
                uni.Union(u, v);
            }
        }
        for (int i = 0; i < N; i++)
        {
            if (uni.find(i) != uni.find(0))
            {
                sum = INT_MAX;
                break; // Break once a vertex not included in MST is found
            }
        }

        return sum;
    }

    vector<vector<int>> findkrushkals(int n,vector<vector<int>> &edges)
    {
        N=n;
        vector<int> critical, pseudo_critical;

        // insert the indexes;
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].push_back(i);
        }

        // sort the edges array by their weight
        auto comparator = [&](auto &v1, auto &v2)
        {
            return v1[2] < v2[2];
        };
        sort(edges.begin(), edges.end(), comparator);

        // find the MST weight using union find
        int MST_WEIGHT = krushkals(edges, -1, -1);

        for (int i = 0; i < edges.size(); i++)
        {
            if (krushkals(edges, i, -1) > MST_WEIGHT)
            {
                critical.push_back(edges[i][3]);
            }
            else if (krushkals(edges, -1, i) == MST_WEIGHT)
            {
                pseudo_critical.push_back(edges[i][3]);
            }
        }

        return {critical, pseudo_critical};
    }
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    int vertices = n;
    vector<vector<int>> ans;
    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back({u, v, weight});
    }

    Solution s;
    ans = s.findkrushkals(vertices,edges);

    // printing the answer
    cout << "Critical Edges : [";
    for (int i = 0; i < ans[0].size(); i++)
    {
        if (i == ans[0].size() - 1)
            cout << ans[0][i];
        else
            cout << ans[0][i] << ",";
    }
    cout << "]" << endl;

    cout << "Pseudo-Critical Edges : [";
    for (int i = 0; i < ans[1].size(); i++)
    {
        if (i == ans[1].size() - 1)
            cout << ans[1][i];
        else
            cout << ans[1][i] << ",";
    }
    cout << "]" << endl;

    return 0;
}














