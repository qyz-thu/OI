//
// Created by leo_qian on 2021/9/30.
//
#include<vector>
#include<iostream>
#include<unordered_map>
#include<set>
using namespace std;

bool taken[20];
bool success = false;
unordered_map<int, set<int>> used_set;
int stack[100];
int head = 0;

void search(int m, vector<int>& nums, int current_sum, int sum, int a, int k)
{
    set<int> selected;
    for (int i = m; i < nums.size(); i++)
    {
        if (taken[i])
            continue;
        // if (selected.find(nums[i]) != selected.end())
        //     continue;
        taken[i] = true;
        if (current_sum + nums[i] == sum)
        {
            if (a + 1 == k)
            {
                success = true;
                return;
            }
            search(0, nums, 0, sum, a + 1, k);
        }
        else
            search(i + 1, nums, current_sum + nums[i], sum, a, k);
        if (success)
            break;
        taken[i] = false;
        // selected.insert(nums[i]);
    }

}

int main()
{
//    vector<int> nums = {815,625,3889,4471,60,494,944,1118,4623,497,771,679,1240,202,601,883};
//    int k = 3;
    vector<int> nums = {2, 2, 2, 2, 3, 4, 5};
    int k = 4;
    if (k == 1)
        return true;
    int sum = 0;
    for(auto n: nums)
        sum += n;
    int group_sum = sum / k;
    if (k * group_sum != sum)
        cout << false;

    search(0, nums, 0, group_sum, 0, k);
    cout << success;

    return 0;
}
