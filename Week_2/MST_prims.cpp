// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph

#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define V 8
#define I INT_MAX


void PrintMST(int T[][V-2], int G[V][V]){
    cout << "\nMinimum Spanning Tree Edges (w/ cost)\n" << endl;
    int sum {0};
    for (int i {0}; i<V-2; i++){
        int c = G[T[0][i]][T[1][i]];
        cout << "[" << T[0][i] << "]---[" << T[1][i] << "] cost: " << c << endl;
        sum += c;
    }
    cout << endl;
    cout << "Total cost of MST: " << sum << endl;
}

//Function to find the Min weighted Edge which return the vertex pair of that edge
void initialize(int graph[V][V],int near[V],int result [][V-2])
{
    int mn = I;
    int u,v;

    for(int i=1; i<V; i++){
		near[i] =I;
        for(int j=1; j<i; j++){  
            if(graph[i][j] < mn){
                mn = graph[i][j];
                u = i;
                v = j;
            }
        }
    }
	
	result[0][0] = u;
	result[1][0] = v;
	//initialize the near array
	near[u] =0;
	near[v] =0;

	for(int i= 1;i<V;i++){
		if(near[i]!=0 && graph[i][u]<graph[i][v]){
			near[i] = u;
		}
		else if(near[i]!=0 && graph[i][u]>=graph[i][v]){
			near[i] = v;
		}
	}

    
}


//produce the resulting minimum spannig tree
void primMST(int graph[V][V])
{

	int near[V];
	//resulting array which contains the MST edges
	int result [2][V-2] {0};

	//initialize the resulting array with the first minimum edge
	initialize(graph,near,result);
	
	//Repeatitive step starts from here
	for(int i=1;i<V-2;i++){
		//find the minimum weighted edge from the near array
		int mn =I;
		int vertex ;
		for(int j = 1;j<V;j++){
			if(near[j]!=0 && graph[j][near[j]]<mn){
				mn = graph[j][near[j]];
				vertex = j;
			}
		}
		//insert the edge in the result array
		result[0][i] = vertex;
		result[1][i] = near[vertex];
		near[vertex] =0;

		//update the near array for the recent inserted vertex
		for(int j=1;j<V;j++){
			if(near[j]!=0 && graph[j][near[j]]>graph[j][vertex]){
				near[j] = vertex;
			}
		}
	}
	PrintMST(result,graph);
}



int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);

	int graph[V][V] = {
			{I, I, I, I, I, I, I, I},
            {I, I, 25, I, I, I, 5, I},
            {I, 25, I, 12, I, I, I, 10},
            {I, I, 12, I, 8, I, I, I},
            {I, I, I, 8, I, 16, I, 14},
            {I, I, I, I, 16, I, 20, 18},
            {I, 5, I, I, I, 20, I, I},
            {I, I, 10, I, 14, 18, I, I},
						};

	// Print the solution
	primMST(graph);

	return 0;
}

// Code by Mosharaf Hossain Apurbo(2105057)
//offline -1 for DSA-2 course 

