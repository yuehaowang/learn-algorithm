/***
 * Reference: https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
 */

#include <stdio.h>

void output(int* ls, int len)
{
	for (int i = 0; i < len; i++) {
		printf("%d ", ls[i]);
	}

	printf("\n");
}

// return value: 1 - next permutation exists; 0 - next permutation doesn't exist
int next_permuation(int* ls, int len)
{
	int ii = len;

	while (--ii > 0) {
		// find a pair of adjacent elements from the end of the array such that ls[i] < ls[ii], i < ii
		if (ls[ii] > ls[ii - 1]) {
			int i = ii - 1, j = len;

			// find a element which is greater than ls[i]
			while (--j >= ii) {
				if (ls[j] > ls[i]) {

					// swap ls[i] and ls[j]
					{
						int c = ls[j];
						ls[j] = ls[i];
						ls[i] = c;
					}

					// reverse elements whose indices are greater than ii
					{
						int k = len - 1;
						while (ii < k) {
							int temp = ls[k];
							ls[k] = ls[ii];
							ls[ii] = temp;

							ii++;
							k--;
						}
					}

					break;
				}
			}

			return 1;
		}
	}

	return 0;
}

int main()
{
	int test[] = {0, 1, 2, 3, 4};
	int len = sizeof(test) / sizeof(int);

	int count = 0;

	do {
		output(test, len);

		count++;
	} while (next_permuation(test, len));

	printf("Total: %d\n", count);
}