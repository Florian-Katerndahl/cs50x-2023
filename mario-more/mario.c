#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_spaces(int total_height, int row);
void print_hashes(int row);

int main(void)
{


    for (int i = 0; i < get_height; i++)
    {
        print_spaces(height, i);
        print_hashes(i);
        printf(" ");
        print_hashes(i)

        printf("\n");
    }

}

int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

void print_spaces(int total_height, int row)
{
    for (int j = 0; j < total_height - row - 1; j++)
    {
        printf(" ");
    }
}

void print_hashes(int row)
{
    for (int j = 0; j < row + 1; j++)
        {
            printf("#");
        }
}