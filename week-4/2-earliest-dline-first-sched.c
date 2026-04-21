#include <stdio.h>

typedef struct Task
{
    int tID;
    int cap;
    int per;
    int dLine;
    int rem;
    int next;
    int absDLine;
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
    printf("Earlist Deadline First Scheduling\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    int hyper = 1, currTime = 0;

    printf("Enter Capacity Period Deadline: \n");
    for (int i = 0; i < n; i++)
    {
        tasks[i].tID = i + 1;

        printf("\tT%d: ", tasks[i].tID);
        scanf("%d %d %d", &tasks[i].cap, &tasks[i].per, &tasks[i].dLine);

        tasks[i].rem = 0;
        tasks[i].next = 0;
        tasks[i].absDLine = 0;
    }

    // defining hyperperiod
    for (int i = 0; i < n; i++)
        hyper = lcm(hyper, tasks[i].per);

    printf("Hyperperiod = %d\n", hyper);

    printf("\nTime\t Running Task\n");

    for (currTime = 0; currTime < hyper; currTime++)
    {
        for (int i = 0; i < n; i++)
        {
            if (currTime == tasks[i].next)
            {
                tasks[i].rem = tasks[i].cap;
                tasks[i].absDLine = currTime + tasks[i].dLine;
                tasks[i].next += tasks[i].per;
            }
        }

        int currTask = -1;

        for (int i = 0; i < n; i++)
        {
            if (tasks[i].rem > 0)
            {
                if (currTask == -1 || tasks[i].absDLine < tasks[currTask].absDLine)
                {
                    currTask = i;
                }
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