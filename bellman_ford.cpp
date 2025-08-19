// used for any type of graphs
#include<bits/stdc++.h>
using namespace std;
#define pp pair<int,int> 

int n,e;

vector<pp> path;
unordered_map<int,int> dis;
unordered_map<int,int> par;

// used for negative weights from one source
// at most you will need to traverse V-1 edges to get from one node to other (if it is linear ie max)
// we will iterate V-1 times
// if on V th iteration if there is still an update in sortest dist , there is negative weighted cycle

bool bellman(int src , int edges[][3]) {
    for(int i=0 ; i<=n ; i++) {
        dis[i] = INT32_MAX;
    }

    dis[src] = 0;
    par[src] = src;
    
    for(int i=0 ; i<n-1 ; i++) {
        for(int j=0 ; j<e ; j++) {
            int sc = edges[j][0];
            int des = edges[j][1];
            int wt = edges[j][2];

            if((dis[sc]!=INT32_MAX) && ((dis[sc]+wt) < dis[des])) {
                dis[des] = dis[sc]+wt;
                par[des] = sc;
            }
        }
    }

    for(int j=0 ; j<e ; j++) {
        int sc = edges[j][0];
        int des = edges[j][1];
        int wt = edges[j][2];

        if((dis[sc]!=INT32_MAX) && ((dis[sc]+wt) < dis[des])) {
            return 1;
        }
    }
    return 0;
}

vector<pp> build_path(int src , int des) {
    vector<pp> path;
    while(par[des] != des) {
        path.push_back({des , dis[des]});
        des = par[des];
    }
    path.push_back({src,0});
    reverse(path.begin() , path.end());
    return path;
}


int main() {
    cin>>n>>e;
    dis.clear();
    par.clear();
    path.clear();

    int edges[e][3];

    for(int i=0 ; i<e ; i++) {
        int a,b,wt;
        cin>>a>>b>>wt;
        edges[i][0] = a;
        edges[i][1] = b;
        edges[i][2] = wt;
    }

    int src,des;
    cin>>src>>des;

    bool f = bellman(src , edges);

    if(f) cout<<"There is a negative cycle present"<<endl;

    else {
        for(int i=0 ; i<n ; i++) {
            cout<<i<<":"<<dis[i]<<":"<<par[i]<<" ";
        }
        cout<<endl;

        path = build_path(src,des);
        for(auto el : path) {
            cout<<el.first<<":"<<el.second<<" ";
        }
        cout<<endl;
    }


}
