//
// Created by leo_qian on 2021/8/4.
//

#include<iostream>
#include<string>
using namespace std;
string get_power(int);
string table[16] = {"2(0)", "2", "2+2(0)", "2(2)", "2(2)+2(0)", "2(2)+2",
                    "2(2)+2+2(0)", "2(2+2(0))", "2(2+2(0))+2(0)", "2(2+2(0))+2",
                    "2(2+2(0))+2+2(0)", "2(2+2(0))+2(2)", "2(2+2(0))+2(2)+2(0)",
                    "2(2+2(0))+2(2)+2", "2(2+2(0))+2(2)+2(0)"};

int main()
{
    string results[20];
    int count = 0;
    int n;
    cin >> n;
    int p = 0;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            if (p < 4)
                results[count++] = table[(1 << p) - 1];
            else
            {
                string s  = "2(" + table[p - 1] + ")";
                results[count++] = s;
            }
        }
        n >>= 1;
        p++;
    }
    for (int i = count - 1; i > 0; i--)
        cout << results[i] + "+";
    cout << results[0];
    cout << get_power(n);

    return 0;
}
