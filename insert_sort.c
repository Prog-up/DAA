#include <math.h>
#include <stdio.h>

void insertionSort(int arr[], int len)
{
    int tmp = 0;
    for (int i = 1; i < len; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        }
    }
}

void printArray(int arr[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubble_sort(int arr[], int len)
{
    int tmp = 0;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    int len = sizeof(arr) / sizeof(arr[0]);

    // insertionSort(arr, len);
    bubble_sort(arr, len);
    printArray(arr, len);

    return 0;
}
