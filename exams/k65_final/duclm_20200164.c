#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int coef;
    int exp;
} Elementtype;

typedef struct Node
{
    Elementtype term;
    struct Node *next;
} Node;

typedef struct Node *List;

List lists[5]; // lists[0] is not needed

void initLists(void);
Node *makeNode(int coef, int exp);
Node *findNode(List l, int exp);
List removeNode(List l, int exp);
List insertNode(List l, Elementtype data);
void displayNode(Node *n);
void displayList(List l);
void splitList(List l, List *l1, List *l2);
List mergeLists(List l1, List l2);
void mergeSort(List *l);
void resetList(List *l);
List addLists(void);
List multiplyLists(void);
int getSpace(List l);
void resetAll(void);

int main(void)
{
    int id;
    Elementtype data;
    char command[256];
    initLists();

    while (1)
    {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0)
        {
            scanf("%d%d%d", &id, &data.coef, &data.exp);
            lists[id] = insertNode(lists[id], data);
        }
        else if (strcmp(command, "display") == 0)
        {
            scanf("%d", &id);
            displayList(lists[id]);
        }
        else if (strcmp(command, "sort") == 0)
        {
            scanf("%d", &id);
            mergeSort(&lists[id]);
            displayList(lists[id]);
        }
        else if (strcmp(command, "add") == 0)
        {
            addLists();
            mergeSort(&lists[3]);
            displayList(lists[3]);
        }
        else if (strcmp(command, "multiply") == 0)
        {
            multiplyLists();
            mergeSort(&lists[4]);
            displayList(lists[4]);
        }
        else if (strcmp(command, "space") == 0)
        {
            scanf("%d", &id);
            printf("%d\n", getSpace(lists[id]));
        }
        else if (strcmp(command, "***") == 0)
        {
            resetAll();
            return 0;
        }
        else
        {
            resetAll();
            return 1;
        }
    }
}

void initLists(void)
{
    lists[0] = NULL; // lists[0] is not needed
    lists[1] = NULL;
    lists[2] = NULL;
    lists[3] = NULL;
    lists[4] = NULL;
}

Node *makeNode(int coef, int exp)
{
    Node *n = malloc(sizeof(Node));
    (n->term).coef = coef;
    (n->term).exp = exp;
    n->next = NULL;
    return n;
}

Node *findNode(List l, int exp)
{
    Node *n = l;
    while (n != NULL)
    {
        if ((n->term).exp == exp)
            return n;
        n = n->next;
    }
    return NULL;
}

List removeNode(List l, int exp)
{
    Node *curr = l;
    Node *prev = NULL;

    // If the 1st node needs to be deleted
    if (curr != NULL && (curr->term).exp == exp)
    {
        l = curr->next;
        free(curr);
        return l;
    }

    // If not, keep searching for it
    while (curr != NULL && (curr->term).exp != exp)
    {
        prev = curr;
        curr = curr->next;
    }

    // Only update the list if the node is found
    if (curr != NULL)
    {
        prev->next = curr->next;
        free(curr);
    }

    return l;
}

List insertNode(List l, Elementtype data)
{
    Node *found = findNode(l, data.exp);
    if (found != NULL)
    {
        (found->term).coef += data.coef;
        if ((found->term).coef == 0)
            l = removeNode(l, data.exp);
    }
    else
    {
        if (data.coef == 0)
            return l;
        Node *n = makeNode(data.coef, data.exp);
        n->next = l;
        l = n;
    }
    return l;
}

void displayNode(Node *n)
{
    printf("%d %d ", (n->term).coef, (n->term).exp);
}

void displayList(List l)
{
    for (Node *p = l; p != NULL; p = p->next)
    {
        displayNode(p);
    }
    if (l != NULL)
        printf("\n");
    else
        printf(" \n");
}

void splitList(List l, List *l1, List *l2)
{
    Node *slow;
    Node *fast;
    slow = l;
    fast = l->next;

    // Advance 'fast' two nodes and 'slow' one node
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Now 'slow' is before the midpoint of the list
    *l1 = l;
    *l2 = slow->next;
    slow->next = NULL;
}

List mergeLists(List l1, List l2)
{
    Node *dummyHead = makeNode(0, 0);
    Node *ptr = dummyHead;
    while ((l1 != NULL) && (l2 != NULL))
    {
        if ((l1->term).exp > (l2->term).exp)
        {
            ptr->next = l1;
            l1 = l1->next;
        }
        else
        {
            ptr->next = l2;
            l2 = l2->next;
        }
        ptr = ptr->next;
    }
    if (l1 != NULL)
        ptr->next = l1;
    else
        ptr->next = l2;

    Node *result = dummyHead->next;
    free(dummyHead);
    return result;
}

void mergeSort(List *l)
{
    List head = *l;

    // Stop if the length is 0 or 1
    if ((head == NULL) || (head->next == NULL))
        return;

    // Split the list into two sublists
    List l1;
    List l2;
    splitList(head, &l1, &l2);

    // Recursively sort each sublist
    mergeSort(&l1);
    mergeSort(&l2);

    // Merge the two sorted sublists
    *l = mergeLists(l1, l2);
}

void resetList(List *l)
{
    Node *p = *l;
    Node *tmp = NULL;
    while (p != NULL)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    *l = NULL;
}

List addLists(void)
{
    resetList(&lists[3]);
    for (Node *p = lists[1]; p != NULL; p = p->next)
    {
        lists[3] = insertNode(lists[3], p->term);
    }
    for (Node *p = lists[2]; p != NULL; p = p->next)
    {
        lists[3] = insertNode(lists[3], p->term);
    }
}

List multiplyLists(void)
{
    resetList(&lists[4]);
    Elementtype tmp;
    for (Node *p1 = lists[1]; p1 != NULL; p1 = p1->next)
    {
        for (Node *p2 = lists[2]; p2 != NULL; p2 = p2->next)
        {
            tmp.coef = (p1->term).coef * (p2->term).coef;
            tmp.exp = (p1->term).exp + (p2->term).exp;
            lists[4] = insertNode(lists[4], tmp);
        }
    }
}

int getSpace(List l)
{
    int cnt = 0;
    for (Node *p = l; p != NULL; p = p->next)
    {
        cnt++;
    }
    return 10 * cnt;
}

void resetAll(void)
{
    for (int i = 0; i < 4; i++)
    {
        resetList(&lists[i]);
    }
}