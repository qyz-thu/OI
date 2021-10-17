//
// Created by leo_qian on 2021/10/16.
//
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;

int virus_num[50][50];
bool updated[50][50];

int main()
{
//    vector<int> r1 = {0,1,0,0,0,0,1,1};
//    vector<int> r2 = {0,1,0,0,0,1,0,1};
//    vector<int> r3 = {0,1,0,0,0,0,1,1};
//    vector<int> r4 = {0,0,0,0,0,0,0,0};
    vector<int> r = {1};
    vector<vector<int>> isInfected = {r};

    int m = isInfected.size();
    int n = isInfected[0].size();
    int ans = 0;
    int stack[2500];
    int head;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (isInfected[i][j]) virus_num[i][j] = 1;

    while (true)
    {
        vector<vector<pair<int, int>>> table;
        table.emplace_back();   // for id alignment
        int cls = 1;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                updated[i][j] = false;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (updated[i][j]) continue;
                updated[i][j] = true;
                if (virus_num[i][j] > 0)
                {
                    // find the virus in one region using bfs
                    virus_num[i][j] = cls;
                    vector<pair<int, int>> v;
                    v.emplace_back(i, j);
                    stack[0] = 0;
                    head = 1;
                    while (--head >= 0)
                    {
                        int x = v[stack[head]].first, y = v[stack[head]].second;
                        if (x + 1 < m && virus_num[x+1][y] > 0 && !updated[x+1][y])
                        {
                            v.emplace_back(x + 1, y);
                            stack[head++] = v.size() - 1;
                            virus_num[x+1][y] = cls;
                            updated[x+1][y] = true;
                        }
                        if (x > 0 && virus_num[x-1][y] > 0 && !updated[x-1][y])
                        {
                            v.emplace_back(x - 1, y);
                            stack[head++] = v.size() - 1;
                            virus_num[x-1][y] = cls;
                            updated[x-1][y] = true;
                        }
                        if (y + 1 < n && virus_num[x][y+1] > 0 && !updated[x][y+1])
                        {
                            v.emplace_back(x, y + 1);
                            stack[head++] = v.size() - 1;
                            virus_num[x][y+1] = cls;
                            updated[x][y+1] = true;
                        }
                        if (y > 0 && virus_num[x][y-1] > 0 && !updated[x][y-1])
                        {
                            v.emplace_back(x, y - 1);
                            stack[head++] = v.size() - 1;
                            virus_num[x][y-1] = cls;
                            updated[x][y-1] = true;
                        }
                    }
                    table.push_back(v);
                    cls++;
                }
            }
        if (cls <= 1) break;

        int* count = new int[cls];
        for (int i = 0; i < cls; i++) count[i] = 0;
        // calculated most contamination
//        set<int> neighbor_virus[50][50];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (virus_num[i][j] != 0) continue;
                set<int> neighbor_virus;
                if (i > 0 && virus_num[i-1][j] > 0)
                    neighbor_virus.insert(virus_num[i-1][j]);
                if (i + 1 < m && virus_num[i+1][j] > 0)
                    neighbor_virus.insert(virus_num[i+1][j]);
                if (j > 0 && virus_num[i][j-1] > 0)
                    neighbor_virus.insert(virus_num[i][j-1]);
                if (j + 1 < n && virus_num[i][j+1] > 0)
                    neighbor_virus.insert(virus_num[i][j+1]);
                for (int it : neighbor_virus)
                    count[it]++;
            }
        int most = -1, most_c = -1;
        for (int i = 0; i < cls; i++)
            if (count[i] > most)
            {
                most = count[i]; most_c = i;
            }

        // count walls needed
        // int wall = 0;
        auto viruses = table[most_c];
        for (auto p: viruses)
        {
            int x = p.first, y = p.second;
            if (x > 0 && virus_num[x-1][y] != most_c && virus_num[x-1][y] != -1)
                ans++;
            if (x + 1 < m && virus_num[x+1][y] != most_c && virus_num[x+1][y] != -1)
                ans++;
            if (y > 0 && virus_num[x][y-1] != most_c && virus_num[x][y-1] != -1)
                ans++;
            if (y + 1 < n && virus_num[x][y+1] != most_c && virus_num[x][y+1] != -1)
                ans++;
            virus_num[x][y] = -1;
        }
//        table.erase(table.begin() + most_c);
        if (table.size() <= 2)
            break;

        // expand contaminated region
        int survival = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (virus_num[i][j] != 0) continue;
                if (i > 0 && virus_num[i-1][j] > 0 && virus_num[i-1][j] != most_c)
                    virus_num[i][j] = most_c;
                else if (j > 0 && virus_num[i][j-1] > 0 && virus_num[i][j-1] != most_c)
                    virus_num[i][j] = most_c;
                else if (i + 1 < m && virus_num[i+1][j] > 0 && virus_num[i+1][j] != most_c)
                    virus_num[i][j] = most_c;
                else if (j + 1 < n && virus_num[i][j+1] > 0 && virus_num[i][j+1] != most_c)
                    virus_num[i][j] = most_c;
                else survival++;
            }
        if (survival == 0)
            break;
    }
    cout << ans;

    return 0;
}
