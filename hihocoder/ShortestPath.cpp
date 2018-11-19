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


void Dijkstra(int N, node** edges, int* path_len)
{
	int unvisited[N + 1];
	int unvisited_num = N;

	for (int i = 0; i <= N; i++) {
		unvisited[i] = 0;
	}

	while (unvisited_num > 0) {
		// find a vertex with the minimum length from the start
		int mini, mini_dist = INF;

		for (int i = 0; i <= N; i++) {
			if (unvisited[i] == 0 && path_len[i] < mini_dist) {
				mini = i;
				mini_dist = path_len[i];
			}
		}

		unvisited[mini] = 1;
		unvisited_num--;

		// re-calculate the length of the vertex's adjacent vertices
		node* next = edges[mini] -> next;

		while(next != nullptr) {
			if (unvisited[next -> val] == 0) {
				int d = mini_dist + next -> w;

				if (d < path_len[next -> val]) {
					path_len[next -> val] = d;
				}
			}

			next = next -> next;
		}
	}
}

void add_edge(node** edges, int u, int v, int l)
{
	node* n = new node(v);
	n -> next = edges[u] -> next;
	n -> w = l;
	edges[u] -> next = n;
}

int main()
{
	int N, M, S, T;  // the number of vertex, the number of edges, start vertex, destination vertex

	cin >> N >> M >> S >> T;

	node* edges[N + 1];
	int path_len[N + 1];	

	for (int v = 0; v <= N; v++) {
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

		add_edge(edges, u, v, l);
		add_edge(edges, v, u, l);
	}

	Dijkstra(N, edges, path_len);

	cout << path_len[T] << endl;
	
	return 0;
}