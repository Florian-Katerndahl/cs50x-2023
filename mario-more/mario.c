#include <cs50.h>
#include <stdio.h>

void print_left_stairs(int size);
void print_right_stairs(int size);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

}