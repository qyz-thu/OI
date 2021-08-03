//
// Created by leo_qian on 2021/8/3.
//

#include<stdio.h>


int main()
{
    double D1, C, D2, P;
    int N;
    double station[10][2];
    double remain = 0;
    double cost = 0;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);
    double distance = C * D2;
    station[0][0] = 0;
    station[0][1] = P;
    int i, j;
    for (i = 0; i < N; i++)
    {
        double di, pi;
        scanf("%lf %lf", &di, &pi);
        station[i + 1][0] = di;
        station[i + 1][1] = pi;
    }
    for (i = 0; i <= N; i++)
    {
        if (distance < station[i + 1][0] - station[i][0])
        {
            printf("No Solution");
            return 0;
        }
        int cheap = i;
        j = i + 1;
        while (j <= N && station[j][0] - station[i][0] < distance)    // find the first station with cheaper gas within the reach
        {
            if (station[j][1] < station[i][1])
            {
                cheap = j;
                break;
            }
            j++;
        }
        if (i > 0)
            remain -= (station[i][0] - station[i - 1][0]) / D2;
        double dist2go = D1 - station[i][0];
        if (cheap == i)
        {
            if (dist2go < distance) // add gas just enough to the destination
            {
                double gas_needed = dist2go / D2 - remain;
                cost += gas_needed * station[i][1];
                break;
            }
            else    // fill up
            {
                cost += station[i][1] * (C - remain);
                remain = C;
            }
        }
        else
        {
            if (remain * D2 < station[cheap][0] - station[i][0])    // get to the next cheap station
            {
                double gas_needed = (station[cheap][0] - station[i][0]) / D2 - remain;
                cost += gas_needed * station[i][1];
                remain += gas_needed;
            }
        }
    }
    printf("%.2f", cost);

    return 0;
}