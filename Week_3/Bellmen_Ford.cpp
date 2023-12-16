// implementing Dijkstra's algorithm using priority queue
//  Time Complexity: O(ElogV)
//  Space Complexity: O(V+E)
//  Author: Mosharaf Hossain Apurbo
//  Roll : 2105057
//  Date : 09/12/2023
/*.................................................*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	/*  Function to implement Bellman Ford
	*   edges: vector of vectors which represents the graph
	*   S: source vertex to start traversing graph with
	*   V: number of vertices
	*/

	vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S,vector<int> &parent) {
		vector<int> dist(V, 1e8);
		dist[S] = 0;
        parent[S]=S;

		for (int i = 0; i < V - 1; i++) {
			for (auto it : edges) {
				int u = it[0];
				int v = it[1];
				int wt = it[2];
				if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
					dist[v] = dist[u] + wt;
                    parent[v]=u;
				}
			}
		}


		// Nth relaxation to check negative cycle
		for (auto it : edges) {
			int u = it[0];
			int v = it[1];
			int wt = it[2];
			if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
				return { -1};
			}
		}


		return dist;
	}

    void printRoute(vector<int> &parent,int Start,int destination){
        vector<int> ans;

        cout<<"Route from "<<Start<<" to "<<destination<<" : ";

        while(Start!=destination){
            ans.push_back(destination);
            destination = parent[destination];
        }
        reverse(ans.begin(),ans.end());

        cout<<Start<<"->";
        for(auto i:ans){
            cout<<i<<"->";
        }
        cout<<"Destination"<<endl;
    }

};


int main() {

	int V ,E;cin>>V>>E;
	vector<vector<int>> edges(E, vector<int>(3));
    vector<int> parent(V,-1);


	for(int i=0;i<E;i++){
        cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
    }

	int S,destination;cin>>S>>destination;
	Solution obj;
	vector<int> dist = obj.bellman_ford(V, edges, S,parent);
	for (auto d : dist) {
		cout << d << " ";
	}
	cout << endl;

    obj.printRoute(parent,S,destination);

	return 0;
}

/*
test case :
4 4 
1 2 10
2 3 12
3 4 -5
4 1 -5
1 4

5 7 
0 1 7
0 2 1
0 3 2
1 2 3
1 3 5
1 4 1
3 4 7
0 4
*/