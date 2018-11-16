/************
 * http://hihocoder.com/problemset/problem/1175
 */

#include <iostream>
#include <queue>
#include <cstring>

#define M 142857


using namespace std;


struct node {
	int val;
	node* next;

	node(int _v) : val(_v), next(nullptr) {}
	~node() { delete next; }
};

int main()
{
	/** create graph */
	int n, m, kv;

	cin >> n >> m >> kv;

	long long virus_list[n];
	memset(virus_list, 0, sizeof(virus_list));

	for (int i = 0; i < kv; i++) {
		int virus_id;
		cin >> virus_id;

		virus_list[virus_id - 1] = 1;
	}

	int indegrees[n];
	memset(indegrees, 0, sizeof(indegrees));

	node* edges[n];

	for (int v = 0; v < n; v++) {
		node* head = new node(v);
		edges[v] = head;
	}

	for (int k = 0; k < m; k++) {
		int A, B;

		cin >> A >> B;

		A -= 1;
		B -= 1;

		node* end = new node(B);
		end -> next = edges[A] -> next;
		edges[A] -> next = end;

		indegrees[B]++;
	}

	/** topological sort */
	queue<int> Q;

	for (int j = 0; j < n; j++) {
		if (indegrees[j] == 0) {
			indegrees[j]--;  // mark the node j visited

			Q.push(j);
		}
	}

	while (!Q.empty()) {
		int top = Q.front();
		Q.pop();

		node* edge_end = edges[top] -> next;
		while (edge_end != nullptr) {
			int val = edge_end -> val;

			indegrees[val]--;

			virus_list[val] = (virus_list[val] + virus_list[top]) % M;  // due to linearity of MOD

			if (indegrees[val] == 0) {
				indegrees[val]--;  // mark the node visited

				Q.push(val);
			}

			edge_end = edge_end -> next;
		}
	}

	long long sum = 0;

	for (int v = 0; v < n; v++) {
		sum += virus_list[v];
	}

	cout << sum % M << endl;

	return 0;
}
