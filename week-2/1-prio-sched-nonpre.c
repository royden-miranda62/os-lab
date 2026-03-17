#include <stdio.h>

int main()
{
    printf("Priority Scheduling (Non-Preemptive)\n");
    printf("Lower the number, higher the priority.\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // arrival time = aTime        burst time = bTime
    // priority = prio             completion time = cTime
    // turnaround time = taTime    wait time = wTime
    // start time = sTime          response time = rTime

    int pID[n], aTime[n], bTime[n], prio[n],
        cTime[n], taTime[n], wTime[n], sTime[n],
        rTime[n], done[n];
    int currTime = 0, totalTAT = 0, totalWT = 0, completed = 0;

    printf("\nEnter AT BT P: \n");
    for (int i = 0; i < n; i++)
    {
        pID[i] = i + 1;

        printf("\tP%d: ", pID[i]);
        scanf("%d %d %d", &aTime[i], &bTime[i], &prio[i]);

        done[i] = 0;
    }

    while (completed < n)
    {
        int minPrio = 999; // init minimum priority
        int currPrc = -1;  // init current process

        for (int i = 0; i < n; i++)
        {
            if (aTime[i] <= currTime && !done[i]) // if uncompleted process arrives before current time
            {
                if (prio[i] < minPrio) // if process is of lower priority
                {
                    minPrio = prio[i]; // assign lowest priority
                    currPrc = i;       // assign current process
                }
            }
        }

        // accounting for CPU idle time
        if (currPrc == -1)
        {
            currTime++;
            continue;
        }

        sTime[currPrc] = currTime;

        // completion time
        cTime[currPrc] = sTime[currPrc] + bTime[currPrc];

        // turnaround time
        taTime[currPrc] = cTime[currPrc] - aTime[currPrc];
        totalTAT += taTime[currPrc];

        // wait time
        wTime[currPrc] = taTime[currPrc] - bTime[currPrc];
        totalWT += wTime[currPrc];

        // response time
        rTime[currPrc] = sTime[currPrc] - aTime[currPrc];

        currTime = cTime[currPrc];

        done[currPrc] = 1;
        completed++;
    }

    printf("\nPID\t AT\t BT\t P \t CT\t TAT\t WT\t RT\n");
    for (int j = 1; j < n + 1; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (pID[i] == j)
            {
                printf("P%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
                       pID[i], aTime[i], bTime[i], prio[i], cTime[i],
                       taTime[i], wTime[i], rTime[i]);
            }
        }
    }

    printf("Avg. TAT = %.2f\n", ((float)totalTAT / n));
    printf("Avg. WT = %.2f\n", ((float)totalWT / n));

    return 0;
}