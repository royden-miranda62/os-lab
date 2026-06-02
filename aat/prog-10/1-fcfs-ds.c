#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("FCFS Disk Scheduling\n");
    printf("Royden Miranda 1WA24CS240\n\n");

    int n, head, i;
    int totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nOrder serviced: %d", head);

    for (i = 0; i < n; i++)
    {
        totalMovement += abs(req[i] - head);
        head = req[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement: %d cylinders\n", totalMovement);
    
    return 0;
}