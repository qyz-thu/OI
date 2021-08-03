//
// Created by leo_qian on 2021/8/3.
//

#include<stdio.h>
#include<stdlib.h>
int soldiers[5001];
void sort(int[], int, int);
int partition(int[], int, int);

int max(int x, int y)
{
    return x > y? x : y;
}

int min(int x, int y)
{
    return x < y? x : y;
}

int main()
{
    int L, N;
    int fast = 0;
    int slow = 0;
    scanf("%d %d", &L, &N);
    for (int i = 0;i < N;i++)
    {
        int p;
//        scanf("%d", soldiers + i);
        scanf("%d", &p);
        int f = min(L + 1 - p, p);
        int s = max(L + 1 - p, p);
        if (fast < f)
            fast = f;
        if (slow < s)
            slow = s;
    }

    printf("%d %d", fast, slow);

    return 0;
}

void sort(int array[], int lo, int hi)
{
    int mi = partition(array, lo, hi);
    partition(array, lo, mi);
    partition(array, mi + 1, hi);
}

int partition(int array[], int lo, int hi)
{
    int mi = rand() % (hi - lo) + lo;
    int pivot = mi;


    return mi;
}