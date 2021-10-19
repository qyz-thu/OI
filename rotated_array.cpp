//
// Created by leo_qian on 2021/10/19.
//
#include <vector>
#include <iostream>
using namespace std;


int find_interval(vector<int>& nums, int lo, int hi)
{
    if (hi - lo < 1)
        return 0;
    if (hi - lo == 1)
        return lo;
    if (hi - lo == 2)
        return nums[hi - 1] < nums[lo]? hi - 1: lo;
    int mi = (hi + lo) / 2;
    if (nums[mi] > nums[lo])
    {
        if (nums[hi - 1] < nums[mi])
            return find_interval(nums, mi + 1, hi);
        return lo;
    }
    else if (nums[mi] < nums[lo])
    {
        if (nums[mi] < nums[mi - 1])
            return mi;
        return find_interval(nums, lo + 1, mi);
    }
    else    // nums[mi] == nums[lo]
    {
        if (nums[hi - 1] > nums[mi])
            return lo;
        if (nums[hi - 1] < nums[mi])
            return find_interval(nums, mi + 1, hi);
        for (int i = mi + 1; i < hi; i++)
        {
            if (nums[i] > nums[i - 1])
                return find_interval(nums, i + 1, hi);
            else if (nums[i] < nums[i - 1])
                return i;
        }
        if (nums[mi] < nums[mi - 1]) return mi;
        return find_interval(nums, lo, mi);
    }
}

int main()
{
    vector<int> nums = {-1,-1,-1,-1,0,0,3,3};

    cout << find_interval(nums, 0, nums.size()) << endl;

    return 0;
}