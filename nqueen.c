#include <stdbool.h>
#include <stdio.h>

void printArray(int board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j])
                printf("X ");
            else
                printf("O ");
        }
        printf("\n");
    }
}

bool isSafe(int board[4][4], int row, int col)
{
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (i = row, j = col; j >= 0 && i < 4; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solve(int board[4][4], int col)
{
    if (col >= 4)
        return true;

    for (int i = 0; i < 4; i++)
    {

        if (isSafe(board, i, col))
        {

            board[i][col] = 1;

            if (solve(board, col + 1))
                return true;

            board[i][col] = 0;
        }
    }

    return false;
}

bool nQueen()
{
    int board[4][4] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};

    if (solve(board, 0) == false)
    {
        printf("Solution does not exist");
        return false;
    }

    printArray(board);
    return true;
}

int main()
{
    nQueen();
    return 0;
}