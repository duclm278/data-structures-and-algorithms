#include <stdio.h>
#include <string.h>

#define N 100

int n;
int x[N];
int marks[N];
int cnt = 0; // Count solution(s)

void solution(void)
{
    printf("Solution %d:\n", ++cnt);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < x[i]; j++)
            printf(" . ");
        printf("[x]");
        for (int j = x[i] + 1; j <= n; j++)
            printf(" . ");
        printf("\n");
    }
    printf("\n");
}

int check(int v, int k)
{
    for (int i = 1; i < k; i++)
    {
        if (x[i] == v)
            return 0;
        if (x[i] - i == v - k)
            return 0;
        if (x[i] + i == v + k)
            return 0;
    }
    return 1;
}

void Try(int k)
{
    for (int v = 1; v <= n; v++)
    {
        if (marks[v] == 0 && check(v, k) == 1)
        {
            x[k] = v;
            marks[v] = 1;
            if (k == n)
                solution();
            else
                Try(k + 1);
            marks[v] = 0;
        }
    }
}

int main(void)
{
    scanf("%d", &n);
    memset(marks, 0, sizeof(marks));
    Try(1);
    return 0;
}
