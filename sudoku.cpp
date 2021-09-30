//
// Created by leo_qian on 2021/9/29.
//
#include<set>
#include<vector>
#include<iostream>
using namespace std;
bool solved = false;
set<int> solutions[9][9];
//int stack[100][3];
//int head = 0;


void solve(vector<vector<char>>& board)
{
    // find the empty cell with least solutions
    int min = 10;
    int min_i = -1, min_j = -1;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (solutions[i][j].empty())
                continue;
            if (solutions[i][j].size() < min)
            {
                min = solutions[i][j].size();
                min_i = i; min_j = j;
            }
        }
    if (min_i == -1)
    {
        solved = true; return;
    }
    // update solution
    int modification[25][2];
    int m_head;
    bool conflict;
    int x = min_i / 3, y = min_j / 3;
    vector<int> possibility;
    for (auto m: solutions[min_i][min_j])
        possibility.push_back(m);
    solutions[min_i][min_j].clear();
    for (auto m: possibility)   // try for every possibility
    {
        m_head = 0;
        conflict = false;
        for (int i = 0; i < 9; i++)
        {
            if (solutions[min_i][i].find(m) != solutions[min_i][i].end())
            {
                if (solutions[min_i][i].size() == 1)
                {
                    conflict = true; break;
                }
                modification[m_head][0] = min_i;
                modification[m_head++][1] = i;
            }
            if (solutions[i][min_j].find(m) != solutions[i][min_j].end())
            {
                if (solutions[i][min_j].size() == 1)
                {
                    conflict = true; break;
                }
                modification[m_head][0] = i;
                modification[m_head++][1] = min_j;
            }
            int xx = 3 * x + i / 3;
            int yy = 3 * y + i % 3;
            if (solutions[xx][yy].find(m) != solutions[xx][yy].end())
            {
                if (solutions[xx][yy].size() == 1)
                {
                    conflict = true; break;
                }
                modification[m_head][0] = xx;
                modification[m_head++][1] = yy;
            }
        }
        if (conflict)
            continue;

        for (int id = 0; id < m_head; id++)
        {
            int xx = modification[id][0], yy = modification[id][1];
            solutions[xx][yy].erase(m);
        }
        board[min_i][min_j] = (char) m + '1';
        solve(board);
        if (solved)
            return;

        // restore
        for (int id = 0; id < m_head; id++)
        {
            int xx = modification[id][0], yy = modification[id][1];
            solutions[xx][yy].insert(m);
        }
    }

    board[min_i][min_j] = '.';
    for (auto m : possibility)
        solutions[min_i][min_j].insert(m);
}


set<int> find_solution(vector<vector<char>>& board, int i, int j)
{
    set<int> solution;
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
        return solution;
    if (board[i][j] != '.')
        return solution;
    bool filled[9];
    for (int a = 0; a < 9; a++) filled[a] = false;
    // check row and column
    for (int a = 0; a < 9; a++)
    {
        if (board[a][j] != '.')
            filled[board[a][j] - '1'] = true;
        if (board[i][a] != '.')
            filled[board[i][a] - '1'] = true;
    }
    // check sub-box
    int x = i / 3;
    int y = j / 3;
    for (int ii = 0; ii < 3; ii++)
        for (int jj = 0; jj < 3; jj++)
            if (board[3 * x + ii][3 * y + jj] != '.')
                filled[board[3 * x + ii][3 * y + jj] - '1'] = true;
    for (int a = 0; a < 9; a++)
        if (!filled[a])
            solution.insert(a);
    return solution;
}


int main()
{
    vector<char> r1 = {'.','.','9','7','4','8','.','.','.'};
    vector<char> r2 = {'7','.','.','.','.','.','.','.','.'};
    vector<char> r3 = {'.','2','.','1','.','9','.','.','.'};
    vector<char> r4 = {'.','.','7','.','.','.','2','4','.'};
    vector<char> r5 = {'.','6','4','.','1','.','5','9','.'};
    vector<char> r6 = {'.','9','8','.','.','.','3','.','.'};
    vector<char> r7 = {'.','.','.','8','.','3','.','2','.'};
    vector<char> r8 = {'.','.','.','.','.','.','.','.','6'};
    vector<char> r9 = {'.','.','.','2','7','5','9','.','.'};
    vector<vector<char>> board = {r1, r2, r3, r4, r5, r6, r7, r8, r9};

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            solutions[i][j] = find_solution(board, i, j);
        }

    solve(board);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << board[i][j] << ' ';
        cout << endl;
    }

}

