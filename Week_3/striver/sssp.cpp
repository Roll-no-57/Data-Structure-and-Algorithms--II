#include <bits/stdc++.h>
using namespace std;


vector<int> shortestPath(int n, vector<vector<int>>&edges, int src) {
    // Write your code here.


    vector<int> adj[n];

    for(auto it:edges){
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }






    vector<int> dist(n, INT_MAX);
    vector<int> vis(n, 0);

    dist[src]=0;
    vis[src]=1;

    queue<int> q;
    q.push(src);

    while(!q.empty()){
        int front = q.front();
        q.pop();

        for(auto it:adj[front]){
            if(!vis[it]){
                vis[it]=1;
                dist[it] = dist[front]+1;
            }
        }
    }

    for(int i=0;i<n;i++){
        if(dist[i]==INT_MAX)dist[i]=-1;
    }
    return dist;
}