#include <stdio.h>

// Linear search

int main()
{
    int array[] = {2, 5, 6, 1, 7, 4, 3};
    int ele, found = 0;
    int length = sizeof(array) / sizeof(array[0]);

    printf("Array elements: ");
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);

    printf("\nEnter element to search: ");
    scanf("%d", &ele);

    for (int i = 0; i < length; i++)
    {
        if (array[i] == ele)
        {
            printf("%d found at position %d.\n", ele, i);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("%d not found in array.\n", ele);

    return 0;
} 

// Binary search

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(array) / sizeof(array[0]);
    int low = 0, mid, high = length - 1;
    int ele, found = 0;

    printf("Array elements: ");
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);

    printf("\nEnter element to search: ");
    scanf("%d", &ele);

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (array[mid] == ele)
        {
            printf("%d found at position %d.\n", ele, mid);
            found = 1;
            break;
        }
        else if (array[mid] < ele)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (!found)
        printf("%d not found in array.\n", ele);

    return 0;
}