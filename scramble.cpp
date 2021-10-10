//
// Created by leo_qian on 2021/10/10.
//
#include <string>
#include <iostream>
#include <set>
using namespace std;

//int order[26];
//int reverse[26];
set<string> table;

bool check(string s1, string s2)
{
    int n = s1.size();
    bool equal = true;
    for (int i = 0; i < n; i++)
        if (s1[i] != s2[i])
        {
            equal = false; break;
        }
    if (equal) return true;
    if (n <= 3)
        return true;

    string s = s1 + ' ' + s2;
    if (table.find(s) != table.end())
        return false;

    int order[26];
    int reverse[26];

    for (int i = 0; i < 26; i++)
        order[i] = reverse[i] = 0;
    int diff = 0, r_diff = 0;
    for (int i = 0; i < n - 1; i++) // divide into [0, i], (i, size)
        {
        // -1 for s1, +1 for s2
        int a = s2[i] - 'a';
        int b = s1[i] - 'a';
        int c = s1[n - 1 - i] - 'a';
        if (order[a] == 0)
            diff++;
        if (reverse[a] == 0)
            r_diff++;
        if (order[b] == 0)
            diff++;
        if (reverse[c] == 0)
            r_diff++;
        order[a]++;
        reverse[a]++;
        order[b]--;
        reverse[c]--;
        if (order[a] == 0)
            diff--;
        if (reverse[a] == 0)
            r_diff--;
        if (order[b] == 0)
            diff--;
        if (reverse[c] == 0)
            r_diff--;
        if (diff == 0)
            if (check(s1.substr(0, i+1), s2.substr(0, i+1)) && check(s1.substr(i+1, n-i-1), s2.substr(i+1, n-i-1)))
                return true;

        if (r_diff == 0)
            if (check(s1.substr(n-1-i, i+1), s2.substr(0, i+1)) && check(s1.substr(0, n-i-1), s2.substr(i+1, n-i-1)))
                return true;
        }

    table.insert(s);
    return false;
}


int main()
{
    string s1 = "eebaacbcbcadaaedceaaacadccd";
    string s2 = "eadcaacabaddaceacbceaabeccd";

    if (s1.size() != s2.size())
        return 0;
    int diff = 0;
    int n = s1.size();
    int order[26];
    int reverse[26];
    for (int i = 0; i < 26; i++)
        order[i] = reverse[i] = 0;
    for (int i = 0; i < n; i++)
    {
        int a = s1[i] - 'a';
        int b = s2[i] - 'a';
        if (order[a] == 0)
            diff++;
        if (order[b] == 0)
            diff++;
        order[a]++;
        order[b]--;
        if (order[a] == 0)
            diff--;
        if (order[b] == 0)
            diff--;
    }
    if (diff != 0)
        return 0;

    cout << check(s1, s2);
    return 0;
}