#include <cs50.h>
#include <stdio.h>

void print_spaces(int size);
void print_hashes(int size);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }

}

void print_spaces(int total_height, int row)
{
    for (int j = 0; j < total_height - row - 1; j++)
    {
        printf(" ");
    }
}