#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A heap has current size and array of elements
struct MaxHeap
{
    int size;
    int *array;
};

void insertion_sort(int array[], int size);
void selection_sort(int array[], int size);
void swap(int *a, int *b);
void maxHeapify(struct MaxHeap *maxHeap, int idx);
struct MaxHeap *createAndBuildHeap(int *array, int size);
void heap_sort(int *array, int size);
void quick_sort(int array[], int left, int right);
void merge(int array[], int left, int mid, int right);
void merge_sort(int array[], int left, int right);
void printArray(int *array, int size);

/* Driver program to test above functions */
int main()
{
    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    int arr1[size];
    int arr2[size];
    int arr3[size];
    int arr4[size];
    int arr5[size];

    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        arr1[i] = arr2[i] = arr3[i] = arr4[i] = arr5[i] = rand();
    }

    clock_t t1;
    t1 = clock();
    insertion_sort(arr1, size);
    t1 = clock() - t1;
    double time_taken1 = ((double)t1) / CLOCKS_PER_SEC;
    printf("Time for insertion_sort is %f\n", time_taken1);

    clock_t t2;
    t2 = clock();
    selection_sort(arr2, size);
    t2 = clock() - t2;
    double time_taken2 = ((double)t2) / CLOCKS_PER_SEC;
    printf("Time for selection_sort is %f\n", time_taken2);

    clock_t t3;
    t3 = clock();
    heap_sort(arr3, size);
    t3 = clock() - t3;
    double time_taken3 = ((double)t3) / CLOCKS_PER_SEC;
    printf("Time for heap_sort is %f\n", time_taken3);

    clock_t t4;
    t4 = clock();
    quick_sort(arr4, 0, size - 1);
    t4 = clock() - t4;
    double time_taken4 = ((double)t4) / CLOCKS_PER_SEC;
    printf("Time for quick_sort is %f\n", time_taken4);

    clock_t t5;
    t5 = clock();
    merge_sort(arr5, 0, size - 1);
    t5 = clock() - t5;
    double time_taken5 = ((double)t5) / CLOCKS_PER_SEC;
    printf("Time for merge_sort is %f\n", time_taken5);

    // Check array
    // printf("Sorted array is \n");
    // printArray(arr5, size);

    return 0;
}

void insertion_sort(int array[], int size)
{
    int i, j;
    int next;
    for (i = 1; i < size; i++)
    {
        next = array[i];
        for (j = i - 1; j >= 0 && next < array[j];
             j--)
            array[j + 1] = array[j];
        array[j + 1] = next;
    }
}

void selection_sort(int array[], int size)
{
    int i, j, min, tmp;
    for (i = 0; i < size - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= size - 1; j++)
            if (array[j] < array[min])
                min = j;
        tmp = array[i];
        array[i] = array[min];
        array[min] = tmp;
    }
}

// A utility function to swap to integers
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap *maxHeap, int idx)
{
    int largest = idx;          // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2

    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->size &&
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size &&
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

// A utility function to create a max heap of given capacity
struct MaxHeap *createAndBuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap *maxHeap =
        (struct MaxHeap *)malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // Initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// The main function to sort an array of given size
void heap_sort(int *array, int size)
{
    // Build a heap from the input data.
    struct MaxHeap *maxHeap = createAndBuildHeap(array, size);

    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size; // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}

void quick_sort(int array[], int left, int right)
{
    int pivot, i, j;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = array[left];
        do
        {
            do
                i++;
            while (i <= right && array[i] < pivot);
            do
                j--;
            while (j >= left && array[j] > pivot);
            if (i < j)
                swap(&array[i], &array[j]);
        } while (i < j);
        swap(&array[left], &array[j]);
        quick_sort(array, left, j - 1);
        quick_sort(array, j + 1, right);
    }
}

// Merge 2 subarray into arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(int array[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Create temporary subarrays and copy data to them*/
    int Left_Arr[n1], Right_Arr[n2];
    for (i = 0; i < n1; i++)
        Left_Arr[i] = array[left + i];
    for (j = 0; j < n2; j++)
        Right_Arr[j] = array[mid + 1 + j];

    /* Merge data from temporary sub array into original array arr[left..right]*/
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (Left_Arr[i] <= Right_Arr[j])
        {
            array[k] = Left_Arr[i];
            i++;
        }
        else
        {
            array[k] = Right_Arr[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining member of Left_Arr[], if there are any */
    while (i < n1)
    {
        array[k] = Left_Arr[i];
        i++;
        k++;
    }

    /* Copy the remaining member of Right_Arr[], if there are any */
    while (j < n2)
    {
        array[k] = Right_Arr[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

// A utility function to print a given array of given size
void printArray(int *array, int size)
{
    int i;
    for (i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}