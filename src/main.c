#include "../include/threadpool.h"
#include <stdio.h>

typedef struct
{
    int num;
    long long result;
} factorial_arg_t;

void factorial(void *arg)
{
    factorial_arg_t *factorial_arg = (factorial_arg_t *)arg;
    int num = factorial_arg->num;
    long long result = 1;
    for (int i = 2; i <= num; i++)
    {
        result *= i;
    }
    factorial_arg->result = result;
    printf("Factorial of %d is %lld\n", num, result);
}

int main()
{
    thread_pool_t *pool = thread_pool_create(4, 4); // 4 threads, 4 queue size.

    factorial_arg_t args[4];
    for (int i = 0; i < 4; i++)
    {
        args[i].num = (i + 1) * 5; // 5, 10, 15, 20.
        thread_pool_add_task(pool, factorial, &args[i]);
    }

    // Cleanup.
    thread_pool_cleanup(pool);

    return 0;
}
