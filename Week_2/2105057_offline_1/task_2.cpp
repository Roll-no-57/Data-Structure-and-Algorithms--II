#include <bits/stdc++.h>
using namespace std;

class Solve
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

		int find(int x)
		{
			if (x == parent[x])
				return x;

			return parent[x] = find(parent[x]);
		}

		void Union(int x, int y)
		{
			int x_parent = find(x);
			int y_parent = find(y);

			if (x_parent == y_parent)
				return;

			if (rank[x_parent] > rank[y_parent])
			{
				parent[y_parent] = x_parent;
			}
			else if (rank[x_parent] < rank[y_parent])
			{
				parent[x_parent] = y_parent;
			}
			else
			{
				parent[x_parent] = y_parent;
				rank[y_parent]++;
			}
		}
	};

	int Kruskal(vector<vector<int>> &vec, int skip_edge, int force_edge)
	{

		int sum = 0;
		UnionFind uf(N);

		if (force_edge != -1)
		{
			uf.Union(vec[force_edge][0], vec[force_edge][1]);
			sum += vec[force_edge][2];
		}

		for (int i = 0; i < vec.size(); i++)
		{

			if (i == skip_edge)
				continue;

			int u = vec[i][0];
			int v = vec[i][1];
			int wt = vec[i][2];

			int parent_u = uf.find(u);
			int parent_v = uf.find(v);

			if (parent_u != parent_v)
			{
				uf.Union(u, v);
				sum += wt;
			}
		}

		// Check if all vertices are included in MST
		for (int i = 0; i < N; i++)
		{
			if (uf.find(i) != uf.find(0))
				return INT_MAX;
		}

		return sum;
	}

	vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
	{
		N = n;

		// since for kruskal's algo, we will sort our input by edge weight.
		// But since we need to return the index in the last
		for (int i = 0; i < edges.size(); i++)
		{
			edges[i].push_back(i);
		}

		auto comparator = [&](auto &v1, auto &v2)
		{
			return v1[2] < v2[2];
		};
		// Now sort based on weight
		// O(ElogE)
		sort(edges.begin(), edges.end(), comparator);

		// Find MST now
		// Find MST weight using union-find
		int MST_WEIGHT = Kruskal(edges, -1, -1);

		vector<int> critical, pseudo_critical;

		for (int i = 0; i < edges.size(); i++)
		{

			if (Kruskal(edges, i, -1) > MST_WEIGHT) // Skipping ith edge
				critical.push_back(edges[i][3]);

			else if (Kruskal(edges, -1, i) == MST_WEIGHT) // Force add ith edge
				pseudo_critical.push_back(edges[i][3]);
		}

		return {critical, pseudo_critical};
	}
};

int main()
{

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int n, m;
	cin >> n >> m;

	int vertices = n;
	vector<vector<int>> ans;
	vector<vector<int>> edges;

	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
	}

	Solve s;
	ans = s.findCriticalAndPseudoCriticalEdges(vertices, edges);

	sort(ans[0].begin(), ans[0].end());
	sort(ans[1].begin(), ans[1].end());
	// Printing the ans
	vector<pair<int, string>> result;

	for (int i = 0; i < ans[0].size(); i++)
	{
		result.push_back({ans[0][i], "any"});
	}

	for (int i = 0; i < ans[1].size(); i++)
	{
		result.push_back({ans[1][i], "at least one"});
	}

	sort(result.begin(), result.end());

	int j = 0;
	for (int i = 0; i < m; i++)
	{
		if (i == result[j].first)
		{
			cout << result[j].second << endl;
			j++;
		}
		else
		{
			cout << "none" << endl;
		}
	}

	return 0;
}
/*
INPUT :
test case -1 :
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

test case -2:
3 3
1 2 1
2 3 1
1 3 2

**Time Complexity : O(E * log(V)) where ,
	E is the number of edges in the graph and
	V is the number of vertices in the graph.

**Space Complexity : O(E + V)


CSE 207 : DSA-2 TASK-2 CODE BY :
	NAME : MOSHARAF HOSSAIN APURBO
	ID : 2105057
*/