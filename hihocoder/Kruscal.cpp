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

	~MinHeap()
	{
		for (int i = 1; i <= maxNum; i++) {
			if (array[i] != nullptr) {
				delete array[i];
			}
		}

		delete array;
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
 * main
 */

int main()
{
	MinHeap h(3);
	h.push(1, 1, 0);
	h.push(1, 2, 5);
	h.push(1, 6, 4);

	edge e1 = h.pop();
	cout << e1.w << endl;
	edge e2 = h.pop();
	cout << e2.w << endl;
	edge e3 = h.pop();
	cout << e3.w << endl;
	return 0;
}