#include <stdio.h>

int main()
{
    printf("Multi-level Queue Scheduling\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // arrival time = aTime        burst time = bTime
    // completion time = cTime     turnaround time = taTime
    // wait time = wTime
    // sys = system                usr = user

    int sysPID[n], sysAT[n], sysBT[n], sysCT[n],
        sysTAT[n], sysWT[n], sSize = 0;
    int usrPID[n], usrAT[n], usrBT[n], usrCT[n],
        usrTAT[n], usrWT[n], uSize = 0;
    int currTime = 0, totalTAT = 0, totalWT = 0, temp, type[n];

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);

        printf("\n\tEnter process type (0 = System, 1 = User): ");
        scanf("%d", &type[i]);

        printf("\tEnter AT BT: ");
        if (type[i] == 0)
        {
            sysPID[sSize] = i + 1;
            scanf("%d %d", &sysAT[sSize], &sysBT[sSize]);
            sSize++;
        }
        else if (type[i] == 1)
        {
            usrPID[uSize] = i + 1;
            scanf("%d %d", &usrAT[uSize], &usrBT[uSize]);
            uSize++;
        }
    }

    // sorting sys processes by AT
    for (int i = 0; i < sSize; i++)
    {
        for (int j = 0; j < sSize - i - 1; j++)
        {
            if (sysAT[j] > sysAT[j + 1])
            {
                temp = sysPID[j];
                sysPID[j] = sysPID[j + 1];
                sysPID[j + 1] = temp;

                temp = sysAT[j];
                sysAT[j] = sysAT[j + 1];
                sysAT[j + 1] = temp;

                temp = sysBT[j];
                sysBT[j] = sysBT[j + 1];
                sysBT[j + 1] = temp;
            }
        }
    }
    
    // sorting user processes by AT
    for (int i = 0; i < uSize; i++)
    {
        for (int j = 0; j < uSize - i - 1; j++)
        {
            if (usrAT[j] > usrAT[j + 1])
            {
                temp = usrPID[j];
                usrPID[j] = usrPID[j + 1];
                usrPID[j + 1] = temp;

                temp = usrAT[j];
                usrAT[j] = usrAT[j + 1];
                usrAT[j + 1] = temp;

                temp = usrBT[j];
                usrBT[j] = usrBT[j + 1];
                usrBT[j + 1] = temp;
            }
        }
    }

    // system queue (higher priority, executed first)
    for (int i = 0; i < sSize; i++)
    {
        if (currTime < sysAT[i])
            currTime = sysAT[i];

        sysCT[i] = currTime + sysBT[i];

        sysTAT[i] = sysCT[i] - sysAT[i];
        totalTAT += sysTAT[i];

        sysWT[i] = sysTAT[i] - sysBT[i];
        totalWT += sysWT[i];

        currTime = sysCT[i];
    }

    // user queue (lower priority, executed next)
    for (int i = 0; i < uSize; i++)
    {
        if (currTime < usrAT[i])
            currTime = usrAT[i];

        usrCT[i] = currTime + usrBT[i];

        usrTAT[i] = usrCT[i] - usrAT[i];
        totalTAT += usrTAT[i];

        usrWT[i] = usrTAT[i] - usrBT[i];
        totalWT += usrWT[i];

        currTime = usrCT[i];
    }

    printf("\nPID\t AT\t BT\t CT\t TAT\t WT\n");

    for (int j = 1; j < n + 1; j++)
    {
        for (int i = 0; i < sSize; i++)
        {
            if (sysPID[i] == j)
            {
                printf("P%d\t %d\t %d\t %d\t %d\t %d\n",
                       sysPID[i], sysAT[i], sysBT[i],
                       sysCT[i], sysTAT[i], sysWT[i]);
            }
        }

        for (int i = 0; i < uSize; i++)
        {
            if (usrPID[i] == j)
            {
                printf("P%d\t %d\t %d\t %d\t %d\t %d\n",
                       usrPID[i], usrAT[i], usrBT[i],
                       usrCT[i], usrTAT[i], usrWT[i]);
            }
        }
    }

    printf("Avg. TAT = %.2f\n", ((float)totalTAT / n));
    printf("Avg. WT = %.2f\n", ((float)totalWT / n));

    return 0;
}