#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** ---------------------
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** ---------------------
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 ** 0 0 0 | 0 0 0 | 0 0 0
 */

static long tot_count;

void    ft_bzero(const char *str, size_t size)
{
    size_t          i;
    unsigned char   *ptr;

    i = 0;
    ptr = (unsigned char *)str;
    while (i < size)
    {
        ptr[i] = 0;
        i++;
    }
}

void    print_puzzle(int **tab)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 9)
    {
        while (j < 9)
        {
            printf("%d ", tab[i][j]);
            j++;
        }
        printf("\n");
        i++;
        j = 0;
    }
}

int     **new_2dint(size_t size)
{
    int     **ptr;
    size_t  i;
    size_t  j;

    ptr = NULL;
    i = 0;
    j = 0;
    if (size)
    {
        ptr = (int **)malloc(sizeof(int *) * (size + 1));
        while (i < size)
        {
            ptr[i] = (int *)malloc(sizeof(int) * size);
            while (j < size)
            {
                ptr[i][j] = 0;
                j++;
            }
            j = i;
            i++;
        }
    }
    return (ptr);
}

int     check_area(int **tab, int row, int col, int against)
{
    int count;

    count = 0;
    if (row <= 2)
        row = 0;
    else if (row > 2 && row < 6)
        row = 3;
    else if (row > 5)
        row = 6;
    if (col <= 2)
        col = 0;
    else if (col > 2 && col < 6)
        col = 3;
    else if (col > 5)
        col = 6;
    if (tab[(row + 0)][(col + 0)] == against)
        count++;
    if (tab[(row + 0)][(col + 1)] == against)
        count++;
    if (tab[(row + 0)][(col + 2)] == against)
        count++;
    if (tab[(row + 1)][(col + 0)] == against)
        count++;
    if (tab[(row + 1)][(col + 1)] == against)
        count++;
    if (tab[(row + 1)][(col + 2)] == against)
        count++;
    if (tab[(row + 2)][(col + 0)] == against)
        count++;
    if (tab[(row + 2)][(col + 1)] == against)
        count++;
    if (tab[(row + 2)][(col + 2)] == against)
        count++;
    if (count == 1)
        return (1);
    return (0);
}

int     check_vertical(int **tab, int col, int against)
{
    int count;

    count = 0;
    if (tab[0][col] == against)
        count++;
    if (tab[1][col] == against)
        count++;
    if (tab[2][col] == against)
        count++;
    if (tab[3][col] == against)
        count++;
    if (tab[4][col] == against)
        count++;
    if (tab[5][col] == against)
        count++;
    if (tab[6][col] == against)
        count++;
    if (tab[7][col] == against)
        count++;
    if (tab[8][col] == against)
        count++;
    if (count == 1)
        return (1);
    return (0);
}

int     check_horizonal(int **tab, int row, int against)
{
    int count;

    count = 0;
    if (tab[row][0] == against)
        count++;
    if (tab[row][1] == against)
        count++;
    if (tab[row][2] == against)
        count++;
    if (tab[row][3] == against)
        count++;
    if (tab[row][4] == against)
        count++;
    if (tab[row][5] == against)
        count++;
    if (tab[row][6] == against)
        count++;
    if (tab[row][7] == against)
        count++;
    if (tab[row][8] == against)
        count++;
    if (count == 1)
        return (1);
    return (0);
}

int     is_safe(int **orig, int row, int col)
{
    if (orig[row][col] == 0)
    {
        return (1);
    }
    return (0);
}

int     check_position(int **tab, int row, int col)
{
    if (check_area(tab, row, col, tab[row][col]))
    {
        if (check_horizonal(tab, row, tab[row][col]))
        {
            if (check_vertical(tab, col, tab[row][col]))
            {
                return (1);
            }
        }
    }
    return (0);
}

int     increment_forward(int *row, int *col)
{
    if (col[0] < 8)
    {
        col[0]++;
    }
    else if (row[0] < 8)
    {
        col[0] = 0;
        row[0]++;
    }
    else if (row[0] == 8 && col[0] == 8)
    {
        printf("solved\n");
        return (0);
    }
    return (1);
}

int     increment_reverse(int *row, int *col)
{
    if (col[0] > 0)
    {
        col[0]--;
    }
    else if (row[0] > 0)
    {
        col[0] = 8;
        row[0]--;
    }
    else if (row[0] == 0 && col[0] == 0)
    {
        printf("Error: return to begining\n");
        return (0);
    }
    return (1);
}

// 1) check if safe
// 2) if safe and tab[row][col] less than 9 then increment by 1
//      a) check if number is valid
//          a1) if valid increase position and goto 1)
//          a2) if not goto 1)
// 3) if not safe increase position *until* safe and goto 1)
// 4) if safe but equal to 9 reset to 0 and decrease position *until* safe and goto 1)
//
// Logic returns only once attempt to increment goes above row(8) col(8) = (solution found) 
// or below row(0) col(0) = (No solutions to puzzle).
int     solve_puzzle(int **orig, int **tab, int row, int col)
{
    int a;
    while (1)
    {
        (++tot_count);
        if (tot_count % 10000000 == 0)
        {
            printf("\n");
            print_puzzle(tab);
        }
        if ((a = is_safe(orig, row, col)) && tab[row][col] < 9)
        {
            tab[row][col]++;
            if (check_position(tab, row, col))
            {
                if (increment_forward(&row, &col) == 0)
                {
                    return (0);
                }
            }

        }
        else if (a == 0)
        {
            while ((a = is_safe(orig, row, col)) == 0)
            {
                if (increment_forward(&row, &col) == 0)
                {
                    return (0);
                }
            }
        }
        else if (a && tab[row][col] == 9)
        {
            tab[row][col] = 0;
            increment_reverse(&row, &col);
            while ((a = is_safe(orig, row, col)) == 0)
            {
                if (increment_reverse(&row, &col) == 0)
                {
                    return (0);
                }
            }
        }
    }
}

void    strtointptr(int ***tab, char *line, int i)
{
    int j = 0;
    while (line[j] != '\0')
    {
        if ((line[j]) == '.')
            tab[0][i][j] = 0;
        else
            tab[0][i][j] = (line[j] - 48);
        j++;
    }
}

int  get_puzzle(int ***tab, char *file)
{
    int     i;
    int     r;
    int     fd;
    int     total_r;
    char    buf[11];

    i = 0;
    r = 0;
    total_r = 0;
    fd = open(file, O_RDONLY, 0);
    if (fd < 0)
    {
        perror("Error: Failed to open file.\n");
        return (0);
    }
    while ((r = read(fd, buf, 11)) > 0)
    {
        if ((buf[r - 1]) == '\n')
            buf[r - 1] = '\0';
        else
        {
            printf("Invalid sudoku puzzle.\n");
            exit(1);
        }
        strtointptr(tab, buf, i);
        i++;
        ft_bzero(buf, 11);
        total_r += r;
        r = 0;
    }
    return (1);
}

int main(int ac, char **av)
{
    int     **tab;
    int     **state;

    tab = new_2dint(9);
    state = new_2dint(9);
    if (ac == 2)
    {
        if (get_puzzle(&tab, av[1]))
        {
            get_puzzle(&state, av[1]);
            printf("Original:\n");
            print_puzzle(tab);
            solve_puzzle(state, tab, 0, 0);
            printf("\n");
            if (tot_count <= 200000)
            {
                printf("EASY PUZZLE\n");
            }
            else if (tot_count > 200000 && tot_count <= 400000)
            {
                printf("MEDIUM PUZZLE\n");
            }
            else
            {
                printf("HARD PUZZLE\n");
            }
            printf("%d\n", tot_count);
            print_puzzle(tab);
        }
    }
    return (0);
}
