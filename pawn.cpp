//
// Created by leo_qian on 2021/8/2.
//

#include<stdio.h>
#include<stdlib.h>
int a, b, n, m;
long long int routes[22][22];
int search(int, int);

int abs(int x)
{
    return x > 0? x : -x;
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &a, &b);

    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 22; j++)
            routes[i][j] = 0;
        routes[n][m] = 1;


        for (int i = n; i >= 0; i--)
            for (int j = m; j >= 0; j--)
            {
                if (i == a && j == b || (abs(i - a) + abs(j - b) == 3 && i != a && j != b))
                    routes[i][j] = 0;
                else if (i == n && j == m)
                    continue;
                else
                    routes[i][j] = routes[i + 1][j] + routes[i][j + 1];
            }
        printf("%ldd", routes[0][0]);
            return 0;
}
