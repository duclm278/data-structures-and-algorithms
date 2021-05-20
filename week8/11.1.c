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
void quick_sort(int left, int right);
void print_array(void);

int main(void)
{

    int option;
    while (1)
    {
        // Print out menu
        printf("+--------------------------------------+\n");
        printf("| 1. Load file                         |\n");
        printf("| 2. Quick sort                        |\n");
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
            quick_sort(0, total - 1);
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

void quick_sort(int left, int right)
{
    char *pivot;
    int i, j;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = strdup(book[left].name);
        do
        {
            do
                i++;
            while (i <= right && strcmp(book[i].name, pivot) < 0);
            do
                j--;
            while (j >= left && strcmp(book[j].name, pivot) > 0);
            if (i < j)
                swap(&book[i], &book[j]);
        } while (i < j);
        swap(&book[left], &book[j]);
        quick_sort(left, j - 1);
        quick_sort(j + 1, right);
    }
}

void print_array(void)
{
    for (int i = 0; i < total; i++)
    {
        printf("%s %s %s\n", book[i].name, book[i].phone, book[i].email);
    }
}