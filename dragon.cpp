//
// Created by leo_qian on 2021/8/5.
//

#include<iostream>
#include<string>
using namespace std;
string words[20];
int n;
int dragon;     // the maximum length of dragon
int overlap[20][20];    // overlap[i][j] is the overlap between the end of i and the start of j
int used[20];
int length[20];
void search(int, int);
void search(char);

int main()
{
    cin >> n;
    char head;
    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
        length[i] = words[i].length();
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int l = 1;
            while (l <= length[i] && l <= length[j])
            {
                if (words[j].substr(0, l) == words[i].substr(length[i] - l, l))
                {
                    overlap[i][j] = l;
                    break;
                }
                l++;
            }
            if (overlap[i][j] == length[i] || overlap[i][j] == length[j])
                overlap[i][j] = 0;  // can't be contained
        }
    cin >> head;
        search(head);
        cout << dragon;

        return 0;
}

void search(int a, int l)
{
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (overlap[a][i] > 0 && used[i] < 2)
        {
            used[i]++;
            search(i, length[i] - overlap[a][i] + l);
            used[i]--;
            found = true;
        }
    }
    if (!found)
        dragon = dragon > l? dragon: l;
}

void search(char a)
{
    for (int i = 0; i < n; i++)
        if (words[i][0] == a)
        {
            used[i]++;
            search(i, length[i]);
            used[i]--;
        }
}