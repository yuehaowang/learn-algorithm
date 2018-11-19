/************
 * http://hihocoder.com/problemset/problem/1081
 */


#include <iostream>

#define INF 9999

using namespace std;


struct node {
	int val;
	int w;
	node* next;

	node(int _v) : val(_v), next(nullptr), w(0) {}
	~node() { delete next; }
};


void Dijkstra(int N, node** edges, int* path_len, int* parent)
{
	int unvisited[N + 1];
	int unvisited_num = N + 1;

	while (unvisited_num > 0) {
		// find a vertex with the minimum length from the start
		int mini, mini_dist = INF;

		for (int i = 0; i < N+1; i++) {
			if (path_len[i] < mini_dist) {
				mini = i;
			}
		}

		// re-calculate the length of the vertex's adjacent vertices
	}
}


int main()
{
	int N, M, S, T;  // the number of vertex, the number of edges, start vertex, destination vertex

	cin >> N >> M >> S >> T;

	node* edges[N + 1];
	int path_len[N + 1];
	int parent[N + 1];
	

	for (int v = 0; v < N; v++) {
		node* head = new node(v);
		edges[v] = head;

		if (v == S) {
			path_len[v] = 0;
		} else {
			path_len[v] = INF;
		}
	}

	for (int e = 0; e < M; e++) {
		int u, v, l;

		cin >> u >> v >> l;

		node* head = new node*(v);
		head -> next = edges[u] -> next;
		head -> w = l;
		edges[u] -> next = head;
	}

	Dijkstra(N, edges, path_len, parent);

	
	return 0;
}