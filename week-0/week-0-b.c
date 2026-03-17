#include <stdio.h>

// Smallest number in array

int main()
{
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int array[n];

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    int small = array[0];
    int pos;
    for (int i = 0; i < n; i++)
    {
        if (array[i] < small)
        {
            small = array[i];
            pos = i;
        }
    }

    printf("Smallest number is %d, found at position %d.\n", small, pos);
}