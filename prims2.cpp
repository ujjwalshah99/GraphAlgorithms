// used to find minimum spanning tree of any type of graph from a src
// if you don't want to find the mst then you can eliminate the parent part in priority queue and mst
// TC -> O( Elog(E) )
// SC -> O( E )
#include<bits/stdc++.h>
using namespace std;

#define pp pair<int,pair<int,int>> // wt , node , par
class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue<pp , vector<pp> , greater<pp>> pq;
        vector<pair<int,int>> mst[V];
        vector<bool> vis(V,0);
        int ver=0 , sum=0;
        
        pq.push({0 , {0,0}}); // {wt , {src,par}}
        while(!pq.empty() && ver<V) {
            int curr_node = pq.top().second.first;
            int curr_wt = pq.top().first;
            int par = pq.top().second.second;
            pq.pop();
            if(vis[curr_node]) continue;
            if(par!=curr_node){ // for root node
                mst[curr_node].push_back({par,curr_wt});
                mst[par].push_back({curr_node,curr_wt});
            }
            sum+=curr_wt;
            vis[curr_node] = 1;
            ver++;
            
            for(auto ch : adj[curr_node]) {
                int ch_wt = ch[1];
                int ch_no = ch[0];
                if(!vis[ch_no]) {
                    pq.push({ch_wt , {ch_no , curr_node}});
                }
            }
        }
        return sum;
    }
};


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        
        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}