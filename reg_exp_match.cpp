//
// Created by leo_qian on 2021/9/25.
//
#include<iostream>
#include<string>
using namespace std;
bool search(string, string, int, int);

int main()
{
    string s = "bbab";
    string p = "b*a*";

    // preprocess
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i] != '*' && p[i] != '.' && (i + 1 >= p.size() || p[i + 1] != '*'))
        {
            auto index = s.find(p[i]);
            if (index == string::npos)
            {
                cout << false; return 0;
            }
        }
        if (p[i] == '*')
        {
            if (i + 2 < p.size() && p[i + 2] == '*' && p[i + 1] == p[i - 1])
            {
                p.erase(i + 1, 2); i--;
            }
        }
    }

    cout << search(s, p, 0, 0);

    return 0;
}


bool search(string s, string p, int m, int n)
{
    if (m == s.size())
    {
        if (n < p.size() - 1 && p[n + 1] == '*')
            return search(s, p, m, n + 2);
        if (n == p.size())
            return true;
        return false;
    }
    if (n == p.size())
        return false;
    if (n < p.size() - 1 && p[n+1] == '*')
        return search(s, p, m, n + 1);
    bool match;
    char c = p[n] == '*'? p[n - 1]: p[n];
    if (c == '.')
        match = true;
    else
        match = s[m] == c;
    if (match)
    {
        if (m == s.size() - 1 && n == p.size() - 1)
            return true;
        if (p[n] == '*')
        {
            return search(s, p, m + 1, n + 1) || search(s, p, m + 1, n) || search(s, p, m, n + 1);
//            return search(s, p, m, n + 1);
        }
        else
        {
            return search(s, p, m + 1, n + 1);
        }
    }
    else if (p[n] == '*')
        return search(s, p, m, n + 1);
    return false;
}