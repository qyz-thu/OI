//
// Created by leo_qian on 2021/10/30.
//
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

int P = 100003;

int duplicate(string& s, int k)
{
    unordered_map<int, int> table;
    vector<pair<int,int>> collisions;
    int power[26];
    int x = 1;      // 27^(k-1) % P
    for (int i = 1; i < k; i++)
        x = x * 26 % P;
    power[0] = 0;
    power[1] = x;
    for (int i = 2; i < 26; i++)
    {
        power[i] = (power[i - 1] + x) % P;
    }
    int i = 0;
    int hash = 0;
    while (i < k)
    {
        hash = (hash * 26 + s[i] - 'a') % P;
        i++;
    }
    table[hash] = 0;
    while (i < s.size())
    {
        hash = (hash - power[s[i - k] - 'a'] + P) % P;
        hash = (hash * 26 + s[i] - 'a') % P;
        if (table.find(hash) != table.end())
        {
            // check collision
            bool collide = false;
            int start1 = table[hash], start2 = i - k + 1;
            for (int j = 0; j < k; j++)
                if (s[start1 + j] != s[start2 + j])
                {
                    collide = true; break;
                }
            if (collide)
            {
                collisions.emplace_back(hash, start1);
            }
            else return start1;
        }
        table[hash] = i - k + 1;
        i++;
    }

    return -1;
}

int main()
{
    string s = "bcanana";

    int n = s.size();
    int l = 0, h = n;
    int start;
    while (l < h - 1)
    {
        int mi = (l + h) / 2;
        int k = duplicate(s, mi);
        if (k != -1)
        {
            l = mi; start = k;
        }
        else h = mi;
    }
    cout << s.substr(start, l);

    return 0;
}
