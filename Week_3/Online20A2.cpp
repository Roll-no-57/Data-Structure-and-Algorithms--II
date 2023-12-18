
// #include <bits/stdc++.h>
// using namespace std;

// class Solution
// {
// public:

//     vector<int> dijkstra(int V, vector<vector<int>> adj[], int S,vector<int> &parent)
//     {

//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//         vector<int> dist(V, 1e9);

//         dist[S] = 0;
//         parent[S]=S;

//         pq.push({0, S});

//         while (!pq.empty())
//         {
//             pair<int, int> topElement = pq.top();

//             pq.pop();

//             int dis = topElement.first;
//             int node = topElement.second;

//             for (auto i : adj[node])
//             {
//                 int edgeWeight = i[1];
//                 int adjNode = i[0];

//                 if (dist[adjNode] > dis + edgeWeight)
//                 {
//                     dist[adjNode] = dis + edgeWeight;
//                     pq.push({dist[adjNode], adjNode});
//                     parent[adjNode]= node;
//                 }

//             }

//         }
//         return dist;
//     }

//     void printRoute(vector<int> &parent,int Start,int destination){
//         vector<int> ans;

//         cout<<"Route from "<<Start<<" to "<<destination<<" : ";

//         while(Start!=destination){
//             ans.push_back(destination);
//             destination = parent[destination];
//         }
//         reverse(ans.begin(),ans.end());

//         cout<<Start<<"->";
//         for(auto i:ans){
//             cout<<i<<"->";
//         }
//         cout<<"Destination"<<endl;
//     }

// };

// // int main()
// // {
// //     // freopen("input.txt", "r", stdin);
// //     // freopen("output.txt", "w", stdout);

// //     int tc;
// //     cin >> tc;
// //     while (tc--)
// //     {
// //         int V, E, S,destination;
// //         cin >> V >> E >> S>>destination;

// //         vector<vector<int>> adj[V];
// //         vector<int> parent(V,-1);

// //         for(int i=0;i<E;i++){
// //             int u,v,w;
// //             cin>>u>>v>>w;

// //             adj[u].push_back({v,w});
// //             // adj[v].push_back({u,w});
// //         }

// //         Solution obj;
// //         vector<int> ans = obj.dijkstra(V,adj,S,parent);

// //         for(int i=0;i<V;i++){
// //             cout<<ans[i]<<" ";
// //         }
// //         cout<<endl;

// //         obj.printRoute(parent,S,destination);

// //     }
// // }

// int main(){

// }
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int time;
};

struct State {
    int node;
    int time;
    vector<int> path;
};

struct CompareState {
    bool operator()(const State& a, const State& b) {
        return a.time > b.time; // Min-heap based on time
    }
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& distance, vector<vector<int>>& paths) {
    int n = graph.size();
    distance.assign(n, numeric_limits<int>::max());
    paths.assign(n, vector<int>());

    priority_queue<State, vector<State>, CompareState> pq;
    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int node = current.node;
        int time = current.time;

        if (distance[node] < time) {
            continue;
        }

        distance[node] = time;

        for (const Edge& edge : graph[node]) {
            int nextNode = edge.to;
            int nextTime = time + edge.time;

            if (nextTime < distance[nextNode]) {
                distance[nextNode] = nextTime;
                paths[nextNode] = current.path;
                paths[nextNode].push_back(nextNode);
                pq.push({nextNode, nextTime, paths[nextNode]});
            }
        }
    }
}

int main() {
    // Read input from a file
    // freopen("input.txt", "r", stdin);

    int numStates, numRoads;
    cin >> numStates >> numRoads;

    vector<vector<Edge>> graph(numStates);
    vector<int> distance;
    vector<vector<int>> paths;

    for (int i = 0; i < numRoads; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t});
    }

    int farhanState;
    cin >> farhanState;

    // Run Dijkstra's algorithm
    dijkstra(farhanState, graph, distance, paths);

    // Find the minimum total time
    int minTotalTime = numeric_limits<int>::max();
    int chosenFriend;

    for (int state = 0; state < numStates; ++state) {
        if (state != farhanState && distance[state] < minTotalTime) {
            minTotalTime = distance[state];
            chosenFriend = state;
        }
    }

    // Output the result to a file
    freopen("output.txt", "w", stdout);

    cout << "Minimum total time: " << minTotalTime << endl;
    cout << "Paths:" << endl;

    for (int node : paths[chosenFriend]) {
        cout << node << " -> ";
    }

    cout << "(time: " << minTotalTime << ")" << endl;

    return 0;
}
