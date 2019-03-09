#include <stdio.h>
#include <string.h>


void cal_next(char* str, unsigned long slen, int* next_list)
{
	int j = -1;
	int i = 0;

	next_list[0] = -1;

	while (i < slen - 1) {
		if (j == -1 || str[j] == str[i]) {
			j++;
			i++;

			next_list[i] = j;
		} else {
			j = next_list[j];
		}
	}
}

int kmp(char* str, unsigned long slen, char* ptr, unsigned long plen)
{
	int next[plen];

	cal_next(ptr, plen, next);

	int j = -1;
	int i = 0;

	while (i < slen) {
		if (j == -1 || ptr[j] == str[i]) {
			j++;
			i++;
		} else {
			j = next[j];
		}

		if (j == plen) {
			return i - plen + 1;  // equal to i - j
		}
	}

	return -1;
}

int main()
{
	char str[] = "abcedefababachhababaca";
	char ptr[] = "ababaca";

	printf("Matched at %d\n", kmp(str, strlen(str), ptr, strlen(ptr)));

	return 0;
}