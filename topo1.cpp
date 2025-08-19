// KAHN Algorithm
// TC -> O(V+E)
// SC -> O(V) 
#include<bits/stdc++.h>
using namespace std;
// used to find cycle if DAG and order of resolution
vector<list<int>> graph;
int v;

vector<int> topo() {
    vector<int> indegree(v,0);
    vector<int> res;
    // agr cycle hai to ek vis arr bhi leni padegi indeg store karate samay
    for(int par = 0 ; par<v ; par++) {
        for(auto ch : graph[par]) {
            indegree[ch]++;
        }
    }
    for(int el : indegree) cout<<el<<" ";
    cout<<endl;
    queue<int> qu;
    for(int i=0 ; i<v ; i++) {
        if(indegree[i]==0) qu.push(i);
    }

    while(!qu.empty()) {
        int curr = qu.front();
        qu.pop();
        res.push_back(curr);
        for(auto ch : graph[curr]) {
            indegree[ch]--;
            if(indegree[ch]==0) qu.push(ch);
        }
    }
    // if any el in indegree is not zero it contains cycle
    // of if resolution has less than v elements i.e. not every node is resolved and there is A cyclic dependency
    for(int el : indegree) cout<<el<<" ";
    cout<<endl;
    return res;
}

//for dir gra if we want to detect cycle if edge list is given use dsu
//if => {find(a)==find(b)} at any point 

//using dfs or bfs is vis==1 except parent
//if cannot make vis array use unord set

int main() {
    int e;
    cin>>v>>e;
    graph.resize(v);
    int a,b;
    for(int i=0 ; i<e ; i++) {
        cin>>a>>b;
        graph[a].push_back(b);
    }
    vector<int> order_resolution = topo();
    for(auto el : order_resolution) cout<<el<<" ";
    cout<<endl;
}