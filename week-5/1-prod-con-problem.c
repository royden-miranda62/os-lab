#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

typedef struct Item
{
    int value;
} Item;

Item buffer[BUFFER_SIZE];
int in = 0, out = 0;
int counter = 0;

// producer section
void producer()
{
    while (counter == BUFFER_SIZE)
        ;

    Item nextProduced;
    printf("Enter value to produce: ");
    scanf("%d", &nextProduced.value);

    buffer[in] = nextProduced;
    printf("Produced %d at position %d.\n", nextProduced.value, in);

    in = (in + 1) % BUFFER_SIZE;
    counter++;
}

void consumer()
{
    while (counter == 0)
        ;

    Item nextConsumed = buffer[out];
    printf("Consumed %d from position %d.\n", nextConsumed.value, out);

    out = (out + 1) % BUFFER_SIZE;
    counter--;
}

int main()
{
    printf("Producer-Consumer Problem\n");
    printf("Royden Miranda 1WA24CS240\n");

    int choice;

    while (1)
    {
        printf("\n1. Produce\t 2. Consume\t 3. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            producer();
            break;
        case 2:
            consumer();
            break;
        case 3:
            printf("Exiting.");
            exit(0);
            break;

        default:
            printf("Error: Invalid choice.");
            break;
        }
    }

    return 0;
}
