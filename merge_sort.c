// Partial- Merge Sort
#include <stdio.h>

int main()
{
    int arr[10], n;
    Readarray(arr);
    printf("Before sorting array elements are \n");
    print(arr, n);
    mergeSort(arr, 0, n - 1);
    printf("\nAfter sorting array elements are \n");
    print(arr, n);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int A[n1], B[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        A[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        B[j] = arr[m + l + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (A[i] <= B[j])
        {
            arr[k] = A[i];
            i++;
        }
        else
        {
            arr[k] = B[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of A[],
    // if there are any
    while (i < n1)
    {
        arr[k] = A[i];
        i++;
        k++;
    }

    // Copy the remaining elements of B[],
    // if there are any
    while (j < n2)
    {
        arr[k] = B[j];
        j++;
        k++;
    }
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