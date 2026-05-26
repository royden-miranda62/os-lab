#include <stdio.h>

#define MAX_BLOCKS 10

typedef struct Block
{
    int allocated; // 0 = free, 1 = allocated
    int next;      // index of next block, -1 if end of chain
} Block;

Block disk[MAX_BLOCKS];

void initDisk()
{
    int i;
    for (i = 0; i < MAX_BLOCKS; i++)
    {
        disk[i].allocated = 0;
        disk[i].next = -1;
    }
}

void displayDisk()
{
    int i;
    printf("\n%-10s %-12s %-10s\n", "Block No.", "Status", "Next Block");
    printf("--------------------------------------\n");
    for (i = 0; i < MAX_BLOCKS; i++)
    {
        printf("%-10d %-12s", i, disk[i].allocated ? "Allocated" : "Free");
        if (disk[i].allocated)
            printf("%d", disk[i].next == -1 ? -1 : disk[i].next);
        printf("\n");
    }
}

// returns index of the first free block, or -1 if none
int findFreeBlock()
{
    int i;
    for (i = 0; i < MAX_BLOCKS; i++)
        if (!disk[i].allocated)
            return i;
    return -1;
}

int main()
{
    printf("Linked Allocation\n");
    printf("Royden Miranda 1WA24CS240\n\n");

    int numBlocks, i, prev, curr, start;

    initDisk();
    displayDisk();

    printf("\nEnter number of blocks to allocate: ");
    scanf("%d", &numBlocks);

    // find start block
    start = findFreeBlock();
    if (start == -1)
    {
        printf("\nAllocation Failed: No free blocks on disk.\n");
        return 1;
    }
    disk[start].allocated = 1;
    prev = start;

    // find and link remaining blocks
    for (i = 1; i < numBlocks; i++)
    {
        curr = findFreeBlock();
        if (curr == -1)
        {
            printf("\nAllocation Failed: Not enough free blocks.\n");
            curr = start;
            while (curr != -1)
            {
                int nxt = disk[curr].next;
                disk[curr].allocated = 0;
                disk[curr].next = -1;
                curr = nxt;
            }
            return 1;
        }
        disk[curr].allocated = 1;
        disk[prev].next = curr; // previous block points to this new block
        prev = curr;
    }

    // last block's next = -1 (NULL)
    disk[prev].next = -1;

    printf("\nFile Allocated Successfully!\n");
    printf("Linked chain: ");
    curr = start;
    while (curr != -1)
    {
        printf("[Block %d]", curr);
        if (disk[curr].next != -1)
            printf(" -> ");
        curr = disk[curr].next;
    }
    printf(" -> NULL\n");

    displayDisk();
    return 0;
}