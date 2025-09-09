#include <stdio.h>
#include <stdbool.h>

#define MAX(a, b) a > b ? a : b;
#define MIN(a, b) a < b ? a : b;

void print_map(char board[3][3]);
int check_rows(char board[3][3]);
int check_cols(char board[3][3]);
int check_diagonals(char board[3][3]);
int check_game(char board[3][3]);
int minimax(char board[3][3], bool isMaximizing);
bool is_move_left(char board[3][3]);
int robot_choice(char board[3][3]);

int main()
{
    bool isRunning = true;
    char board[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }

    print_map(board);
    while (isRunning)
    {
        printf("\n Choose the cell you want to fill :");
        int num;
        scanf("%d", &num);
        num--;
        int row = num / 3;
        int col = num % 3;
        if (board[row][col] != '-')
        {
            printf("\n This cell has been already filled \n");
            continue;
        }
        board[row][col] = 'x';

        int move = robot_choice(board);
        int r = move / 3;
        int c = move % 3;
        board[r][c] = 'o';
        print_map(board);

        int check_g = check_game(board);
        if (check_g == 1)
        {
            printf("\n PLAYER");
            break;
        }
        else if (check_g == -1)
        {
            printf("\n ROBOT");
            break;
        }
        if (!is_move_left(board))
        {
            printf("\n DRAW");
            break;
        }
    }

    return 0;
}

int robot_choice(char board[3][3])
{
    int best = 100;
    int move = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                board[i][j] = 'o';
                int score = minimax(board, true);
                board[i][j] = '-';
                if (score < best)
                {
                    best = score;
                    move = 3 * i + j;
                }
            }
        }
    }
    return move;
}

bool is_move_left(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
                return true;
        }
    }
    return false;
}

int minimax(char board[3][3], bool isMaximizing)
{
    int score = check_game(board);
    if (score != 0)
    {
        return score;
    }
    if (!is_move_left(board))
    {
        return 0;
    }
    if (isMaximizing)
    {
        int best = -100;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '-')
                {
                    board[i][j] = 'x';
                    best = MAX(best, minimax(board, false));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 100;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '-')
                {
                    board[i][j] = 'o';
                    best = MIN(best, minimax(board, true));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}

int check_game(char board[3][3])
{
    int rows = check_rows(board);
    if (rows)
    {
        return rows;
    }
    int cols = check_cols(board);
    if (cols)
    {
        return cols;
    }
    int d = check_diagonals(board);
    if (d)
    {
        return d;
    }
    return 0;
}

int check_rows(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == 'x' && board[i][1] == 'x' && board[i][2] == 'x')
        {
            return 1;
        }
        else if (board[i][0] == 'o' && board[i][1] == 'o' && board[i][2] == 'o')
        {
            return -1;
        }
    }
    return 0;
}

int check_cols(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == 'x' && board[1][i] == 'x' && board[2][i] == 'x')
        {
            return 1;
        }
        else if (board[0][i] == 'o' && board[1][i] == 'o' && board[2][i] == 'o')
        {
            return -1;
        }
    }
    return 0;

}

int check_diagonals(char board[3][3])
{
    if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x')
    {
        return 1;
    }
    if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o')
    {
        return -1;
    }
    if (board[2][0] == 'x' && board[1][1] == 'x' && board[0][2] == 'x')
    {
        return 1;
    }
    if (board[2][0] == 'o' && board[1][1] == 'o' && board[0][2] == 'o')
    {
        return -1;
    }
    return 0;
}

void print_map(char board[3][3])
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", board[i][j]);
            if (j != 2)
            {
                printf(" | ");
            }
        }
        if (i != 2)
            printf("\n-----------\n");
    }
    printf("\n");
}