// used to find shortest path from src to any node 
// can be used in any graphs 
// can handle negative weights and negative weight cycles 
// at most you will need to traverse N-1 edges to get from one node to other (if it is linear ie max)
// if on Nth iteration if there is still an update in sortest dist , there is negative weighted cycle
// for undir we will check for both the sides seprately

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int> dist(V,(int)1e8);
        dist[S]=0;
        
        for(int i=0 ; i<V-1 ; i++) {
            for(int j=0 ; j<edges.size() ; j++) {
                int u = edges[j][0];
                int v = edges[j][1];
                int wt = edges[j][2];
                
                if((dist[u]<1e8) && (dist[u] + wt < dist[v])) {
                    dist[v] = dist[u]+wt;
                }
            }
        }
        for(int j=0 ; j<edges.size() ; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
                
            if((dist[u]<1e8) && (dist[u] + wt < dist[v])) {
                return {-1};
            }
        }
        return dist;
    }
};


int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, m;
        cin >> N >> m;
        vector<vector<int>> edges;

        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
        }

        int src;
        cin >> src;

        Solution obj;
        vector<int> res = obj.bellman_ford(N, edges, src);

        for (auto x : res) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}

// TC O(V*E)
// SC O(V)