/************
 * http://hihocoder.com/problemset/problem/1098
 */


#include <iostream>

using namespace std;


/**
 * edge
 */
struct edge
{
	int v1;
	int v2;
	int w;

	edge(int _v1, int _v2, int _w) : v1(_v1), v2(_v2), w(_w) {}
};



/**
 * MinHeap
 */
class MinHeap
{
private:

	edge** array;
	int tail;
	int maxNum;

	void swap(int i, int j)
	{
		edge* temp = array[i];
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
		array = new edge*[N + 1];

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

	void push(int v1, int v2, int w)
	{
		edge* n = new edge(v1, v2, w);
		array[++tail] = n;

		percolateUp(tail);
	}

	edge pop()
	{
		edge* top = array[1];

		array[1] = array[tail];
		array[tail--] = nullptr;

		percolateDown(1);

		edge ret(top -> v1, top -> v2, top -> w);

		delete top;

		return ret;
	}

	bool empty()
	{
		return tail == 0;
	}

};



/**
 * UnionSet
 */

class UnionFind
{
private:

	int* set;

public:

	void unite(int n, int m)
	{
		int n_root = find(n);
		int m_root = find(m);

		if (n_root > m_root) {
			int temp = m_root;
			m_root = n_root;
			n_root = temp;
		}

		set[m_root] = n_root;
	}

	int find(int ele)
	{
		if (set[ele] != ele) {
			set[ele] = find(set[ele]);
		}

		return set[ele];
	}

	UnionFind(int N)
	{
		set = new int[N + 1];
		
		for (int i = 0; i <= N; i++) {
			set[i] = i;
		}
	}

	virtual ~UnionFind()
	{
		delete[] set;
	}

};


/**
 * main
 */

int main()
{
	int N, M;
	cin >> N >> M;

	MinHeap p_queue(M);
	UnionFind uf_set(N);

	for (int i = 0; i < M; ++i){
		int n1, n2, w;

		cin >> n1 >> n2 >> w;

		p_queue.push(n1, n2, w);
	}

	long long sum = 0;
	int added_edge = 0;

	/** Kruscal */
	while (added_edge < N + 1 && !p_queue.empty()) {
		edge min_e = p_queue.pop();

		if (uf_set.find(min_e.v1) != uf_set.find(min_e.v2)) {
			sum += min_e.w;

			added_edge++;

			uf_set.unite(min_e.v1, min_e.v2);
		}
	}

	cout << sum << endl;
	
	return 0;
}