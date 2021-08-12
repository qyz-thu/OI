//
// Created by leo_qian on 2021/8/11.
//

#include<stdio.h>
int N, K;
int sum;
void search(int, int, int);

int main()
{
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N / K; i++)
        search(i, 1, i);
    printf("%d", sum);

    return 0;
}

void search(int n, int k, int s)   // n is the last number divided, k is the amount of number divided, s is the sum of current numbers
{
    if (k == K - 1)
    {
        if (N - s >= n)
            sum += 1;
    }
    else
    {
        for (int i = n; i <= N - s; i++)
            search(i, k + 1, s + i);
    }
}