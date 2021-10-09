//
// Created by leo_qian on 2021/10/9.
//
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

struct Node
    {
unordered_map<char, int> children;
bool end;
bool found;
    };
Node tree[3000];
int head = 1;
bool taken[12][12];
vector<string> ans;
void build_trie(string);
void search_word(int, string);
void search(vector<vector<char>>&, int, int, int);


int main()
{
    vector<char> r1 = {'o', 'a', 'a', 'n'};
    vector<char> r2 = {'e', 't', 'a', 'e'};
    vector<char> r3 = {'i', 'h', 'k', 'r'};
    vector<char> r4 = {'i', 'f', 'l', 'v'};
    vector<vector<char>> board = {r1, r2, r3, r4};
    string s = "oaaneate";
    vector<string> words = {s};
    for (auto w: words)
        build_trie(w);
    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            search(board, 0, i, j);
    search_word(0, "");
    return 0;
}

void build_trie(string word)
{
    Node* p = tree;
    for (int i = 0; i < word.size(); i++)
    {
        if (p->children.find(word[i]) == p->children.end())
            p->children[word[i]] = head++;
        p = tree + p->children[word[i]];
    }
    p->end = true;
}

void search_word(int k, string s) // traverse the trie tree to find
{
    Node* p = tree + k;
    if (p->end && p->found)
        ans.push_back(s);
    for (auto it = p->children.begin(); it != p->children.end(); it++)
    {
        s.push_back(it->first);
        search_word(it->second, s);
        s.pop_back();
    }
}


void search(vector<vector<char>>& board, int k, int x, int y) // search for tree[k]'s children in adjacent cell
{
    Node* p = tree + k;
    taken[x][y] = true;
    int m = board.size(), n = board[0].size();
    for (auto it = p->children.begin(); it != p->children.end(); it++)
    {
        char c = it->first;
        int child = it->second;
        if (board[x][y] != c)
            continue;
        (tree + child)->end = true;
        if (x < m - 1 && !taken[x + 1][y])  // down
            search(board, child, x + 1, y);
        if (y < n - 1 && !taken[x][y + 1])  //right
            search(board, child, x, y + 1);
        if (x > 0 && !taken[x - 1][y])  // up
            search(board, child, x - 1, y);
        if (y > 0 && !taken[x][y - 1])  // left
            search(board, child, x, y - 1);
    }

    taken[x][y] = false;
}