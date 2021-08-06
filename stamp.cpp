//
// Created by leo_qian on 2021/8/6.
//

#include<stdio.h>
void search(int, int);
int maximum(int);
int N, K;
int values[15];
int max_values[15];
int minimum[500];   // minimum[i] is the minimum number of stamps used to get value i.
int max = 0;

int main()
{
    minimum[0] = 0;
    minimum[1] = 1;
    scanf("%d %d", &N, &K);
    search(1, 1);
    for (int i = 0; i < K; i++)
        printf("%d ", max_values[i]);
    printf("\n");
    printf("MAX=%d", max);

    return 0;
}


void search(int v, int k)   // k is the number of stamps, v is the value of last selected stamp
{
    values[k - 1] = v;
    if (k == K)
    {
        // calculate max
        int c = maximum(k);
        if (c > max)
        {
            max = c;
            for (int i = 0; i < K; i++)
                max_values[i] = values[i];
        }
    }
    else
    {
        int current_max = maximum(k);
        for (int i = v + 1; i <= current_max + 1; i++)
            search(i, k + 1);
    }
}

int maximum(int k)
{
    int m = 1;
    while (m++)
    {
        minimum[m] = N + 1;
        for (int i = 0; i < k; i++)
            if (values[i] == m)
                minimum[m] = 1;
        if (minimum[m] != 1)
        {
            for (int i = 0; i < m; i++)
                for (int j = 0; j < k; j++)
                {
                    if (values[j] == m - i)
                        minimum[m] = minimum[m] < minimum[i] + 1? minimum[m] : minimum[i] + 1;
                }
            if (minimum[m] == N + 1)
                break;
        }

    }
    return m - 1;
}