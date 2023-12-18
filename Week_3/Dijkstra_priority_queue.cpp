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

    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S,vector<int> &parent)
    {

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(V, 1e9);

        dist[S] = 0;
        parent[S]=S;

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
                    parent[adjNode]= node;
                }

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

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E, S,destination;
        cin >> V >> E >> S>>destination;

        vector<vector<int>> adj[V];
        vector<int> parent(V,-1);

        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;

            adj[u].push_back({v,w});
            // adj[v].push_back({u,w});
        }

        Solution obj;
        vector<int> ans = obj.dijkstra(V,adj,S,parent);

        for(int i=0;i<V;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;

        obj.printRoute(parent,S,destination);

    }
}
/*

1
5 7 0 4
0 1 7
0 2 1
0 3 2
1 2 3
1 3 5
1 4 1
3 4 7

*/