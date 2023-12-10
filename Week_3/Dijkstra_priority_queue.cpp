// implementing Dijkstra's algorithm using priority queue
//  Time Complexity: O(ElogV)
//  Space Complexity: O(V+E)
//  Author: Mosharaf Hossain Apurbo
//  Roll : 2105057
//  Date : 09/12/2023
/*.................................................*/

#include <bits/stdc++.h>
using namespace std;


class Solution
{
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex S.

    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        //
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(V, 1e9);

        dist[S] = 0;

        pq.push({0, S});

        while (!pq.empty())
        {
            pair<int, int> topElement = pq.top();

            pq.pop();

            int dis = topElement.first;
            int node = topElement.second;

            for (auto i : adj[node])
            {
                int edgeWeight = i[1];
                int adjNode = i[0];

                if (dist[adjNode] > dis + edgeWeight)
                {
                    dist[adjNode] = dis + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E, S;
        cin >> V >> E >> S;

        vector<vector<int>> adj[V];

        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;

            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }

        cout<<"Journey starts from "<<S<<endl; 
        Solution obj;
        vector<int> ans = obj.dijkstra(V,adj,S);

        for(int i=0;i<V;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;

    }
}