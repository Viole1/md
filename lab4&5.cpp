#include <iostream>
#include <iomanip>
#include <limits.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
	int src, dest, weight;
};

struct Graph { 
	int V, E;
	Edge* edge;
};

Graph* createGraph(int V, int E){
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

void display(vector<int>& dist, int n)
{
	cout << "Vertex   Distance from Source\n";
	for (int i = 0; i < n; ++i)
		cout << i + 1 << '\t' << dist[i] << endl;
}

void Ford(struct Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	vector<int> dist(V);

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}
	display(dist, V);
	return;
}
void BK(vector< vector<int> >& matrix, int n, int k) {
	vector<int> row(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) row[j] = (matrix[i][j] != INT_MAX && matrix[n][j] != INT_MAX) ? matrix[i][j] + matrix[n][j] : INT_MAX;
		matrix[n + k][i] = *min_element(row.begin(), row.end());
	}

	for (int i = 0; i < n + 5; i++) {
		for (int j = 0; j < n; j++)  if (matrix[n + k][j] != matrix[n + k - 1][j]) BK(matrix, n, k + 1);
	}
	
}
void displayMat(vector< vector<int> >& matrix) {
	for (auto i : matrix) {
		for (auto j : i) (j != INT_MAX) ? cout << setw(2) << j << ' ' : cout << " - ";
		cout << endl;
	}
}
int main() {
	int V, E, s, d, w;
	cin >> V >> E;
	Graph* graph = createGraph(V, E);
	vector< vector<int> > matrix(V + 5,vector<int>(V, INT_MAX));
	

	for (int i = 0; i < E; i++) {
		cout << "Enter " << i + 1 << " src, dest, weight" << endl;
		cin >> s >> d >> w;
		graph->edge[i].src = s - 1;
		graph->edge[i].dest = d - 1;
		graph->edge[i].weight = w;
		matrix[s - 1][d - 1] = w;
	}

	for (int i = 0; i < V; i++) matrix[V][i] = matrix[i][V - 1];
	for (int i = 0; i < V; i++) matrix[i][i] = 0;
	
	
	BK(matrix, V, 1);
	displayMat(matrix);
	cout << endl;
	Ford(graph, 0);

	return 0;
}
/*
* Ford
7 12
1 2 5
1 3 3
1 4 5
1 5 6
1 6 8
2 4 1
2 5 4
3 5 2
4 6 5
5 6 4
5 7 6
6 7 5
*/
/*
* BK
8 16
1 2 3
1 3 7
1 5 9
2 3 4
2 4 3
3 4 2
3 5 3
3 7 3
4 5 4
4 6 4
4 8 7
5 6 2
5 7 3
5 8 4
6 8 3
7 8 3
*/
