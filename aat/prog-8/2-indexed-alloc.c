#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_INDEX 5

int disk[MAX_BLOCKS]; // 0 = free, 1 = allocated

void displayDisk()
{
    printf("\n%-10s %-10s\n", "Block No.", "Status");
    printf("----------------------------\n");
    for (int i = 0; i < MAX_BLOCKS; i++)
        printf("%-10d %-10s\n", i, disk[i] ? "Allocated" : "Free");
}

int main()
{
    printf("Indexed Allocation\n");
    printf("Royden Miranda 1WA24CS240\n\n");

    int i, indexBlock, numData, canAllocate;
    int indexTable[MAX_INDEX]; // stores block numbers of data blocks

    // init all blocks as free
    for (i = 0; i < MAX_BLOCKS; i++)
        disk[i] = 0;

    displayDisk();

    // find index block number
    printf("\nEnter index block number: ");
    scanf("%d", &indexBlock);

    if (indexBlock < 0 || indexBlock >= MAX_BLOCKS)
    {
        printf("Error: Invalid block number.\n");
        return 1;
    }

    // allocate index block if free
    if (disk[indexBlock] == 1)
    {
        printf("Error: Index block %d is already in use.\n", indexBlock);
        return 1;
    }
    disk[indexBlock] = 1;
    printf("Index block %d allocated.\n", indexBlock);

    // get data block numbers
    printf("Enter number of data blocks needed: ");
    scanf("%d", &numData);

    if (numData <= 0 || numData > MAX_INDEX)
    {
        printf("Error: Number of data blocks must be between 1 and %d.\n", MAX_INDEX);
        disk[indexBlock] = 0;
        return 1;
    }

    printf("Enter the block numbers for the data blocks:\n");
    for (i = 0; i < numData; i++)
    {
        printf("  Data block %d: ", i + 1);
        scanf("%d", &indexTable[i]);
    }

    // check if all requested data blocks are free
    canAllocate = 1;
    for (i = 0; i < numData; i++)
    {
        int b = indexTable[i];

        if (b < 0 || b >= MAX_BLOCKS || b == indexBlock || disk[b] == 1)
        {
            printf("Error: Block %d is invalid or already allocated.\n", b);
            canAllocate = 0;
            break;
        }
    }

    // allocate data blocks and store in index table
    if (canAllocate)
    {
        for (i = 0; i < numData; i++)
            disk[indexTable[i]] = 1;

        printf("\nFile Allocated Successfully!\n");
        printf("Index Block : %d\n", indexBlock);
        printf("Data Blocks : ");
        for (i = 0; i < numData; i++)
            printf("%d ", indexTable[i]);
        printf("\n");
    }
    else
    {
        printf("\nAllocation Failed.\n");
        disk[indexBlock] = 0;
    }

    displayDisk();
    return 0;
}