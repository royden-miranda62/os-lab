#include <stdio.h>

// Duplicates in array

int main()
{
    int found = 0;

    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int array[n];

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (array[i] == array[j])
            {
                printf("Duplicate of %d found at position %d.\n", array[i], j);
                found = 1;
                break;
            }
        }
    }

    if (!found)
        printf("No duplicates found in array.\n");

    return 0;
}