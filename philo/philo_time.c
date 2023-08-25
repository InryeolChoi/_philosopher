#include "philo_info.h"

long    get_time(void)
{
    struct  timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}