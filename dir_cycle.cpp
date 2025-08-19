// directed graphs any 

// TC -> O(V+E)
// SC -> O(V) 

#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    vector<int> curr_path;
    vector<int> vis;
    bool isCyclic(int V, vector<int> adj[]) {
        curr_path.resize(V , 0);
        vis.resize(V , 0);
        for(int i=0 ; i<V ; i++) {
            if(!vis[i]) {
                if(check(adj,i)) return 1;
            }
        }
        return 0;
    }
    bool check(vector<int> adj[] , int no) {
        vis[no]=1;
        curr_path[no]=1;
        for(int ch : adj[no]) {
            if(vis[ch] && curr_path[ch]) return 1;
            if(!vis[ch]) {
                if(check(adj,ch)) return 1; 
            }
        }
        curr_path[no]=0;
        return 0;
    }
};

int main() {

    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        cout << obj.isCyclic(V, adj) << "\n";
    }

    return 0;
}
