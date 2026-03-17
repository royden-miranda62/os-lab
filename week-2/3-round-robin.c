#include <stdio.h>

int main()
{
    printf("Round Robin Scheduling\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // arrival time = aTime        burst time = bTime
    // completion time = cTime     turnaround time = taTime
    // wait time = wTime           start time = sTime
    // response time = rTime       ready queue = readyQ

    int pID[n], aTime[n], bTime[n], cTime[n],
        taTime[n], wTime[n], sTime[n],
        rTime[n], remaining[n], inQueue[n];
    int currTime = 0, totalTAT = 0, totalWT = 0,
        completed = 0, timeQuant = 0;
    int readyQ[n], front = 0, rear = -1, qSize = 0;

    printf("\nEnter AT BT: \n");
    for (int i = 0; i < n; i++)
    {
        pID[i] = i + 1;

        printf("\tP%d: ", pID[i]);
        scanf("%d %d", &aTime[i], &bTime[i]);

        remaining[i] = bTime[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuant);

    for (int i = 0; i < n; i++)
        inQueue[i] = 0;

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (aTime[i] <= currTime && remaining[i] > 0) // if uncompleted process arrives before current time
            {
                if (!inQueue[i]) // if process not in queue
                {
                    rear = (rear + 1) % n;
                    readyQ[rear] = i; // enqueue process
                    inQueue[i] = 1;   // flag process as part of queue
                    qSize++;
                }
            }
        }

        // accounting for CPU idle time
        if (qSize == 0) // if ready queue empty
        {
            currTime++;
            continue;
        }

        // dequeue process
        int currPrc = readyQ[front];
        front = (front + 1) % n;
        inQueue[currPrc] = 0;
        qSize--;

        // if process is entering for first time
        if (remaining[currPrc] == bTime[currPrc])
            sTime[currPrc] = currTime;

        if (remaining[currPrc] < timeQuant) // if less remaining time than quantum
        {
            currTime += remaining[currPrc]; // complete entire process
            remaining[currPrc] = 0;
        }
        else
        {
            currTime += timeQuant; // complete quantum amount of process
            remaining[currPrc] -= timeQuant;
        }

        for (int j = 0; j < n; j++)
        {
            if (aTime[j] <= currTime && remaining[j] > 0)
            {
                if (!inQueue[j] && j != currPrc)
                {
                    rear = (rear + 1) % n;
                    readyQ[rear] = j;
                    inQueue[j] = 1;
                    qSize++;
                }
            }
        }

        // if no remaining time left
        if (remaining[currPrc] == 0)
        {
            // completion time
            cTime[currPrc] = currTime;

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
        else
        {
            rear = (rear + 1) % n;
            readyQ[rear] = currPrc;
            inQueue[currPrc] = 1;
            qSize++;
        }
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