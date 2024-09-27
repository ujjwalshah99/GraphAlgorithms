// it is not used for negative weight cycle and also for any negative weights
// undirected graphs with cycle too
// TC -> O(Elog(V))
// SC -> O(V)
// we can also use a queue in this implementation but it will not consider the shortest path to reach a node first
// which will increase the TC cuz there are multiple paths to a node 
#include<bits/stdc++.h>
using namespace std;

class Solution
{
	public:
	// Algo to find the shortest distance of all the vertice from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        set<pair<int,int>> st;
        vector<int> dist(V,1e9);
        
        st.insert({0,S});
        dist[S]=0;
        
        while(!st.empty()) {
            int dis = st.begin()->first;
            int node = st.begin()->second;
            
            st.erase(st.begin());
            
            for(auto ch : adj[node]) {
                int ch_node = ch[0];
                int ch_wt = ch[1];
                
                if(dis+ch_wt < dist[ch_node]) {

                    if(dist[ch_node]!=1e9) {
                        st.erase({dist[ch_node] , ch_node});
                    }

                    dist[ch_node] = dis+ch_wt;
                    st.insert({dist[ch_node] , ch_node});
                }
            }
        }
        return dist;
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
        int S;
        cin>>S;
        
        Solution obj;
    	vector<int> res = obj.dijkstra(V, adj, S);
    	
    	for(int i=0; i<V; i++)
    	    cout<<res[i]<<" ";
    	cout<<endl;
    }

    return 0;
}

// time complexity
// queue will run for V nodes
// V * ((pop from heap) + (no of edges of each node)*(push into heap))  :: V-1 edges will be at max from a node
// V * (log(heap size) + (V-1)*(log(heap size)))
// V * log(heap size) * (V-1+1)
// V * V * log(E)  :: there will be at most V*(V-1) edges ie V^2
// V*V * log(V^2)
// 2*E log(V)