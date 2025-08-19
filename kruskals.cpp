// mst is the tree which has n nodes and n-1 edges and from each node ypu can reach every other node , where we have minimum sum of edge weights
// TC -> O(E log(E))
// SC -> O(E + V)

#include<bits/stdc++.h>
using namespace std;

#define pp pair<int,pair<int,int>> // wt , u , v
class Disjoint {
    private:
    vector<int> par , rank;
    public:
    Disjoint(int size) {
        par.resize(size);
        rank.resize(size,0);
        for(int i=0 ; i<size  ; i++) par[i]=i;
    }
    int find(int x) {
        if(par[x]==x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x , int y) {
        x = find(x);
        y = find(y);
        if(x==y) return;
        if(rank[x] < rank[y]) par[x]=y;
        else if(rank[x] > rank[y]) par[y]=x;
        else {
            par[x]=y;
            rank[y]++;
        }
    }
};
class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        int ans=0 , total=0;
        // for kruskals we need edge list
        vector<pp> edges;
        for(int i=0 ; i<V ; i++) {
            for(auto el : adj[i]) {
                int ch = el[0];
                int wt = el[1];
                edges.push_back({wt , {i , ch}});
            }
        }
        
        // E log(E)
        sort(edges.begin() , edges.end());
        Disjoint dis(V);
        
        // E * 4*2*alpha
        for(pp ed : edges) {
            int wt = ed.first;
            int u = ed.second.first;
            int v = ed.second.second;
            
            if(dis.find(u)!=dis.find(v)) { // this step ensure that each node is visisted only once
                dis.unite(u,v);
                ans += wt;
                total++;
            }
            if(total==V) break;
        }
        
        return ans;
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