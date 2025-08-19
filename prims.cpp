#include<bits/stdc++.h>
using namespace std;

int n,e;
vector<list<pair<int,int>>> mst;
vector<list<pair<int,int>>> gra;
priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
unordered_map<int ,pair<int,int>> mp; // stores the {node} -> {wt , par} to  maintain min wt
unordered_set<int> vis;

// insert {0,src} in pq
// one by one remove the root node of pq
// if vis continue
// else mark root vis
// update mapping
// go to the all unvisited node

int prims(int src) {

    for(int i=0 ; i<n+1 ; i++) {
        mp[i] = {INT32_MAX , -1};
    }

    pq.push({0,src});
    mp[src] = {0,-1};
    int total_vertices = 0; // 0->n-1
    int result = 0; // sum of min wt

    while(total_vertices < (n) && !pq.empty()) {
        pair<int,int> curr = pq.top();
        if(vis.count(curr.second)) {
            pq.pop();
            continue;
        }
        vis.insert(curr.second);
        total_vertices++;
        result += curr.first;
        pq.pop();
        for(auto neighbour : gra[curr.second]) {
            if(vis.count(neighbour.first)) continue;
            if(mp[neighbour.first].first > neighbour.second) {
                pq.push({neighbour.second , neighbour.first});
                mp[neighbour.first] = {neighbour.second , curr.second};
            }
        }
    }

    return result;
}

int main() {
    cin>>n>>e;
    mst.resize(n+1);
    gra.resize(n+1);
    mp.clear();
    vis.clear();
    
    for(int i=0 ; i<e ; i++) {
        int a,b,wt;
        cin>>a>>b>>wt;
        gra[a].push_back({b,wt});
        gra[b].push_back({a,wt});
    }

    int src;
    cin>>src;
    cout<<prims(src);
    return 0;
}