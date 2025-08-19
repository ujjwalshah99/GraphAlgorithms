// Algo to find the shortest distance of all the vertice from the source vertex S.
// it is not used for negative weight cycle and also for any negative weights
// undirected graphs with cycle too (can be used for dir gra also)
// TC -> O(Elog(V))
// SC -> O(V)
// we can also use a queue in this implementation but it will not consider the shortest path to reach a node first
// which will increase the TC cuz there are multiple paths to a node 

#include <bits/stdc++.h>
using namespace std;


class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        vector<pair<int,int>> gra[n+1];
        for(int i=0 ; i<m ; i++) {
            gra[edges[i][0]].push_back({edges[i][1] , edges[i][2]});
            gra[edges[i][1]].push_back({edges[i][0] , edges[i][2]});
        }
        
        vector<int> par(n+1,-1);
        vector<int> dist(n+1,1e9);
        set<pair<int,int>> st;
        st.insert({0,1});
        dist[1]=0; // src node dis=0
        par[1]=1; // src par = src
        
        while(!st.empty()) {
            int curr_node = st.begin()->second;
            int curr_wt = st.begin()->first;
            st.erase(st.begin());
            
            for(auto ch : gra[curr_node]) {
                int ch_node = ch.first;
                int ch_wt = ch.second;
                
                if(curr_wt+ch_wt < dist[ch_node]) {

                    if(dist[ch_node]!=1e9) st.erase({dist[ch_node] , ch_node}); // optional line ... used for dense graphs

                    dist[ch_node] = curr_wt+ch_wt;
                    par[ch_node] = curr_node;
                    st.insert({dist[ch_node] , ch_node});
                }
            }
        }
        
        vector<int> path;
        int curr=n; // des node
        
        while(par[curr]!=curr && par[curr]!=-1) { // dosen't reach the source node
            path.push_back(curr);
            curr = par[curr];
        }

        // if par of any node==-1 then that node is unreachable from src node

        if(path.size()==0) return {-1};
        path.push_back(1); // src node
        reverse(path.begin() , path.end());
        return path;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        map<pair<int, int>, int> mp;
        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
            mp[{edges.back()[0], edges.back()[1]}] = edges.back()[2];
            mp[{edges.back()[1], edges.back()[0]}] = edges.back()[2];
        }

        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        int ans = 0;
        for (int i = 2; i < res.size(); i++) {
            ans += mp[{res[i], res[i - 1]}];
        }
        if (ans == res[0]) {

        } else if (res.size() == 1 && res[0] == -1)
            ans = res[0];
        else
            ans = -2;
        cout << ans << endl;
    }
}

// time complexity
// queue will run for V nodes
// V * ((pop from heap) + (no of edges of each node)*(push into heap))  :: V-1 edges will be at max from a node
// V * (log(heap size) + (V-1)*(log(heap size)))
// V * log(heap size) * (V-1+1)
// V * V * log(E)  :: there will be at most V*(V-1) edges ie V^2
// V*V * log(V^2)
// 2*E log(V)