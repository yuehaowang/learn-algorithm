/************
 * http://hihocoder.com/problemset/problem/1109
 */


#include <iostream>
#include <cstring>

#define MAX_W 9999

using namespace std;



/**
 * node
 */

struct node {
	int val;
	int w;
	node* next;

	node(int _v, int _w) : val(_v), w(_w), next(nullptr) {}
	~node() { delete next; }
};



/**
 * MinHeap
 */
class MinHeap
{
private:

	node** array;
	int tail;
	int maxNum;

	void swap(int i, int j)
	{
		node* temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	void percolateUp(int i)
	{
		if (i == 1) {
			return;
		}

		int p;
		if (i % 2 == 0) {
			p = i / 2;
		} else {
			p = (i - 1) / 2;
		}

		if ((array[p] -> w) > (array[i] -> w)) {
			swap(i, p);

			percolateUp(p);
		}
	}

	void percolateDown(int i)
	{
		if (maxNum < i * 2 || array[2 * i] == nullptr) {
			return;
		}

		int successor, successor_val;

		if (array[2 * i + 1] == nullptr || (array[2 * i] -> w) < (array[2 * i + 1] -> w)) {
			successor = 2 * i;
			successor_val = (array[2 * i] -> w);
		} else {
			successor = 2 * i + 1;
			successor_val = (array[2 * i + 1] -> w);
		}

		if (array[i] -> w > successor_val) {
			swap(i, successor);

			percolateDown(successor);
		}
	}

public:

	MinHeap(int N) : tail(0), maxNum(N)
	{
		array = new node*[N + 1];

		for (int i = 0; i <= maxNum; i++) {
			array[i] = nullptr;
		} 
	}

	virtual ~MinHeap()
	{
		for (int i = 1; i <= maxNum; i++) {
			if (array[i] != nullptr) {
				delete array[i];
			}
		}

		delete[] array;
	}

	void push(int v, int w)
	{
		node* n = new node(v, w);
		array[++tail] = n;

		percolateUp(tail);
	}

	node pop()
	{
		node* top = array[1];

		array[1] = array[tail];
		array[tail--] = nullptr;

		percolateDown(1);

		node ret(top -> val, top -> w);

		delete top;

		return ret;
	}

	bool empty()
	{
		return tail == 0;
	}

};



/**
 * utils
 */

void add_edge(node** nodes, int N1, int N2, int V)
{
	node* n = new node(N2, V);

	n -> next = nodes[N1] -> next;
	nodes[N1] -> next = n;

	// if (N1 == 1) {
	// 	cout << nodes[1] -> next -> w << endl;
	// }
}


/**
 * main
 */

int main()
{
	int N, M;
	cin >> N >> M;

	node* nodes[N + 1];
	for (int j = 0; j <= N; j++) {
		nodes[j] = new node(j, 0);
	}

	MinHeap heap(M);

	int weights[N + 1];
	memset(weights, MAX_W, sizeof(weights));

	bool visited[N + 1];
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < M; i++) {
		int N1, N2, V;
		cin >> N1 >> N2 >> V;

		add_edge(nodes, N1, N2, V);
		add_edge(nodes, N2, N1, V);
	}

	weights[1] = 0;
	heap.push(1, 0);

	int visited_num = 0;
	int sum = 0;

	do {
		node top = heap.pop();

		int v = top.val;

		if (visited[v]) {
			continue;
		}

		sum += top.w;
		visited[v] = true;

		node* head = nodes[v] -> next;
		while (head != nullptr) {
			if (head -> w < weights[head -> val]) {
				weights[head -> val] = head -> w;

				heap.push(head -> val, head -> w);
			}

			head = head -> next;
		}

	} while(!heap.empty() && visited_num < N);

	cout << sum << endl;

	for (int i = 0; i <= N; i++) {
		delete nodes[i];
	}
}