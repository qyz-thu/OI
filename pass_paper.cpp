//
// Created by leo_qian on 2021/8/9.
//

#include<stdio.h>

int map[51][51];
int f[51][51][110];
int max(int a, int b, int c, int d)
{
    int aa, bb;
    aa = a > b? a : b;
    bb = c > d? c : d;
    return aa > bb? aa : bb;
}

int main()
{
    // matrix: (1, 1) - (m, n)
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &map[i][j]);

    f[1][1][0] = 0;
    for (int k = 1; k <= m + n - 2; k++)
        for (int i = 1; i <= k + 1 && i <= m; i++)
            for (int j = 1; j <= k + 1 && j <= m; j++)
            {
                if (i == j && (i < m || k < m + n -2))
                {
                    f[i][j][k] = 0;
                    continue;
                }
                f[i][j][k] = map[i][k+2-i] + map[j][k+2-j] + max(f[i][j][k-1], f[i][j-1][k-1], f[i-1][j][k-1], f[i-1][j-1][k-1]);
//                if (i == j)
//                    f[i][j][k] -= map[i][k+2-i];
            }
    printf("%d", f[m][m][m + n - 2]);

    return 0;
}