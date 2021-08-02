//
// Created by leo_qian on 2021/8/2.
//

#include<stdio.h>
#include<stdlib.h>
long long int map[11][11];
long long int f[11][11][20];


long long int max(long long a, long long b, long long c, long long d)
{
    long long aa = a > b? a : b;
    long long bb = c > d? c : d;
    return aa > bb? aa : bb;
}

int main()
{
    // board range: [1, n]
    int n;
    scanf("%d", &n);
    while(1)
    {
        int x, y, a;
        scanf("%d %d %d", &x, &y, &a);
        if (x == 0)
            break;
        map[x][y] = a;
    }
    f[1][1][0] = map[1][1];
    for (int k = 1; k <= 2 * (n - 1); k++)
        for (int i = 1; i <= k + 1 && i <= n; i++)
            for (int j = 1; j <= k + 1 && j <= n; j++)
            {
                f[i][j][k] = map[i][k + 2 - i] + map[j][k + 2 - j] + max(f[i][j][k-1], f[i-1][j-1][k-1], f[i-1][j][k-1], f[i][j-1][k-1]);
                if (i == j)
                    f[i][j][k] -= map[i][k + 2 - i];
            }
    printf("%lld", f[n][n][2 * n - 2]);
    return 0;
}