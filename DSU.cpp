// without path compression it works in log(N) time
// we connect smaller to larger for efficient path compression
// in path compression there is a distortion in rank(length) so we can also use size
// used in dynamic graphs where we are connecting nodes again and again
// can used to find connected components and cycles
#include<bits/stdc++.h>
using namespace std;
const int k=1001;
int e,n;
// vector<int> par;
// vector<int> size;
// vector<int> rank;
int par[k];
int rankd[k];
int size[k];
vector<list<int>> tree;

//TC(log*(n)) or O(4*alpha)

int find(int x) {
    if(par[x]==x) return x;
    return par[x] = find(par[x]);
}

void union_size(int a , int b) {
    a = find(a);
    b = find(b);
    if(a==b) return;
    if(size[a]<size[b]) {
        size[b]+=size[a];
        par[a]=b;
    } else {
        size[a]+=size[b];
        par[b]=a;
    }
}

void union_rank(int a , int b) {
    a=find(a); b=find(b);
    if(a==b) return;
    if(rankd[a]<rankd[b]) {
        rankd[b]++;
        par[a]=b;
    } else {
        rankd[a]++;
        par[b]=a;
    }

    // alternate 
    // if(rankd[a]<rankd[b]) par[a]=b;
    // else if(rank[b]<rank[a]) par[b]=a;
    // else {
    //     par[b]=a;
    //     rank[a]++;
    // }
}

struct Edge {
    int src,des;
    int wt;
};

static bool comp(Edge e1 , Edge e2) {
    return e1.wt<e2.wt;
}

// TC O(E + E.logE)
long long kru(vector<Edge> &input) {
    sort(input.begin() , input.end() , comp);
    int tredge = 0; // edges of tree with n nodes are n-1(const) 
    //you can do it for all edges also but it will sometime take some extra iterations
    int i=0;
    long long sumEdge = 0;
    while(tredge<n-1 && i<e) {
        Edge curr = input[i];
        int srcPar = find(curr.src);
        int desPar = find(curr.des); // if srcPar==desPar this means they have same parent and already met through a path
        // if you add this path , direct path it will create cycle
        if(srcPar != desPar) {
            union_rank(srcPar,desPar);
            tree[srcPar].push_back(desPar);
            tree[desPar].push_back(srcPar);
            sumEdge += curr.wt;
            tredge++;
        }
        i++;
    }
    return sumEdge;
}

int main() {
    cin>>n>>e;
    tree.resize(n);

    for(int i=0 ; i<n ; i++) {
        par[i]=i;
        rankd[i] = 0;
        size[i] = 1;
    }

    vector<Edge> edges(e);
    for(int i=0 ; i<e ; i++) {
        // int a,b,wt;
        // cin>>a>>b>>wt;
        // Edge e = {a,b,wt};
        // edges.push_back(e);
        cin>>edges[i].src>>edges[i].des>>edges[i].wt;
    }

    cout<<kru(edges)<<endl;
    
}

// where we need to delete a edge , we use precomputation