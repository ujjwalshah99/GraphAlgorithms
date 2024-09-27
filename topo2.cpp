// used to take out topological sorting - ordering of resolution easily

// topological sort is the sorting --- if there is a edge between u and v then u comes before v in the sorting

// TC -> O(V+E)
// SC -> O(V) 
#include <bits/stdc++.h>
using namespace std;

class Solution
{
	public:
	stack<int> st;
	vector<bool> vis;
	vector<int> ans;
	vector<int> topoSort(int V, vector<int> adj[]) {
	    vis.resize(V,0);
	    for(int i=0 ; i<V ; i++) {
	        if(!vis[i]) func(adj,i);
	    }
	    
	    while(!st.empty()) {
	        ans.push_back(st.top());
	        st.pop();
	    }
	    return ans;
	}
	
	
	void func(vector<int> adj[] , int no) {
	    vis[no]=1;
	    for(int ch : adj[no]) {
	        if(!vis[ch]) func(adj,ch);
	    }
	    st.push(no);
	}
};

int check(int V, vector <int> &res, vector<int> adj[]) {
    
    if(V!=res.size())
    return 0;
    
    vector<int> map(V, -1);
    for (int i = 0; i < V; i++) {
        map[res[i]] = i;
    }
    for (int i = 0; i < V; i++) {
        for (int v : adj[i]) {
            if (map[i] > map[v]) return 0;
        }
    }
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> E >> N;
        int u, v;

        vector<int> adj[N];

        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
        }
        
        Solution obj;
        vector <int> res = obj.topoSort(N, adj);

        cout << check(N, res, adj) << endl;
    }
    
    return 0;
}