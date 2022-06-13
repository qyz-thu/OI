//
// Created by leo_qian on 2021/10/19.
//
#include <unordered_map>
#include <iostream>
using namespace std;

struct cache
{
    int value = -1;
    int p = -1;
    cache() {value = -10086;}
    cache(int a, int b) {
        value = a; p = b;
    }
};

struct time_order
{
    int key = -1;
    int previous = -1, next = -1;
};
int c = 2;
unordered_map<int, cache> table;
time_order list[3001];
int head = 0;
int tail = -1;
int m = 0;

int get(int key) {
    if (table.find(key) == table.end())
        return -1;
    return table[key].value;
}

void put(int key, int value) {
    if (table.find(key) == table.end()) // put new element
        {
        if (table.size() < c)   // increase
            {
            table[key] = cache(key, head);
            if (tail >= 0)
                list[tail].next = head;
            list[head].key = key;
            list[head].previous = tail;
            tail = head++;
            }
        else
        {
            table[key] = cache(key, m);
            table.erase(list[m].key);
            list[m].key = key;
            list[tail].next = m;
            list[m].previous = tail;
            int next = list[m].next;
            list[m].next = -1;
            list[next].previous = -1;
            tail = m; m = next;
        }
        }
    else
    {
        int time_id = table[key].p;
        table[key].value = value;
        if (time_id == m)
        {
            m = list[time_id].next;
            list[m].previous = -1;
            list[tail].next = time_id;
            list[time_id].previous = tail;
            list[time_id].next = -1;
            tail = time_id;
        }
        else if (time_id != tail)
        {
            list[list[time_id].previous].next = list[time_id].next;
            list[list[time_id].next].previous = list[time_id].previous;
            list[tail].next = time_id;
            list[time_id].previous = tail;
            list[time_id].next = -1;
            tail = time_id;
        }
    }
}

int main()
{
    put(1, 1);
    put(2, 2);
    cout << get(1) << ' '; cout << get(2) << " ";
    put(3, 3);
    cout << get(1) << ' '; cout << get(2) << ' ';
    put(4, 4);
    cout << get(1) << ' '; cout << get(3) << ' '; cout << get(4) << ' ';
}