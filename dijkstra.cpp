
#include<bits/stdc++.h>
using namespace std;
#define pp pair<int,int>

int n,e;

vector<list<pp>> gra;
vector<pp> path;
unordered_set<int> vis;
unordered_map<int , int> mwt; // stores min wt (node) -> (min wt to reach node from src)
unordered_map<int , int> par; // stores from where node is vis ie par node
priority_queue<pp , vector<pp> , greater<pp>> pq;

// for only 0-1 weight use 0-1 BFS using dequeue , push wt 0 in front and 1 at back

// TC O( (E+V)log(V) )
void dijkstras(int src) {

    for(int i=0 ; i<=n ; i++) {
        mwt[i] = INT32_MAX;
    }

    pq.push({0,src});
    par[src] = src;
    mwt[src] = 0;

    while(!pq.empty()) {
        pp curr = pq.top();
        pq.pop();
        if(vis.count(curr.second)) continue;

        vis.insert(curr.second);

        for(auto neigh : gra[curr.second]) {
            if(mwt[neigh.first] > (curr.first+neigh.second)) {
                mwt[neigh.first] = (curr.first+neigh.second);
                par[neigh.first] = curr.second;
                pq.push({mwt[neigh.first] , neigh.first});
            }
        }
    }

}

vector<pp> build_path(int src,int des) {
    vector<pp> path;
    while(par[des] != des) {
        int pa = par[des];
        path.push_back({des , mwt[des]});
        des = pa;
    }
    path.push_back({src,0});
    reverse(path.begin() , path.end());
    return path;
}

int main() {
    cin>>n>>e;
    gra.resize(n+1);
    vis.clear();
    mwt.clear();
    par.clear();
    
    for(int i=0 ; i<e ; i++) {
        int a,b,wt;
        cin>>a>>b>>wt;
        gra[a].push_back({b,wt});
        gra[b].push_back({a,wt});
    }

    int src,des;
    cin>>src>>des;

    dijkstras(src);

    for(int i=0 ; i<n ; i++) {
        cout<<i<<":"<<mwt[i]<<":"<<par[i]<<" ";
    }
    cout<<endl;

    path = build_path(src,des);
    for(auto el : path) {
        cout<<el.first<<":"<<el.second<<" ";
    }
    cout<<endl;
}