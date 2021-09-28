//
// Created by leo_qian on 2021/9/27.
//
#include<string>
#include<vector>
#include<iostream>
using namespace std;

void add_p(vector<string>& ans, string s, int k, int n, int p)
{
    if (k == n - 1)
    {
        string ss;
        for (int i = 0; i < p + 2; i++)
            ss += ')';
        for (int i = 0; i < p + 1; i++)
        {
            string sss = ss;
            sss[i] = '(';
            ans.push_back(s + sss);
        }
        return;
    }
    // add_p(ans, s + "()", k + 1, n, p);
    add_p(ans, s + "(", k + 1, n, p + 1);
    for (int i = p; i > 0; i--)
    {
        string ss;
        for (int j = 0; j < i; j++)
            ss += ')';
        // add_p(ans, s + ss + "()", k + 1, n, p - i);
        add_p(ans, s + ss + '(', k + 1, n, p - i + 1);
    }
}


int main()
{
    int n = 3;

    vector<string> ans;
    add_p(ans, "", 0, n, 0);

    for (auto & an : ans)
        cout<< an << " ";
    return 0;
}


