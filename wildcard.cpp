//
// Created by leo_qian on 2021/10/2.
//
#include<string>
#include<iostream>
using namespace std;

bool f[2001][2001];

int main()
{
    string s = "a";
    string p = "*a";

    s.insert(s.begin(), 'a');
    p.insert(p.begin(), 'a');
    int m = s.size();
    int n = p.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (i == 0)
            {
                f[i][j] = j == 0;
            }
            else
            {
                if (p[i] == '*')
                {
                    f[i][j] = false;
                    for (int k = 0; k <= j; k++)
                        if (f[i - 1][k])
                        {
                            f[i][j] = true; break;
                        }
                }
                else if (p[i] == '?')
                {
                    if (j > 0 && f[i - 1][j - 1])
                        f[i][j] = true;
                    else f[i][j] = false;
                }
                else
                {
                    if (p[i] == s[j] && j > 0 && f[i - 1][j - 1])
                        f[i][j] = true;
                    else f[i][j] = false;
                }
            }
        }

    cout << f[n - 1][m - 1];
    return 0;

}
