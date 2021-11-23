//
// Created by leo_qian on 2021/11/22.
//
#include <vector>
#include <iostream>
using namespace std;

int ans = 0;
int inf, sup;
long long temp[100000];

void merge(vector<long long>& pre, int lo, int hi)
{
    if (lo >= hi) return;
    if (lo == hi - 1)
    {
        if (pre[hi] - pre[lo] >= inf && pre[hi] - pre[lo] <= sup)
            ans++;
        return;
    }
    int mi = (lo + hi) / 2;
    merge(pre, lo, mi); // [lo, mi)
    merge(pre, mi + 1, hi); // [mi + 1, hi)
    // pre[mi] is skipped because the smallest crossing range will be pre[mi + 1] - pre[mi - 1]
    // make up for the uncounted range starts at mi
    for (int i = mi + 1; i < hi; i++)
    {
        if (pre[i] - pre[mi] >= inf && pre[i] - pre[mi] <= sup)
            ans++;
        else if (pre[i] - pre[mi] > sup)
            break;
    }
    if (pre[hi] - pre[mi] >= inf && pre[hi] - pre[mi] <= sup)
        ans++;
    int i = lo, j = mi + 1, k = mi + 1;
    while (i < mi)
    {
        while (j < hi && pre[j] - pre[i] < inf)
            j++;
        while (k < hi && pre[k] - pre[i] <= sup)
            k++;
//        if (k > j)
//            cout << "found" << endl;
        ans += k - j;
        i++;
    }
    for (i = lo; i < mi; i++)
    {
        if (pre[hi] - pre[i] >= inf && pre[hi] - pre[i] <= sup)
            ans++;
        else if (pre[hi] - pre[i] > sup)
            break;
    }
    long long x = pre[mi];
    for (i = mi + 1; i < hi; i++)
        if (pre[i] < x)
            pre[i - 1] = pre[i];
        else break;
    pre[i - 1] = x;
    i = lo, j = mi;
    int head = 0;
    while (i < mi || j < hi)
    {
        if (i == mi)
            temp[head++] = pre[j++];
        else if (j == hi)
            temp[head++] = pre[i++];
        else
            temp[head++] = pre[i] < pre[j]? pre[i++]: pre[j++];
    }
    for (i = 0; i < head; i++)
        pre[i + lo] = temp[i];
}


int main()
{
    inf = -82832; sup = -12044;
//    vector<int> nums = {-2,5,-1,-4,2,10,8,-5,-7,0,3,11,-12,-4,-3,8,4,10,-1,9,-10,0};
    vector<int> nums;
    for (int i = 0; i < 90971; i++)
        nums.push_back(-677945463);
    vector<long long> prefix(nums.size() + 1, 0);
//    prefix[0] = 0;
    for (int i = 1; i < prefix.size(); i++)
        prefix[i] = prefix[i - 1] + nums[i - 1];
    merge(prefix, 0, prefix.size() - 1);

    cout << ans << endl;

    return 0;
}

