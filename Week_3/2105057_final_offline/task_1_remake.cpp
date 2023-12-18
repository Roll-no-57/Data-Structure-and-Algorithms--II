#include <bits/stdc++.h>
using namespace std;


#define INF 1e8


int ModifiedDijkstra(int n,vector<vector<int>> Graph[],vector<int> &gasPrice,int s,int destination,int capacity)
{
    
    vector<vector<int>> dist(n,vector<int>(capacity+1,INF));
    vector<vector<int>> vis(n,vector<int>(capacity+1,0));

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;

    dist[s][0] = 0;
    pq.push({dist[s][0],{s,0}});

    while(!pq.empty()){
        pair<int,pair<int,int>> p = pq.top();
        pq.pop();

        int d = p.first;
        int u = p.second.first;
        int r = p.second.second;

        if(u == destination)return d;

        if(vis[u][r])continue;
        vis[u][r] = 1;

        if(r<capacity){
            dist[u][r+1] = dist[u][r]+gasPrice[u];
            pq.push({dist[u][r+1],{u,r+1}});
        }

        for(auto v:Graph[u]){
            int neighbour
        }

        
    }
}





int main(){
    int n,m,capacity;
    cin>>n>>m>>capacity;

    vector<vector<int>> Graph[n];
    vector<int> gasPrice(n);

    for(int i=0;i<n;i++) cin>>gasPrice[i];

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Graph[u].push_back({v,w});
        Graph[v].push_back({u,w});
    }

    int s,destination;cin>>s>>destination;

    int ans = ModifiedDijkstra(n,Graph,gasPrice,s,destination,capacity);


    if(ans<INF) cout<<ans<<endl;
    else cout<<"impossible"<<endl;
}
