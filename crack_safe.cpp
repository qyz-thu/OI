//
// Created by leo_qian on 2021/10/14.
//
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Node
{
    string prefix;
    vector<int> children;
};
Node pool[2000];    // at most 1024 nodes

int main()
{
    int n = 3;
    int k = 2;
    if (n == 1)
    {
        string ans;
        for (int i = 0; i < k; i++)
            ans.push_back('0' + i);
        cout << ans;
        return 0;
    }
    int powers[n];
    string s;
    powers[0] = 1;
    for (int i = 1; i < n; i++)
    {
        powers[i] = powers[i - 1] * k; s.push_back('0');
    }
    for (int i = 0; i < powers[n - 1]; i++)
    {
        pool[i].prefix = s;
        for (int j = 0; j < n - 1; j++)
            pool[i].prefix[j] += (i % powers[n - 1 - j]) / powers[n - 2 - j];
        int pre = (i % (powers[n - 2])) * k;
        for (int j = 0; j < k; j++)
            pool[i].children.push_back(pre + j);
    }

    vector<int> ans_stack;
    int stack[2000];
    int head = 1;
    stack[0] = 0;
    while (head > 0)
    {
        int c = stack[head - 1];
        if (pool[c].children.empty())
        {
            head--;
            ans_stack.push_back(c);
        }
        else
        {
            stack[head++] = pool[c].children.back();
            pool[c].children.pop_back();
        }
    }
    string ans = pool[0].prefix;
    for (int it = ans_stack.size() - 1; it > 0; it--)
        ans.push_back(pool[ans_stack[it]].prefix[n - 2]);

    cout << ans;
    return 0;
}