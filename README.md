# thread-pool-in-c

A simple thread pool implementation in C

## Dependencies

pthread lib

## Usage

- The `queue_init`, `queue_push`, and `queue_pop` functions are used to manage the task queue. These operations are protected with a mutex to prevent data races.
- The `thread_pool_worker` function is the entry point for each thread in the pool. It continuously dequeues tasks and runs them. If there are no tasks available, it waits for one second and then tries again.
- The `thread_pool_create` function creates a new thread pool with a specified number of threads and queue size. It also initializes the queue and creates the worker threads.
- The `thread_pool_add_task` function is used to add a new task to the thread pool. It simply enqueues the task.

## TODOs

- pool resizing
- error handling

## Example

This small example uses this thread pool lib to execute tasks in parallel. In this example, let's create a function that will calculate the factorial of a number, and then use the thread pool to calculate the factorials of multiple numbers at the same time.

```c
#include <stdio.h>

typedef struct {
    int num;
    long long result;
} factorial_arg_t;

void factorial(void* arg) {
    factorial_arg_t* factorial_arg = (factorial_arg_t*)arg;
    int num = factorial_arg->num;
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    factorial_arg->result = result;
    printf("Factorial of %d is %lld\n", num, result);
}
```

This function calculates the factorial of a number and stores the result in the result field of the `factorial_arg_t` struct. It also prints the result to the standard output.

Now, let's use the thread pool to calculate the factorials of the numbers 5, 10, 15, and 20:

```c
int main() {
    thread_pool_t* pool = thread_pool_create(4, 4); // 4 threads, 4 queue size.

    factorial_arg_t args[4];
    for (int i = 0; i < 4; i++) {
        args[i].num = (i+1) * 5; // 5, 10, 15, 20.
        thread_pool_add_task(pool, factorial, &args[i]);
    }

    // Cleanup.
    thread_pool_cleanup(pool);

    return 0;
}
```

This code first creates a thread pool with 4 threads and a queue size of 4. It then adds 4 tasks to the pool, each of which calculates the factorial of a number. The arguments for the tasks are stored in an array, so that the memory for them remains valid until all tasks have finished.

The output of this program should be the factorials of the numbers 5, 10, 15, and 20, printed in some order. The order is not determined, because the tasks are executed in parallel.
