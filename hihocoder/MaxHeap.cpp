/************
 * http://hihocoder.com/problemset/problem/1105
 */

#include <iostream>
#include <cstring>


using namespace std;


struct Heap
{
	int* array;
	int tail;
};

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void percolateUp(int* array, int i)
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

	if (array[p] < array[i]) {
		swap(array, i, p);

		percolateUp(array, p);
	}
}

void percolateDown(int* array, int i, int N)
{
	if (N < i * 2) {
		return;
	}

	int successor, successor_val;

	if (array[2 * i] > array[2 * i + 1]) {
		successor = 2 * i;
		successor_val = array[2 * i];
	} else {
		successor = 2 * i + 1;
		successor_val = array[2 * i + 1];
	}

	if (array[i] < successor_val) {
		swap(array, i, successor);

		percolateDown(array, successor, N);
	}
}

void push(Heap& heap, int n)
{
	heap.array[++heap.tail] = n;

	percolateUp(heap.array, heap.tail);
}

int pop(Heap& heap, int N)
{
	int top = heap.array[1];

	heap.array[1] = heap.array[heap.tail];
	heap.array[heap.tail--] = 0;

	percolateDown(heap.array, 1, N);

	return top;
}

int main()
{
	int N;
	cin >> N;

	int arr[N + 1];
	memset(arr, 0, sizeof(arr));

	Heap heap = {&arr[0], 0};

	for (int i = 0; i < N; i++) {
		char cmd;
		cin >> cmd;

		if (cmd == 'A') {
			int n;
			cin >> n;

			push(heap, n);
		} else if (cmd == 'T') {
			cout << pop(heap, N) << endl;
		}
	}

	return 0;
}