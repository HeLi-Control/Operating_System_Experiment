#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Remember to use 'gcc threadCreate.c -o threadCreate.o -lpthread' while compling.
// The 'usleep(10)' in code is set for the print could reflect the real running order correctly.

int sum = 0;

void *runner01(void *param)
{
    int i, upper = atoi(param);
    for (i = 1; i <= upper; i++)
        sum += i;
    printf("[thread 1] sum = %d\n", sum);
    usleep(10);
}

void *runner02(void *param)
{
    int i, lower = atoi(param);
    for (i = 1; i <= lower; i++)
        sum -= i;
    printf("[thread 2] sum = %d\n", sum);
    usleep(10);
}

int main(int argc, char *argv[])
{
    /* Print the args received. */
    if (argc != 2)
    {
        fprintf(stderr, "argc = %d\n", argc);
        fprintf(stderr, "usage:a.out<integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) <= 0)
    {
        fprintf(stderr, "%d must be > 0\n", atoi(argv[1]));
        return -1;
    }

    /* Create two threads. */
    pthread_t tid01;
    pthread_attr_t attr;
    pthread_attr_init(&attr); // get default setting
    pthread_create(&tid01, &attr, runner01, argv[1]);
    pthread_join(tid01, NULL);

    pthread_t tid02;
    pthread_create(&tid02, &attr, runner02, argv[1]);
    pthread_join(tid02, NULL);

    pthread_exit(0);
}
