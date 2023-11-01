#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    char **endptr = &(argv + 1);
    int shift = strtol(argv + 1, endptr, 10)
    return 0;
}
