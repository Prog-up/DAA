// Partial-Quick Sort
#include <stdio.h>


int main()
{
    int arr[10], n;
    Readarray(arr);
    printf("Before sorting array elements are \n");
    print(arr, n);
    quick(arr, 0, n - 1);
    printf("\nAfter sorting array elements are \n");
    print(arr, n);
}

void quick(int a[], int start, int end)
{
    if (start < end)
    {
        int par = partition(a, start, end);
        quick(a, start, par);
        quick(a, par+1, end);
    }
}

int partition(int a[], int start, int end)
{
    int pivot = a[end];
    int i = (start - 1);

    for (int j = start; j < end; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
        }
    }
    int t = a[i + 1];
    a[i+1] = a[end];
    a[end] = t;
    return (i + 1);
}

Readarray(int arr[])
{
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", arr[i]);
    }
}

void print(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int linear_search(int *a, int len, int x)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] == x)
            return i;
    }
    return -1;
}