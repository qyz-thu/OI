//
// Created by leo_qian on 2021/9/28.
//
#include<string>
#include<vector>
#include<unordered_map>
#include<iostream>
using namespace std;

struct Node
{
    int depth;
    vector<int> index;
    unordered_map<char, Node*> children;
    Node(int x): depth(x) {}
};


int main()
{
    string s = "foobarfoobarthefoobarman";
    vector<string> words = {"foo", "bar"};


    vector<int> ans;
    Node* heads[26];
    for (auto & head : heads)
        head = nullptr;
    int len = words[0].size();
    int id = 0;
    for (auto it = words.begin(); it != words.end(); it++, id++)
    {
        char c = (*it)[0];
        if (!heads[c - 'a'])
            heads[c - 'a'] = new Node(0);
        Node* p = heads[c - 'a'];
        for (int i = 1; i < it->size(); i++)
        {
            c = (*it)[i];
            auto child = p->children.find(c);
            if (child == p->children.end())
                p->children[c] = new Node(p->depth + 1);
            p = p->children[c];
        }
        p->index.push_back(id);
    }

    bool *pool = new bool[words.size()];
    int* last_pos = new int[words.size()];
    for (int start = 0; start < len; start++)
    {
        int i = start;
        for (int ii = 0; ii < words.size(); ii++)
        {
            pool[ii] = false;
            last_pos[ii] = -1;
        }
        int current_count = 0;
        while (i + len <= s.size())
        {
            int j = 1;
            char c = s[i];
            if (!heads[c - 'a'])
            {
                i += len;
                current_count = 0;
                for (int ii = 0; ii < words.size(); ii++)
                {
                    pool[ii] = false;
                    last_pos[ii] = -1;
                }
                continue;
            }
            Node* p = heads[c - 'a'];
            while (j < len)
            {
                if (p->children.find(s[i + j]) != p->children.end())
                    p = p->children[s[i + j++]];
                else
                    break;
            }
            if (!p->index.empty())  // found one
            {
                int free = -1;
                int first = i;
                int first_word;
                for (auto word_index : p->index)
                {
                    if (!pool[word_index])
                    {
                        free = word_index; break;
                    }
                    if (first > last_pos[word_index])
                    {
                        first = last_pos[word_index];
                        first_word = word_index;
                    }
                }
                if (free == -1) // too many use of this word, remove the first usage and all records before it
                {
                    last_pos[first_word] = i;
                    current_count = 0;
                    for (int ii = 0; ii < words.size(); ii++)
                    {
                        if (last_pos[ii] < first)
                        {
                            pool[ii] = false;
                            last_pos[ii] = -1;
                        }
                        else current_count++;
                    }
                }
                else
                {
                    current_count++;
                    last_pos[free] = i;
                    pool[free] = true;
                    if (current_count == words.size())
                    {
                        current_count--;
                        ans.push_back(i - (words.size() - 1) * len);
                        // remove first record
                        int min = i;
                        int min_i = 0;
                        for (int ii = 0; ii < words.size(); ii++)
                            if (last_pos[ii] < min)
                            {
                                min = last_pos[ii];
                                min_i = ii;
                            }
                        last_pos[min_i] = -1;
                        pool[min_i] = false;
                    }
                }
            }
            else    // delete all records
            {
                current_count = 0;
                for (int ii = 0; ii < words.size(); ii++)
                {
                    pool[ii] = false;
                    last_pos[ii] = -1;
                }
            }
            i += len;
        }

    }

    for (auto a : ans)
        cout << a << " " ;


    return 0;


}