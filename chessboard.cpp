//
// Created by leo_qian on 2021/9/26.
//
#include<vector>
#include<iostream>
using namespace std;

int main()
{
    vector<int> r1 = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    vector<int> r2 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
    vector<int> r3 = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    vector<int> r4 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
    vector<int> r5 = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    vector<int> r6 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
    vector<int> r7 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
    vector<int> r8 = {1, 0, 1, 1, 1, 1, 0, 0, 0};
    vector<int> r9 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
    vector<vector<int>> board = {r1, r2, r3, r4, r5, r6, r7, r8, r9};

    int n = board.size();
    // check validity
    // every row or coloum must be the same or opposite
    int same_rows = 0;
    int same_columns = 0;
    for (int i = 0 ; i < n; i++)
    {
        if (board[i][0] == 0)
            same_rows++;
        if (board[0][i] == 0)
            same_columns++;
        if (i > 0)
            continue;
        for (int j = i + 1; j < n; j++)
        {
            bool same_row = board[i][0] == board[j][0];
            bool same_column = board[0][i] == board[0][j];
            for (int k = 1; k < n; k++)
            {
                if (same_row != board[i][k] == board[j][k])
                    return -1;
                if (same_column != board[k][i] == board[k][j])
                    return -1;
            }
        }
    }
    // number of rows and columns start with 0 must be n/2 (n is even)
    // or (n+1)/2 or (n-1)/2 (n is odd)
    if (n % 2 == 0)
    {
        if (same_rows != n / 2)
            return -1;
        if (same_columns != n / 2)
            return -1;
    }
    else
    {
        if (same_rows != (n+1) / 2 && same_rows != (n-1) / 2)
            return -1;
        if (same_columns != (n+1) / 2 && same_columns != (n-1) / 2)
            return -1;
    }


    // check the swap time if board[0][0] is 0
    int swap1 = 0;
    int swap2 = 0;
    if (n % 2 == 0)
    {
        int min_row_swap_zero = n;
        int min_row_swap_one = n;
        for (int i = 0; i < n; i++)
        {
            int swap_zero = 0;
            int swap_one = 0;
            for (int j = 0; j < n; j += 2)
            {
                if (board[i][j] != 0)
                    swap_zero++;
                else
                    swap_one++;
            }
            min_row_swap_zero = min(min_row_swap_zero, swap_zero);
            min_row_swap_one = min(min_row_swap_one, swap_one);
        }
        int min_column_swap_zero = n;
        int min_column_swap_one = n;
        for (int i = 0; i < n; i++)
        {
            int swap_zero = 0;
            int swap_one = 0;
            for (int j = 0; j < n; j += 2)
            {
                if (board[j][i] != 0)
                    swap_zero++;
                else
                    swap_one++;
            }
            min_column_swap_zero = min(min_column_swap_zero, swap_zero);
            min_column_swap_one = min(min_column_swap_one, swap_one);
        }
        swap1 = min_row_swap_zero + min_column_swap_zero;
        swap2 = min_row_swap_one + min_column_swap_one;
    }
    else
    {
        int swap_row_zero;
        int swap_row_one;
        int swap_column_zero;
        int swap_column_one;
        for (int i = 0; i < n; i++) // find the row with more zero or one
        {
            int zeros = 0;
            int swap_zero = 0;
            int swap_one = 0;
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 0)
                    zeros++;
                if (j % 2 == 0)
                {
                    board[i][j] != 0? swap_zero++: swap_one++;
                }
            }
            if (zeros == n / 2 + 1)
                swap_row_zero = swap_zero;
            else
                swap_row_one = swap_one;
        }
        for (int i = 0; i < n; i++) // find the row with more zero or one
        {
            int zeros = 0;
            int swap_zero = 0;
            int swap_one = 0;
            for (int j = 0; j < n; j++)
            {
                if (board[j][i] == 0)
                    zeros++;
                if (j % 2 == 0)
                {
                    board[j][i] != 0? swap_zero++: swap_one++;
                }
            }
            if (zeros == n / 2 + 1)
                swap_column_zero = swap_zero;
            else
                swap_column_one = swap_one;
        }
        swap1 = swap_row_zero + swap_column_zero;
        swap2 = swap_row_one + swap_column_one;
    }

    int cost;
    int k;
    if (n % 2 == 0)
        cost = min(swap1, swap2);
    else
    {
        bool more_zero;
        if (same_rows == (n + 1) / 2)   // extra row start with 0
            {
            k = 0;
            while (board[k][0] != 0)
                k++;
            int sum = 0;
            for (int i = 0; i < n; i++)
                sum += board[k][i];
            more_zero = sum == n / 2;
            }
        else    // extra row start with 1
        {
            k = 0;
            while (board[k][0] != 1)
                k++;
            int sum = 0;
            for (int i = 0; i < n; i++)
                sum += board[k][i];
            more_zero = sum == n / 2;
        }
        cost = more_zero? swap1: swap2;
    }
    cout << cost;

    return 0;
}
