//
// Created by leo_qian on 2021/8/3.
//

#include<iostream>
using namespace std;

int main()
{
    int height[100001];
    int f[100001];
    int n = 0;
    while (cin >> height[n++])
        ;
    n--;
    for (int i = n; i >= 0; i--)
    {
        f[i] = 1;
        for (int j = i + 1; j <= n; j++)
            if (height[j] <= height[i])
                f[i] = f[i] > f[j] + 1? f[i] : f[j] + 1;
    }
    cout << f[n];

    return 0;
}