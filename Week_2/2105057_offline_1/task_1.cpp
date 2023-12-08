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

		// we will sort our input by edge weight.
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
	void printMST(vector<int> ans, vector<vector<int>> edges)
	{
		cout << "[";
		for (int i = 0; i < ans.size(); i++)
		{
			cout << "[";
			cout << edges[ans[i]][0] << "," << edges[ans[i]][1] << "," << edges[ans[i]][2];
			if (i == ans.size() - 1)
				cout << "]";
			else
				cout << "],";
		}
		cout << "]" << endl;
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


	Solve s;
	ans = s.findCriticalAndPseudoCriticalEdges(vertices,edges);

	vector<int> result;
	for (int i = 0; i < ans[0].size(); i++)
	{
		result.push_back(ans[0][i]);
	}

	// Printing the ans
	for (int i = 0; i < ans[1].size(); i++)
	{
		result.push_back(ans[1][i]);
		s.printMST(result, edges);
		result.pop_back();
	}

	return 0;
}
/*

test case -1
5 10
0 1 1
2 4 1
1 2 2
0 4 2
3 4 3
0 3 5
1 4 6
2 3 8
0 2 9
1 3 9

test case -2
7 12
3 4 1
1 5 1
1 4 1
0 6 4
2 3 8
4 5 8
2 6 10
0 5 10
3 6 10
1 6 10
1 3 12
3 5 12


 **Time complexity: O(E * log(V)) where ,
	 E is the number of edges and
	 V is the number of vertices.
** Space complexity: O(E + V)


CSE 207 : DSA-2 TASK-1 CODE BY :
	NAME : MOSHARAF HOSSAIN APURBO
	ID : 2105057

*/