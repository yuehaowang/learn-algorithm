/************
 * http://hihocoder.com/problemset/problem/1615
 */

#include <iostream>
#include <cstring>


int main()
{
    int N;
    std::cin >> N;

    int mat[N * N];

    int col_sums[N];
    memset(col_sums, 0, sizeof(col_sums));

    for (int i = 0; i < N * N; i++) {
        int val;
        std::cin >> val;

        mat[i] = val;

        col_sums[i % N] += val;
    }

    while (true) {
        // choose columns
        int min = col_sums[0], secmin = col_sums[1];
        int min_col = 0, secmin_col = 1;

        for(int i = 1; i < N; i++) {
            if (min > col_sums[i]) {
                secmin = min;
                secmin_col = min_col;

                min = col_sums[i];
                min_col = i;
            } else if (secmin > col_sums[i]) {
                secmin = col_sums[i];

                secmin_col = i;
            }
        }

        if (min + secmin > 0) {
            break;
        }

        // inverse the two chosen columns
        col_sums[min_col] = -col_sums[min_col];
        col_sums[secmin_col] = -col_sums[secmin_col];
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += col_sums[i];
    }

    std::cout << sum << std::endl;

    return 0;
}