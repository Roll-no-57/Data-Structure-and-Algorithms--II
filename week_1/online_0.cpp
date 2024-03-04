// Implementing bfs algorithm
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll mod = 1e9 + 7, MOD = 998244353;




void solve() {
    // Your solution goes here
    int n,m ; cin >> n>> m;
    vector<vector<int>> adj(n);

    F0R(i,m) {
        int u,v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int,int>>  connect ;

    int q ;cin>>q;
    for(int i=0;i<q;i++){
        int u,v; cin >> u >> v;
        u--; v--;
        connect.push_back({u,v});
    }

    


}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}