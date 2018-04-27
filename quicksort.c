#include <stdio.h>

int partition(int* list, int start, int end)
{
	int pivot = list[end];
	int i = start;

	for (int j = start; j < end; j++) {
		if (list[j] < pivot) {
			int temp = list[i];
			list[i] = list[j];
			list[j] = temp;

			i++;
		}
	}

	list[end] = list[i];
	list[i] = pivot;

	return i;
}

void quicksort(int* list, int start, int end)
{
	if (start >= end) {
		return;
	}

	int p = partition(list, start, end);
	quicksort(list, start, p - 1);
	quicksort(list, p + 1, end);
}

int main()
{
	int list[] = {0, 2, 1, 20, 7, 50, 11, 10};
	int len = sizeof(list) / sizeof(int);

	quicksort(list, 0, len - 1);

	for (int i = 0; i < len; i++) {
		printf("%d ", list[i]);
	}

	printf("\n");
}
