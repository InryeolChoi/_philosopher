#include "bonus_info.h"

static int  blank_sign(char *str, int i, int *sign)
{
    while (str[i] >= 9 && str[i] <= 13)
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            (*sign) = -1;
        i++;
    }
    return (i);
}

int ft_atoi(char *str)
{
    int     i;
    int     sign;
    long    num;

    i = 0;
    sign = 1;
    num = 0;
    i = blank_sign(str, i, &sign);
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        if (num >= LONG_MAX / 10 || (num == LONG_MAX / 10 - 1 && num % 10 > 7))
        {
            if (sign == 1)
                return ((int)LONG_MAX);
            else
                return ((int)LONG_MIN);
        }
        num = (num * 10 + str[i] - '0');
        i++;
    }
    return ((int)(sign * num));
}

int ft_error(char *str)
{
    printf("%s", str);
    return (1);
}