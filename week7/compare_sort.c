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
void printArray(int *array, int size);

/* Driver program to test above functions */
int main()
{
    int arr[1000000];
    int size = sizeof(arr)/sizeof(arr[0]);
    
    srand(time(0));
    for (int i = 0; i < 1000000; i++)
    {
        arr[i] = rand();
    }

    clock_t t;
    t = clock();

    // insertion_sort(arr, size);
    // selection_sort(arr, size);
    heap_sort(arr, size);

    t = clock() - t;
    double time_taken = ((double) t)/CLOCKS_PER_SEC;

    printf("Sorted array is \n");
    printArray(arr, size);
    printf("Time is %f\n", time_taken);
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
void swap(int *a, int *b) { int t = *a; *a = *b;  *b = t; }

// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap *maxHeap, int idx)
{
    int largest = idx;  // Initialize largest as root
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
    struct MaxHeap* maxHeap =
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
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
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
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