//
// Created by leo_qian on 2021/8/29.
//
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<set>
using namespace std;

vector<pair<int, int>> table[40][40];   // step, number of obstacles to break
set<pair<int, int>> queue;      // x, y


void update_path(int x, int y, int s, int kk, int obs, int k)
{
//    if (x == 4 && y == 2)
//        cout << "stop here";
    if (kk + obs <= k){
        if (table[x][y].empty()){
            table[x][y].emplace_back(s + 1, kk + obs);
            queue.insert(pair<int, int>(x, y));
        }
        else{
            bool better = false;
            for (auto p = table[x][y].begin(); p != table[x][y].end();)
                if (p->first > s+1 || p->second > kk + obs){
                    better = true;
                    if (p->first >= s + 1 && p->second >= kk + obs)
                        p = table[x][y].erase(p);
                    else p++;
                }
                else if (p->first <= s +1 && p->second <= kk + obs) {
                    better = false; break;
                }
                else p++;
            if (better)
            {
                table[x][y].emplace_back(s + 1, kk + obs);
                queue.insert(pair<int, int>(x, y));
            }
        }
    }
}


int main()
{
    vector<int> grid1 = {0, 1, 1};
    vector<int> grid2 = {1, 1, 1};
    vector<int> grid3 = {1, 0, 0};
//    vector<int> grid4 = {0, 1, 1};
//    vector<int> grid5 = {0, 0, 0};
    vector<vector<int>> grid = {grid1, grid2, grid3};
    int k = 1;
    int m = grid.size();
    int n = grid[0].size();
    table[0][0].emplace_back(0, 0);
    queue.insert(pair<int, int>(0, 0));
    while (!queue.empty())
    {
        auto it = queue.begin();
        int x = it->first;
        int y = it->second;
        for (auto path = table[x][y].begin(); path != table[x][y].end(); path++)
        {
            int s = path->first;
            int kk = path->second;
            if (x + 1 < m)     // down
                update_path(x+1, y, s, kk, grid[x+1][y], k);
            if (x - 1 >= 0)    // up
                update_path(x - 1, y, s, kk, grid[x-1][y], k);
            if (y + 1 < n)    // right
                update_path(x, y + 1, s, kk, grid[x][y+1], k);
            if (y - 1 >= 0)   // left
                update_path(x, y - 1, s, kk, grid[x][y-1], k);

        }
        queue.erase(it);
    }
    int min = 10000;
    for (auto it  = table[m - 1][n - 1].begin(); it != table[m - 1][n - 1].end(); it++)
        min = min < it->first? min : it->first;
    if (min == 10000)
        cout << -1;
    else
        cout << min;

    return 0;

}