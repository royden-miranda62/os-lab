#include <stdio.h>

typedef struct Task
{
    int tID;
    int cap;
    int per;
    int rem;
    int next;
    int prio;
} Task;

//  gcd(m, n) = gcd(n, m%n)
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int lcm(int a, int b)
{
    return ((a * b) / gcd(a, b));
}

int main()
{
    printf("Rate Monotonic Scheduling\n");
    printf("Shorter period, higher priority.\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n], temp;
    int hyper, currTime = 0;

    printf("Enter Capacity Period: \n");
    for (int i = 0; i < n; i++)
    {
        tasks[i].tID = i + 1;

        printf("\tT%d: ", tasks[i].tID);
        scanf("%d %d", &tasks[i].cap, &tasks[i].per);

        tasks[i].rem = 0;
        tasks[i].next = 0;
    }

    // sorting tasks by period (priority)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (tasks[j].per > tasks[j + 1].per) // if period of current task is higher
            {
                // swap task
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    // assiging priority
    for (int i = 0; i < n; i++)
        tasks[i].prio = tasks[i].per;

    // defining hyperperiod
    hyper = tasks[0].per;
    for (int i = 0; i < n; i++)
        hyper = lcm(hyper, tasks[i].per);

    printf("Hyperperiod = %d\n", hyper);

    printf("\nTime\t Running Task\n");

    for (currTime = 0; currTime < hyper; currTime++)
    {
        for (int i = 0; i < n; i++)
        {
            if (currTime % tasks[i].per == 0)
            {
                tasks[i].rem = tasks[i].cap;
                tasks[i].next += tasks[i].per;
            }
        }

        int currTask = -1;

        for (int i = 0; i < n; i++)
        {
            if (tasks[i].rem > 0)
            {
                currTask = i;
                break;
            }
        }

        if (currTask != -1)
        {
            printf("%d\t T%d\n", currTime, tasks[currTask].tID);
            tasks[currTask].rem--;
        }
        else
            printf("%d\t Idle\n", currTime);
    }

    return 0;
}