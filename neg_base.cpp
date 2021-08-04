//
// Created by leo_qian on 2021/8/4.
//

#include<stdio.h>
char digits[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

int main()
{
//    printf("%d", -10 % (9));
    int n, r;
    char res[20];
    int count = 0;
    scanf("%d %d", &n, &r);
    printf("%d=", n);
    int dd = r;
    int d = 1;
    while (n != 0)
    {
        if ((long long) n * (long long) d > 0)  // 同号
        {
            int quotient = (n % dd) / d;
            res[count++] = digits[quotient];
            n -= quotient * d;
        }
        else
        {
            int quotient = (n % dd) / d;
            if (quotient != 0)
                quotient -= r;
            res[count++] = digits[quotient];
            n -= quotient * d;
        }
        d *= r;
        dd *= r;
    }
    for (int i = count - 1; i >= 0; i--)
        printf("%c", res[i]);
    printf("(base%d)", r);

    return 0;
}