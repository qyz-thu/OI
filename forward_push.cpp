//
// Created by leo_qian on 2022/5/4.
//
#include<stdio.h>
#include<time.h>
#include<cstdlib>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<fstream>
#include<iostream>
#include<direct.h>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;

// number of vertices
//#define N 1971280
#define N 7733822
// number of edges
//#define M 5533214
#define M 8156517
#define alpha 0.2
#define lambda 0.00001
double pi[N + 1];
double r[N + 1];
vector<int> adj[N + 1];
double r_max = lambda / M;

int main()
{
    // read graph
    FILE *fp = nullptr;
//    fp = fopen("../roadNet-CA.txt", "r");
    fp = fopen("../road-great-britain-osm.mtx", "r");
    int a, b;
    int i = 0;
    int m = 0;
    while (fscanf(fp, "%d %d", &a, &b) != EOF)
    {
        i++;
//        if (i >= 10000) break;
        adj[a].push_back(b);
        adj[b].push_back(a);
        m = max(m, max(a, b));
    }
    fclose(fp);
//    printf("%d\n%d", i, m);

    // initialize r
    for (double & i : r)
        i = 1;
    // initialize active vertices
    unordered_set<int> active_nodes;
    for (int i = 1; i < N + 1; i++)
        active_nodes.insert(i);
    const clock_t begin = clock();
    while (!active_nodes.empty())
    {
        // randomly choose one active node
        auto it = active_nodes.begin();
        int v = *it;

        pi[v] += r[v] * alpha;
        int d = adj[v].size();
        for (int u: adj[v])
        {
            r[u] += (1 - alpha) * r[v] / d;
            if (r[u] > adj[u].size() * lambda)
                active_nodes.insert(u);
        }
        r[v] = 0;
        active_nodes.erase(v);
    }
    cout << "time used" << float(clock() - begin) / CLOCKS_PER_SEC;

    // write results to file
    fp = nullptr;
    fp = fopen("../road-gb-fwdpsh.txt", "w");
    for (i = 0; i < N + 1; i++)
        fprintf(fp, "%.6f\n", pi[i]);

    return 0;
}