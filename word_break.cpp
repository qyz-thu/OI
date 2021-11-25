//
// Created by leo_qian on 2021/11/25.
//
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

struct node
        {
    bool leaf = false;
    unordered_map<char, int> children;
        };
node pool[10000];
int head = 1;
vector<string> current;
vector<string> ans;
unordered_set<string> table[20];
bool memory[20];

void search(string s, int k)
{
    if (k == s.size())
    {
        int x = k;
        string previous;
        for (int i = current.size() - 1; i >= 0; i--)
        {
            x -= current[i].size();
            if (i != 0)
                previous = " " + current[i] + previous;
            else previous = current[i] + previous;
            table[x].insert(previous);
        }
        // string a = current[0];

        ans.push_back(previous);
        current.pop_back();
        return ;
    }
    if (memory[k])
    {
        string a = current[0];
        for (int i = 1; i < current.size(); i++)
            a.append(" " + current[i]);
        for (auto it: table[k])
            ans.push_back(a + it);
        current.pop_back();
        return ;
    }
    node* p = pool;
    for (int i = k; i < s.size(); i++)
    {
        char c = s[i];
        if (p->children.find(c) == p->children.end())
            break;
        p = pool + p->children[c];
        if (p->leaf)
        {
            current.push_back(s.substr(k, i - k + 1));
            search(s, i + 1);
        }
    }
    if (!current.empty())
        current.pop_back();
    memory[k] = true;
}

int main()
{
    string s = "aaaaa";
    vector<string> wordDict = {"cat", "a", "aa", "aaa"};


    for (string word: wordDict)
    {
        node* p = pool;
        for (char c: word)
        {
            if (p->children.find(c) == p->children.end())
                p->children[c] = head++;
            p = pool + p->children[c];
        }
        p->leaf = true;
    }
    search(s, 0);

    return 0;
}