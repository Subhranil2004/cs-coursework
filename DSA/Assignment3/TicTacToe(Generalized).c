// Generalized Tic-tac-toe game (NxN). User has to check N consecutive squares to win.
#define N 3 // Generates an NxN board
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // use time.h header file to use time

char check(char mat[N][N]);
void choose(char mat[N][N]);
void display(char mat[N][N]);
int main()
{
    int row, col;
    char mat[N][N];
    char win = 'n';

    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
            mat[row][col] = ' ';
    }
    while (win == 'n')
    {
        do
        {
            printf("Your turn :\nEnter row index : ");
            scanf("%d", &row);
            while (row < 0 || row >= N)
            {
                printf("Enter a valid row index : ");
                scanf("%d", &row);
            }
            printf("Enter column index : ");
            scanf("%d", &col);
            while (col < 0 || col >= N)
            {
                printf("Enter a valid column index : ");
                scanf("%d", &col);
            }
        } while (mat[row][col] != ' ' && printf("That square is already filled. Enter again.\n"));

        mat[row][col] = 'O';
        display(mat);
        win = check(mat);
        if (win != 'n')
            break;
        printf("Computer's turn :\n");
        choose(mat);
        display(mat);
        win = check(mat);
    }

    if (win == 'y')
        printf("\nYou Win!");
    else if (win == 'c')
        printf("\nComputer Wins!");
    else
        printf("\nMatch Draw!");
    return 0;
}

void choose(char mat[N][N])
{
    int row, col;
    time_t t1;                 // declare time variable
    srand((unsigned)time(&t1)); // setting a random seed based on current time.
    do
    {
        row = rand() % N;
        col = rand() % N;
    } while (mat[row][col] != ' ');
    mat[row][col] = 'X';
}

char check(char mat[N][N])
{
    // n -> nobody has won, y -> user won, c -> computer won, d -> match draw
    int i, j;
    char ch;

    // Checking for rows
    for (i = 0; i < N; i++)
    {
        ch = mat[i][0];
        for (j = 1; j < N; j++)
        {
            if (mat[i][j] == ' ' || mat[i][j] != ch)
                break;
        }
        if (j == N)
        {
            if (ch == 'O')
                return 'y';
            else if (ch == 'X')
                return 'c';
        }
    }
    // Checking for columns
    for (i = 0; i < N; i++)
    {
        ch = mat[0][i];
        for (j = 0; j < N; j++)
        {
            if (mat[j][i] == ' ' || mat[j][i] != ch)
                break;
        }
        if (j == N)
        {
            if (ch == 'O')
                return 'y';
            else if (ch == 'X')
                return 'c';
        }
    }

    // Checking for both diagonals
    ch = mat[0][0];
    for (i = 1; i < N; i++)
    {

        if (mat[i][i] == ' ' || mat[i][i] != ch)
            break;
    }
    if (i == N)
    {
        if (ch == 'O')
            return 'y';
        else if (ch == 'X')
            return 'c';
    }

    ch = mat[0][N - 1];
    for (i = 1; i < N; i++)
    {
        if (mat[i][N - i - 1] == ' ' || mat[i][N - i - 1] != ch)
            break;
    }
    if (i == N)
    {
        if (ch == 'O')
            return 'y';
        else if (ch == 'X')
            return 'c';
    }

    // Checking for draw
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            ch = mat[i][j];
            if (ch == ' ')
                return 'n';
        }
    }
    return 'd';
}

void display(char mat[N][N])
{
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("\t");
        for (j = 0; j < N; j++)
            printf(" %c |", mat[i][j]);
        printf("\b \n");
        if (i != N - 1)
        {
            printf("\t___");
            for (j = 0; j < N - 1; j++)
                printf("|___");
            printf("\n");
        }
        else
        {
            printf("\t   ");
            for (j = 0; j < N - 1; j++)
                printf("|   ");
            printf("\n");
        }
    }
}
