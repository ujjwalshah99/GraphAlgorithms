// to find sortest path in any graph having same wt we use dfs
// to find 0-1 wt graph path we use deque

// to find shortest path from src node to any node in DAG
// TC -> O(V+E)
// SC -> O(V) 

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    stack<int> st;
    vector<bool> vis;
    vector<int> dist;
    
    vector<int> shortestPath(int n,int m, vector<vector<int>>& edges){
        vis.resize(n,0);
        vector<pair<int,int>> gra[n];
        for(int i=0 ; i<m ; i++) {
            gra[edges[i][0]].push_back({edges[i][1] , edges[i][2]});
        }
        
        // O(V+E)
        for(int i=0 ; i<n ; i++) {
            if(!vis[i]) topo(i,gra);
        }
        
        dist.resize(n,INT32_MAX);
        //dist[src]=0;
        dist[0]=0;
        
        // O(V+E)
        while(!st.empty()) {
            int curr = st.top();
            st.pop();
            
            for(pair<int,int> pp : gra[curr]) {
                int ch = pp.first;
                int wt = pp.second;
                
                if(dist[curr]!=INT32_MAX && dist[curr]+wt < dist[ch]) {
                    dist[ch] = dist[curr]+wt;
                }
            }
        }
        
        for(int i=0 ; i<n ; i++) {
            if(dist[i]==INT32_MAX) dist[i]=-1;
        }
        
        return dist;
    }
    
    void topo(int no , vector<pair<int,int>> gra[]) {
        vis[no]=1;
        for(pair<int,int> pp : gra[no]) {
            int ch = pp.first;
            if(!vis[ch]) topo(ch,gra);
        }
        st.push(no);
    }
    
};


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        for(int i=0; i<m; ++i){
            vector<int> temp;
            for(int j=0; j<3; ++j){
                int x; cin>>x;
                temp.push_back(x);
            }
            edges.push_back(temp);
        }
        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        for (auto x : res) {
            cout << x << " ";
        }
        cout << "\n";
    }
}