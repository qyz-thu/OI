//
// Created by leo_qian on 2021/10/26.
//
#include <vector>
#include <iostream>
using namespace std;

struct Node
{
    int sum;
    int l, r;
};
Node tree[80];

void build_tree(int k, int left, int right)
{
    tree[k].l = left;
    tree[k].r = right;
    tree[k].sum = 0;
    if (right - left <= 1) return;
    int mid = (left + right) / 2;
    build_tree(2 * k + 1, left, mid);
    build_tree(2 * k + 2, mid, right);
}

void add(int k, int x)
{
    Node* p = tree + k;
    if (p->l > x || p->r <= x) return;    // illegal
    if (p->l <= x && p->r >= x + 1)
        p->sum++;

    int mi = (p->l + p->r) / 2;
    if (x < mi)
        add(2 * k + 1, x);
    else
        add(2 * k + 2, x);
}

int get(int k, int left, int right)
{
    Node* p = tree + k;
    if (left >= right || p->l > left || p->r < right) return 0;    // illegal
    if (p->l ==left && p->r == right)
        return p->sum;

    int mi = (p->l + p->r) / 2;
    if (right <= mi)
        return get(2 * k + 1, left, right);
    if (left >= mi)
        return get(2 * k + 2, left, right);
    return get(2 * k + 1, left, mi) + get(2 * k + 2, mi, right);
}

int main()
{
    vector<int> nums = {5, 2, 6, 1};
    int n = nums.size() - 1;
    vector<int> ans(n + 1, 0);
    build_tree(0, 0, 10);
    for (int i = n; i >= 0; i--)
    {
        ans[i] = get(0, 0, nums[i]);
        add(0, nums[i]);
    }

    for (int x: ans)
        cout << x << ' ';
//    for (int i = 0; i < 200; i++)
//        cout<< (rand() % 20000) - 10000 << ',';

    return 0;
}