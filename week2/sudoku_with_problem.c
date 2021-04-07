#include <stdio.h>

typedef struct
{
    int r;
    int c;
}
position;

int x[9][9] =
{
    {5, 3, 0,   0, 7, 0,   0, 0, 0},
    {6, 0, 0,   1, 9, 5,   0, 0, 0},
    {0, 9, 8,   0, 0, 0,   0, 6, 0},

    {8, 0, 0,   0, 6, 0,   0, 0, 3},
    {4, 0, 0,   8, 0, 3,   0, 0, 1},
    {7, 0, 0,   0, 2, 0,   0, 0, 6},

    {0, 6, 0,   0, 0, 0,   2, 8, 0},
    {0, 0, 0,   4, 1, 9,   0, 0, 5},
    {0, 0, 0,   0, 8, 0,   0, 7, 9}
};

position find_empty(void)
{
    position empty_cell;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (x[i][j] == 0)
            {
                empty_cell.r = i;
                empty_cell.c = j;
                return empty_cell;
            }
        }
    }

    // No more empty cells
    empty_cell.r = -1;
    empty_cell.c = -1;
    return empty_cell;
}

void solution(void)
{
    for (int i = 0; i < 9; i++)
    {
        if (i == 0 || i == 3 || i == 6)
            printf("+-------+-------+-------+\n");
        for (int j = 0; j < 9; j++)
        {
            if (j == 0 || j == 3 || j == 6)
                printf("| %d ", x[i][j]);
            else
                printf("%d ", x[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n\n");
}

int check(int v, int r, int c)
{
    for (int i = 0; i < 9; i++)
    {
        if (x[i][c] == v)
            return 0;
    }

    for (int j = 0; j < 9; j++)
    {
        if (x[r][j] == v)
            return 0;
    }

    int I = r / 3;
    int J = c / 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (x[i + 3 * I][j + 3 * J] == v)
                return 0;
        }
    }

    return 1;
}

void Try(int r, int c)
{
    for (int v = 1; v <= 9; v++)
    {
        if (check(v, r, c))
        {
            x[r][c] = v;

            // Find the next empty cell
            position empty_cell = find_empty();

            // No more empty cells (-1) means the board have been solved
            if (empty_cell.r == -1 && empty_cell.c == -1)
                solution();
            else
                Try(empty_cell.r, empty_cell.c);

            // Reset the cell
            x[r][c] = 0;
        }
    }
}

int main(void)
{
    // Find the first empty cell
    position empty_cell = find_empty();
    Try(empty_cell.r, empty_cell.c);
    return 0;
}
