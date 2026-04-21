#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Process
{
    int pID;
    int tix;
} Process;

int main()
{
    printf("Proportional Share Scheduling\n");
    printf("Royden Miranda 1WA24CS240\n");

    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    Process prcss[n];
    srand(time(NULL));
    int totalTix = 0;

    printf("Enter tickets: \n");
    for (int i = 0; i < n; i++)
    {
        prcss[i].pID = i + 1;

        printf("\tP%d: ", prcss[i].pID);
        scanf("%d", &prcss[i].tix);

        totalTix += prcss[i].tix;
    }

    int timePer;
    printf("Enter time period: ");
    scanf("%d", &timePer);
    printf("\n");
     
    for (int i = 0; i < timePer; i++)
    {
        int winTicket = rand() % totalTix + 1;
        int ticketPool = 0;
        int winIndex = 0;

        for (int j = 0; j < n; j++)
        {
            ticketPool += prcss[j].tix;
            if (winTicket <= ticketPool)
            {
                winIndex = j;
                break;
            }
        }

        printf("Time: %d\n Ticket picked: %d    Winner: P%d\n", i, winTicket, prcss[winIndex].pID);
    }
    
    printf("\n\tScheduling Summary \n");
    for (int i = 0; i < n; i++)
    {
        float share = ((float)prcss[i].tix / totalTix) * 100;
        printf("P%d gets %.2f%% of processor time.\n", prcss[i].pID, share);
    }

    return 0;
}
