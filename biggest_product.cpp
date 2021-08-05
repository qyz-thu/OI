//
// Created by leo_qian on 2021/8/5.
//

#include<iostream>
#include<string>
#include<string.h>
using namespace std;

bool operator > (string a, string b)
{
    if (a.length() > b.length())
        return true;
    else if (a.length() < b.length())
        return false;
    for (int i = 0; i < a.length(); i++)
        if (a[i] > b[i])
            return true;
        else if (a[i] < b[i])
            return false;
    return false;
}

string operator * (string a, string b)
{
    char ans[50];
    memset(ans, '0', 50);
    int flag, i, j;
    int number = a.length() + b.length() - 2;
    int length;
    for (i = a.length() - 1; i >= 0; i--)
    {
        flag = 0;
        for (j = b.length() - 1; j >= 0; j--)
        {
            int x = (char) a[i] - '0';
            int y = (char) b[j] - '0';
            int previous = ans[number - i - j] - '0';
            int p = (x * y + flag + previous) % 10;
            flag = (x * y + flag + previous) / 10;
            ans[number - i - j] = p + '0';
        }
        if (flag > 0)
            ans[number - i - j] = flag + '0';
    }
    if (flag > 0)
    {
        ans[number + 1] = flag + '0';
        length = number + 1;
    }
    else length = number;

    string res;
    for (i = length; i >= 0; i--)
        res.append(ans + i, 1);

    return res;
}


int main()
{


    string s;
    int N, K;
    cin >> N >> K;
    cin >> s;
    string f[40][6];

    // f[i][j]: biggest product up to the i-th digits with j multipliers (requires j <= i)
    for (int i = 0; i < N; i++)
    {
        f[i][0] = s.substr(0, i + 1);
        for (int j = 1; j <= K && j <= i; j++)
        {
            string a = "0";
            for (int k = j - 1; k <= i - 1; k++)     // search for the biggest results when all multipliers in the first i-1 digits
            {
                string b = f[k][j - 1] * s.substr(k + 1, i - k);
                if (b > a)
                {
                    f[i][j] = b;
                    a = b;
                }
            }
        }
    }
    cout << f[N - 1][K];

    return 0;
}

