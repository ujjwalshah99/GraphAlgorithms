//{ Driver Code Starts

// TC -> O(V+E)
// SC -> O(V) 

#include <bits/stdc++.h>
using namespace std;

// BFS
class Solution {
  public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> vis(V,0);
        for(int i=0 ; i<V ; i++) {
            if(vis[i]) continue;
            queue<pair<int,int>> qu;
            qu.push({i,-1});
            vis[i]=1;
            while(!qu.empty()) {
                int curr = qu.front().first;
                int par = qu.front().second;
                qu.pop();
                for(int ch : adj[curr]) {
                    if(ch==par) continue;
                    if(vis[ch]) return 1;
                    qu.push({ch,curr});
                    vis[ch]=1;
                }
            }
        }
        return 0;
    }
};

// DFS
class Solution {
  public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> vis(V,0);
        for(int i=0 ; i<V ; i++) {
            if(!vis[i]) {
                if(func(vis,adj,i,i)) return 1;
            }
        }
        return 0;
    }
    bool func(vector<bool> &vis , vector<int> adj[] , int no , int par) {
        vis[no]=1;
        for(int ch : adj[no]) {
            if(ch==par) continue;
            if(vis[ch]) return 1;
            if(func(vis,adj,ch,no)) return 1;
        }
        return 0;
    }
};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(V, adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}

// shortest path with equal weights == bfs
// remember multi-source bfs