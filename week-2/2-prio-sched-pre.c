#include <stdio.h>

int main()
{
    printf("Priority Scheduling (Preemptive)\n");
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
        rTime[n], remaining[n];
    int currTime = 0, totalTAT = 0, totalWT = 0, completed = 0;

    printf("\nEnter AT BT P: \n");
    for (int i = 0; i < n; i++)
    {
        pID[i] = i + 1;

        printf("\tP%d: ", pID[i]);
        scanf("%d %d %d", &aTime[i], &bTime[i], &prio[i]);

        remaining[i] = bTime[i];
    }

    while (completed < n)
    {
        int minPrio = 99999; // init minimum priority
        int currPrc = -1;    // init current process

        for (int i = 0; i < n; i++)
        {
            if (aTime[i] <= currTime && remaining[i] > 0) // if uncompleted process arrives before current time
            {
                if (prio[i] < minPrio) // if process has lower priority
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

        // if process is entering for first time
        if (remaining[currPrc] == bTime[currPrc])
            sTime[currPrc] = currTime;

        remaining[currPrc]--;

        // if no remaining time left
        if (remaining[currPrc] == 0)
        {
            // completion time
            cTime[currPrc] = currTime + 1;

            // turnaround time
            taTime[currPrc] = cTime[currPrc] - aTime[currPrc];
            totalTAT += taTime[currPrc];

            // wait time
            wTime[currPrc] = taTime[currPrc] - bTime[currPrc];
            totalWT += wTime[currPrc];

            // response time
            rTime[currPrc] = sTime[currPrc] - aTime[currPrc];

            completed++;
        }

        currTime++;
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