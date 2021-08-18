#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 256
#define MAX 100000

typedef struct Node
{
    char name[256];
    char email[256];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *root;

Node *makeNode(char *name, char *email)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->email, email);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *name, char *email)
{
    if (r == NULL)
        return makeNode(name, email);
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        printf("Student %s exists, do not insert\n", name);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, name, email);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, email);
        return r;
    }
}

Node *find(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, name);
    return find(r->leftChild, name);
}

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL)
        return lmin;
    return r;
}

Node *removeStudent(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->leftChild = removeStudent(r->leftChild, name);
    else if (c < 0)
        r->rightChild = removeStudent(r->rightChild, name);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            Node *tmp = findMin(r->rightChild);
            strcpy(r->name, tmp->name);
            strcpy(r->email, tmp->email);
            r->rightChild = removeStudent(r->rightChild, tmp->name);
        }
        else
        {
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    root = NULL;
    while (!feof(f))
    {
        char name[256], email[256];
        fscanf(f, "%s%s\n", name, email);
        root = insert(root, name, email);
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s, %s\n", r->name, r->email);
    inOrder(r->rightChild);
}

void inOrderF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
    fprintf(f, "%s %s\n", r->name, r->email);
    inOrderF(r->rightChild, f);
}

void printList()
{
    inOrder(root);
}

void processFind()
{
    char name[256];
    scanf("%s", name);
    Node *result = find(root, name);
    if (result != NULL)
    {
        printf("Found student %s, email %s\n", result->name, result->email);
    }
    else
    {
        printf("Not found student %s\n", name);
    }
}

void processLoad()
{
    char filename[256];
    scanf("%s", filename);
    load(filename);
}

void processStore()
{
    char filename[256];
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    inOrderF(root, f);
    fclose(f);
}

void processInsert()
{
    char name[256], email[256];
    scanf("%s%s", name, email);
    root = insert(root, name, email);
}

void processRemove()
{
    char name[256];
    scanf("%s", name);
    root = removeStudent(root, name);
}

void main()
{
    while (1)
    {
        printf("Enter command: ");
        char cmd[256];
        scanf("%s", cmd);
        if (strcmp(cmd, "Quit") == 0)
            break;
        else if (strcmp(cmd, "Load") == 0)
            processLoad();
        else if (strcmp(cmd, "Print") == 0)
            printList();
        else if (strcmp(cmd, "Find") == 0)
            processFind();
        else if (strcmp(cmd, "Insert") == 0)
            processInsert();
        else if (strcmp(cmd, "Remove") == 0)
            processRemove();
        else if (strcmp(cmd, "Store") == 0)
            processStore();
    }
    freeTree(root);
}