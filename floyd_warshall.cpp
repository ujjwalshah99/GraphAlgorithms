// all pair shortest path algorithm
// can be used for any gra 
// for undir gra init dist matrix form both the sides

// if matrix graph is given 
class Solution {
  public:
	//Function to find the shortest distance between all pairs of vertices.
	void shortest_distance(vector<vector<int>>&matrix){
		int INF = INT_MAX; //initialize INF as maximum integer value.
		int n = matrix.size(); //get the size of the matrix.

		//replace all -1 with INF in the matrix.
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(matrix[i][j] == -1)
					matrix[i][j] = INF;
			}
		}

		//perform Floyd-Warshall algorithm to find shortest distances.
		for (int k = 0; k < n; ++k) {
		    for (int i = 0; i < n; ++i) {
		        for (int j = 0; j < n; ++j) {
		            if (matrix[i][k] < INF && matrix[k][j] < INF and matrix[i][k] + matrix[k][j] < INF)
		                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]); 
		        }
		    }
		}

		//replace all INF with -1 in the matrix.
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(matrix[i][j] >= INF)
					matrix[i][j] = -1;
			}
		}

		// If distance of any vertex from itself
    	// becomes negative, then there is a negative
    	// weight cycle.
		bool fl=0;
		for (int i = 0; i < V; i++)
			if (dist[i][i] < 0)
				fl = true;
		fl = false; 
	}
};

// if edge list is given
        int gra[n][n];
        for(int i=0 ; i<n ; i++) {
            for(int j=0 ; j<n ; j++) {
                gra[i][j] = INT32_MAX;
                if(i==j) gra[i][j]=0;
            }
        }
        for(int i=0 ; i<edges.size() ; i++) {
            gra[edges[i][0]][edges[i][1]] = edges[i][2];
            gra[edges[i][1]][edges[i][0]] = edges[i][2];
        }
        for(int k=0 ; k<n ; k++) {
            for(int i=0 ; i<n ; i++) {
                for(int j=0 ; j<n ; j++) {
                    if(gra[i][k]==INT32_MAX || gra[k][j]==INT32_MAX) continue;
                    gra[i][j] = min(gra[i][j] , gra[i][k]+gra[k][j]);
                }
            }
        }

// to check for negative wt cycle if (gra[i][i] < 0) then there is a negative cycle
// TC O(N^3) / O(V^3)
// SC O(N^2) / O(V^2)

// if there is no negative cycle then we can use dijkstra for all nodes as src , 
// it still will be V*E*log(V) , less than V^3 => maybe not since V*E*log(V) == V^3*log(V)
