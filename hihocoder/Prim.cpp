/************
 * http://hihocoder.com/problemset/problem/1097
 */

#include <iostream>

#define INF 2147483647

using namespace std;


int Prim(int V, int* adj_mat)
{
	bool visited[V];
	int unvisited_num = V - 1;
	int dist[V];

	for (int i = 0; i < V; i++) {
		dist[i] = INF;
		visited[i] = false;
	}

	int min_dist = 0;

	int curr = 0;

	while (unvisited_num != 0) {
		visited[curr] = true;
		unvisited_num--;

		int temp_min, temp_min_dist = INF;

		for (int j = 0; j < V; j++) {
			if (visited[j] != true) {
				int w = adj_mat[curr * V + j];

				if (w < dist[j]) {
					dist[j] = w;
				}

				if (temp_min_dist > dist[j]) {
					temp_min = j;
					temp_min_dist = dist[j];
				}
			}
		}

		curr = temp_min;
		min_dist += temp_min_dist;
	}

	return min_dist;
}

int main()
{
	int V;
	cin >> V;

	int adj_mat[V][V];

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			int weight;
			cin >> weight;

			adj_mat[i][j] = weight;
		}
	}

	cout << Prim(V, adj_mat[0]) << endl;

	return 0;
}