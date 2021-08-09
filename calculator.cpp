//
// Created by leo_qian on 2021/8/7.
//

#include<stdio.h>
#include<string.h>

int main()
{
    char equation[100];
    scanf("%s", equation);

    int len = strlen(equation);
    int i = 0;
    int constant = 0;   // constant
    int x = 0;      // factor of unknown number
    int side = 1;
    int sign = 1;
    int factor;
    char alpha;
    while (i < len)
    {
        if (equation[i] == '-')
            sign = -1;
        else if (equation[i] == '+')
            sign = 1;
        else if (equation[i] >= '0' && equation[i] <= '9')
        {
            factor = equation[i++] - '0';
            while (equation[i] >= '0' && equation[i] <= '9')
            {
                factor *= 10;
                factor += equation[i++] - '0';
            }
            if (equation[i] >= 'a' && equation[i] <= 'z')
            {
                x += factor * sign * side;
                alpha = equation[i];
                i++;
            }
            else constant += factor * sign * side;
            i--;
        }
        else if (equation[i] >= 'a' && equation[i] <= 'z')
        {
            x += side * sign;
            alpha = equation[i];
        }
        else if (equation[i] == '=')
        {
            side = -1;
            sign = 1;
        }
        i++;
    }
    double res;
    if (constant == 0)
        res = 0;
    else res = (double) -constant / (double) x;
    printf("%c=%.3f", alpha, res);

    return 0;
}