/************
 * http://hihocoder.com/problemset/problem/1174
 */

#include <iostream>
#include <queue>
#include <cstring>


using namespace std;


struct node {
	int val;
	node* next;

	node(int _v) : val(_v), next(nullptr) {}
	~node() { delete next; }
};

int main()
{
	int inp_group_num;
	cin >> inp_group_num;

	for (int i = 0; i < inp_group_num; i++) {
		/** create graph */
		int n, m;

		cin >> n >> m;

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
		int remaining_vertex_num = n;

		for (int j = 0; j < n; j++) {
			if (indegrees[j] == 0) {
				indegrees[j]--;  // mark the node j visited

				Q.push(j);

				remaining_vertex_num--;
			}
		}

		while (!Q.empty()) {
			int top = Q.front();
			Q.pop();

			node* edge_end = edges[top] -> next;
			while (edge_end != nullptr) {
				int val = edge_end -> val;

				indegrees[val]--;

				if (indegrees[val] == 0) {
					indegrees[val]--;  // mark the node visited

					Q.push(val);

					remaining_vertex_num--;
				}

				edge_end = edge_end -> next;
			}
		}

		cout << (remaining_vertex_num == 0 ? "Correct" : "Wrong") << endl;
	}

	return 0;
}
