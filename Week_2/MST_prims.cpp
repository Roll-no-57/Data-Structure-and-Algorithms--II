#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

// Function to find sum of weights of edges of the Minimum Spanning Tree.
void spanningTree()
{ 
	// Create an adjacency list representation of the graph
	int V,E;cin>>V>>E;

	vector<vector<int>> adj[V];
	
	// Fill the adjacency list with edges and their weights
	for (int i = 0; i < E; i++) {
		int u,v,wt;cin>>u>>v>>wt;
		u--;v--;
		adj[u].push_back({v, wt});
		adj[v].push_back({u, wt});
	}
	
	// Create a priority queue to store edges with their weights
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	
	// Create a visited array to keep track of visited vertices
	vector<bool> visited(V, false);
	vector<int> parent(V, -1);
	
	// Variable to store the result (sum of edge weights)
	int res = 0;
	
	// Start with vertex 0
	pq.push({0, 0});
	parent[0] = 0; // First node is always root of MST
	
	// Perform Prim's algorithm to find the Minimum Spanning Tree
	while(!pq.empty()){
		auto p = pq.top();
		pq.pop();
		
		int wt = p.first; // Weight of the edge
		int u = p.second; // Vertex connected to the edge
		
		if(visited[u] == true){
			continue; // Skip if the vertex is already visited
		}
		
		res += wt; // Add the edge weight to the result
		visited[u] = true; // Mark the vertex as visited
		
		// Explore the adjacent vertices
		for(auto v : adj[u]){
			// v[0] represents the vertex and v[1] represents the edge weight
			if(visited[v[0]] == false){
				pq.push({v[1], v[0]}); // Add the adjacent edge to the priority queue
				parent[v[0]] = u; // Set the parent of the adjacent vertex
			}
		}
	}
	
	 // Return the sum of edge weights of the Minimum Spanning Tree
	 cout<<res<<endl;
	 for(int i=1;i<V;i++)
	 {
	 	cout<<i<<" "<<parent[i]<<endl;
	 }
}

int main()
{
	

	spanningTree();

	return 0;
}
