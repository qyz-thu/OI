//
// Created by leo_qian on 2021/10/1.
//
#include<map>
#include<vector>
#include<iostream>
using namespace std;

struct Node
{
int l;
int r;
int val;
};
Node tree[50000];

void build(vector<int>& height, int l, int r, int p)
{
    if (l == r)
    {
        tree[p].l = tree[p].r = l;
        tree[p].val = height[l];
    }
    else
    {
        int m = (l + r) / 2;
        tree[p].l = l;
        tree[p].r = r;
        build(height, l, m, 2 * p + 1);
        build(height, m + 1, r, 2 * p + 2);
        tree[p].val = max(tree[2 * p + 1].val, tree[2 * p + 2].val);
    }
}

int search(int lo, int hi, int p)  // find the max in [lo, hi] in node p
{
    int l = tree[p].l;
    int r = tree[p].r;
    if (lo < l || hi > r || lo > hi)
        return -1;
    if (lo == l && hi == r)
        return tree[p].val;
    int mi = (l + r) / 2;
    if (lo <= mi)
    {
        if (hi <= mi)
            return search(lo, hi, 2 * p + 1);
        else
            return max(search(lo, mi, 2 * p + 1), search(mi + 1, hi, 2 * p + 2));
    }
    return search(lo, hi, 2 * p + 2);
}

int main()
{
    vector<int> height = {0};
    int ans = 0;
    build(height, 0, height.size() - 1, 0);
    map<int, vector<int>> table;
    for (int i = 0; i < height.size(); i++)
    {
        if (table.find(height[i]) == table.end())
            table[height[i]] = vector<int>();
        table[height[i]].push_back(i);
    }

    int max = search(0, height.size() - 1, 0);
    int max_i = table[max][0];  // choose the first max as our starting point
    // search for the left
    while (true)
    {
        int m = search(0, max_i - 1, 0);
        if (m < 0)
            break;
        int max_j;  // the index of rightest highest block on the left side of current pivot
        for (int j = table[m].size() - 1; j >= 0; j--)
            if (table[m][j] < max_i)
            {
                max_j = table[m][j]; break;
            }
        for (int i = max_j + 1; i < max_i; i++)
            ans += (m - height[i]);
        if (max_j == 0)
            break;
        max_i = max_j;
    }
    // search for the right
    max_i = table[max][0];
    while (true)
    {
        int m = search(max_i + 1, height.size() - 1, 0);
        if (m < 0)
            break;
        int max_j;  // the index of leftest highest block on the right side of current pivot
        for (int j = 0; j < table[m].size(); j++)
            if (table[m][j] > max_i)
            {
                max_j = table[m][j]; break;
            }
        for (int i = max_i + 1; i < max_j; i++)
            ans += (m - height[i]);
        if (max_j == height.size() - 1)
            break;
        max_i = max_j;
    }
    cout << ans;

    return 0;
}
