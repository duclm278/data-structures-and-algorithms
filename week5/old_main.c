#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

char s[100];
Tree t;

void func(char *l);
void freeTree(Tree r);
void load(void);
void printTree(Tree r);
void processFind(void);
void processFindChildren(void);
void processHeight(void);
void processCount(void);
void processAddChild(void);
void processStore(void);

int main()
{
    while (1)
    {
        char cmd[100];
        printf("Enter command: ");
        scanf("%s", cmd);
        if (strcmp(cmd, "Quit") == 0)
            break;
        else if (strcmp(cmd, "Load") == 0)
            load();
        else if (strcmp(cmd, "Print") == 0)
            printTree(t);
        else if (strcmp(cmd, "Find") == 0)
            processFind();
        else if (strcmp(cmd, "FindChildren") == 0)
            processFindChildren();
        else if (strcmp(cmd, "Height") == 0)
            processHeight();
        else if (strcmp(cmd, "Count") == 0)
            processCount();
        else if (strcmp(cmd, "AddChild") == 0)
            processAddChild();
        else if (strcmp(cmd, "Store") == 0)
            processStore();
    }
    freeTree(t);
    return 0;
}

void func(char *l)
{
    strcat(s, l);
    strcat(s, ", ");
}

void freeTree(Tree r)
{
    if (r == NULL)
        return;
    Tree p = r->leftMostChild;
    while (p != NULL)
    {
        Tree sp = p->rightSibling;
        freeTree(p);
        p = sp;
    }
    printf("Free node %s\n", r->label);
    free(r);
    r = NULL;
}

void load(void)
{
    char file_name[100];
    scanf("%s", file_name);
    FILE *f = fopen(file_name, "r");

    // Root
    char current_label[100];
    if (fscanf(f, "%s", current_label) != 1)
        return;
    t = createRoot(current_label);

    // Children
    Tree tmp;
    int new_line = 0;
    Tree current_parent = t;
    while (fscanf(f, "%s", current_label) == 1)
    {
        if (strcmp(current_label, "$$") == 0)
            return;
        else if (current_label[0] == '$')
            new_line = 1;
        else if (new_line == 1)
        {
            current_parent = find(t, current_label);
            new_line = 0;
        }
        else
            tmp = addChild(current_parent, current_label);
    }

    fclose(f);
}

void printTree(Tree r)
{
    if (r == NULL)
        return;
    printf("%s: ", r->label);
    Tree p = r->leftMostChild;
    while (p != NULL)
    {
        printf("%s ", p->label);
        p = p->rightSibling;
    }
    printf("\n");
    p = r->leftMostChild;
    while (p != NULL)
    {
        printTree(p);
        p = p->rightSibling;
    }
}

void processFind(void)
{
    char name[256];
    scanf("%s", name);
    Tree p = find(t, name);
    if (p == NULL)
        printf("Not Found %s\n", name);
    else
        printf("Found %s\n", name);
}

void processFindChildren(void)
{
    char label[100];
    scanf("%s", label);
    Tree p = find(t, label);
    if (p == NULL)
        printf("Not Found %s\n", label);
    else
    {
        printf("Found %s with children: ", label);
        Tree q = p->leftMostChild;
        while (q != NULL)
        {
            printf("%s ", q->label);
            q = q->rightSibling;
        }
    }
    printf("\n");
}

void processHeight(void)
{
    char name[100];
    scanf("%s", name);
    Tree p = find(t, name);
    if (p == NULL)
        printf("Not Found %s\n", name);
    else
    {
        printf("Found %s having height = %d\n", name, height(p));
    }
}

void processCount(void)
{
    printf("Number of members is %d\n", size(t));
}

void processAddChild(void) {}

void processStore(void) {}