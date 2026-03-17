#include <stdio.h>

int main()
{
    printf("Process Scheduling - SRTF\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // arrival time = aTime        burst time = bTime
    // completion time = cTime
    // turnaround time = taTime    wait time = wTime
    // start time = sTime          response time = rTime

    int pID[n], aTime[n], bTime[n],
        cTime[n], taTime[n], wTime[n], sTime[n],
        rTime[n], remaining[n];
    int currTime = 0, totalTAT = 0, totalWT = 0, temp,
        completed = 0;

    printf("\nEnter AT BT: \n");
    for (int i = 0; i < n; i++)
    {
        pID[i] = i + 1;

        printf("\tP%d: ", pID[i]);
        scanf("%d %d", &aTime[i], &bTime[i]);
    }

    // sorting by AT
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (aTime[j] > aTime[j + 1]) // if process enters after current process
            {
                // swap PID
                temp = pID[j];
                pID[j] = pID[j + 1];
                pID[j + 1] = temp;

                // swap AT
                temp = aTime[j];
                aTime[j] = aTime[j + 1];
                aTime[j + 1] = temp;

                // swap BT
                temp = bTime[j];
                bTime[j] = bTime[j + 1];
                bTime[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
        remaining[i] = bTime[i];

    while (completed != n)
    {
        int minTime = 99999; // init minimum time
        int currPrc = -1;    // init current process

        for (int i = 0; i < n; i++)
        {
            if (aTime[i] <= currTime && remaining[i] > 0) // if uncompleted process arrives before current time
            {
                if (remaining[i] < minTime) // if process has remaining time
                {
                    minTime = remaining[i]; // assign lowest priority
                    currPrc = i;            // assign current process
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

    printf("\nPID\t AT\t BT\t CT\t TAT\t WT\t RT\n");
    for (int j = 1; j < n + 1; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (pID[i] == j)
            {
                printf("P%d\t %d\t %d\t %d\t %d\t %d\t %d\n",
                       pID[i], aTime[i], bTime[i], cTime[i],
                       taTime[i], wTime[i], rTime[i]);
            }
        }
    }

    printf("Avg. TAT = %.2f\n", ((float)totalTAT / n));
    printf("Avg. WT = %.2f\n", ((float)totalWT / n));

    return 0;
}