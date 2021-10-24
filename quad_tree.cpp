
//
// Created by leo_qian on 2021/10/23.
//
#include <vector>
using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
};

struct Sum
        {
    int sum;
    int x, y, len;
    Sum *lt=NULL, *rt=NULL, *lb=NULL, *rb=NULL;
        };
Sum* root;

Sum* get_sum(vector<vector<int>>& grid, int i, int j, int l)
{
    Sum *p = new Sum();
    p->x = i; p->y = j; p->len = l;
    if (l == 1)
    {
        p->sum = grid[i][j];
    }
    else
    {
        int ll = l >> 1;
        p->lt = get_sum(grid, i, j, ll);
        p->rt = get_sum(grid, i, j + ll, ll);
        p->lb = get_sum(grid, i + ll, j, ll);
        p->rb = get_sum(grid, i + ll, j + ll, ll);
        p->sum = p->lt->sum + p->rt->sum + p->lb->sum + p->rb->sum;
    }
    return p;
}

int find_sum(Sum* p, int i, int j, int l)
{
    if (p->len == l)
        return p->sum;
    else
    {
        int ll = p->len >> 1;
        if (p->x + ll > i && p->y + ll > j)
            return find_sum(p->lt, i, j, l);
        if (p->x + ll <= i && p->y + ll > j)
            return find_sum(p->lb, i, j, l);
        if (p->x + ll > i && p->y + ll <= j)
            return find_sum(p->rt, i, j, l);
        if (p->x + ll <= i && p->y + ll <= j)
            return find_sum(p->rb, i, j, l);
    }
    return -1;
}

Node* build(vector<vector<int>>& grid, int x, int y, int len)
{
    if (len < 1)
        return NULL;
    Node* p = new Node();
    if (len == 1)
    {
        p->val = grid[x][y] == 1;
        p->isLeaf = true;
        return p;
    }
    int sum = find_sum(root, x, y, len);
    if (sum != len * len && sum != 0)
    {
        int new_len = len >> 1;
        p->topLeft = build(grid, x, y, new_len);
        p->bottomLeft = build(grid, x + new_len, y, new_len);
        p->topRight = build(grid, x, y + new_len, new_len);
        p->bottomRight = build(grid, x + new_len, y + new_len, new_len);
    }
    else
    {
        p->val = grid[x][y] == 1;
        p->isLeaf = true;
    }

    return p;
}

int main()
{
    vector<int> r1 = {1,1,0,1,0,0,1,0};
    vector<int> r2 = {1,1,1,1,0,0,0,1};
    vector<int> r3 = {1,1,1,1,1,1,1,1};
    vector<int> r4 = {1,1,1,1,1,0,1,1};
    vector<int> r5 = {1,1,1,1,0,0,0,0};
    vector<int> r6 = {1,1,1,1,0,0,0,0};
    vector<int> r7 = {1,1,1,1,0,0,0,0};
    vector<int> r8 = {1,1,1,1,0,0,0,0};
    vector<vector<int>> grid = {r1, r2, r3, r4, r5, r6, r7, r8};

    root = get_sum(grid, 0, 0, 8);
    find_sum(root, 0, 2, 2);
    Node* p = build(grid, 0, 0, 8);

    return 0;
}