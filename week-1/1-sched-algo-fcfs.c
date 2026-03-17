#include <stdio.h>

int main()
{
    printf("Process Scheduling - FCFS\n");
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
        rTime[n];
    int currTime = 0, totalTAT = 0, totalWT = 0, temp;

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
    {
        if (currTime < aTime[i])
            currTime = aTime[i];

        sTime[i] = currTime;

        // completion time
        cTime[i] = currTime + bTime[i];

        // turnaround time
        taTime[i] = cTime[i] - aTime[i];
        totalTAT += taTime[i];

        // wait time
        wTime[i] = taTime[i] - bTime[i];
        totalWT += wTime[i];

        // response time
        rTime[i] = sTime[i] - aTime[i];

        currTime = cTime[i];
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