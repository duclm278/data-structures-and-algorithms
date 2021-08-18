#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[30];
    char phone[15];
    char email[30];
} Address;

Address book[100];
int total;

void load(void);
void swap(Address *a, Address *b);
void merge_sort(Address arr[], int left, int right);
void merge(Address arr[], int left, int mid, int right);
void print_array(void);

int main(void)
{

    int option;
    while (1)
    {
        // Print out menu
        printf("+--------------------------------------+\n");
        printf("| 1. Load file                         |\n");
        printf("| 2. Merge sort                        |\n");
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
            merge_sort(book, 0, total - 1);
            print_array();
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

void swap(Address *a, Address *b)
{
    Address t = *a;
    *a = *b;
    *b = t;
}

void merge_sort(Address arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge 2 subarray into arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(Address arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Create temporary subarrays and copy data to them*/
    Address Left_Arr[n1], Right_Arr[n2];
    for (i = 0; i < n1; i++)
        Left_Arr[i] = arr[left + i];

    for (j = 0; j < n2; j++)
        Right_Arr[j] = arr[mid + 1 + j];

    /* Merge data from temporary sub array into original array arr[left..right]*/
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(Left_Arr[i].name, Right_Arr[j].name) < 0)
        {
            arr[k] = Left_Arr[i];
            i++;
        }
        else
        {
            arr[k] = Right_Arr[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining member of Left_Arr[], if there are any */
    while (i < n1)
    {
        arr[k] = Left_Arr[i];
        i++;
        k++;
    }

    /* Copy the remaining member of Right_Arr[], if there are any */
    while (j < n2)
    {
        arr[k] = Right_Arr[j];
        j++;
        k++;
    }
}

void print_array(void)
{
    for (int i = 0; i < total; i++)
    {
        printf("%s %s %s\n", book[i].name, book[i].phone, book[i].email);
    }
}