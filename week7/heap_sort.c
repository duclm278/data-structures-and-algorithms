#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[30];
    char phone[15];
    char email[30];
} Address;

// A heap has current size and array of elements
struct MaxHeap
{
    int size;
    Address *array;
};

Address book[100];
int total;

void load(void);
void swap(Address *a, Address *b);
void maxHeapify(struct MaxHeap *maxHeap, int idx);
struct MaxHeap *createAndBuildHeap(Address *array, int size);
void heap_sort(void);

int main(void)
{

    int option;
    while (1)
    {
        // Print out menu
        printf("+--------------------------------------+\n");
        printf("| 1. Load file                         |\n");
        printf("| 2. Heap sort                         |\n");
        printf("| 3. Quit                              |\n");
        printf("+--------------------------------------+\n");

        // Read option
        printf("Choose an option: ");
        if (scanf("%d", &option) != 1)
            return 1;

        // Perform option
        switch (option)
        {
        case 1:
            load();
            break;
        case 2:
            heap_sort();
            break;
        case 3:
            return 0;
        default:
            return 1;
        }

        printf("\n");
    }
}

void load(void)
{
    char filename[100];
    scanf("%s", filename);
    FILE *input = fopen(filename, "r");
    if (input == NULL)
        return;

    fscanf(input, "%d", &total);
    for (int i = 0; i < total; i++)
    {
        fscanf(input, "%s %s %s", book[i].name, book[i].phone, book[i].email);
        printf("Loaded: %s %s %s\n", book[i].name, book[i].phone, book[i].email);
    }

    fclose(input);
}

// A utility function to swap to integers
void swap(Address *a, Address *b)
{
    Address t = *a;
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
    if (left < maxHeap->size && strcmp((maxHeap->array[left]).name, (maxHeap->array[largest]).name) > 0)
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size && strcmp((maxHeap->array[right]).name, (maxHeap->array[largest]).name) > 0)
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

// A utility function to create a max heap of given capacity
struct MaxHeap *createAndBuildHeap(Address *array, int size)
{
    int i;
    struct MaxHeap *maxHeap = (struct MaxHeap *)malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

void heap_sort(void)
{
    // Build a heap from the input data.
    struct MaxHeap *maxHeap = createAndBuildHeap(book, total);

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

    for (int i = 0; i < total; i++)
    {
        printf("%s %s %s\n", book[i].name, book[i].phone, book[i].email);
    }
}