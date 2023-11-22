#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert_iter(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert_iter(input));
}

int convert_iter(string input)
{
    size_t len = strlen(input);
    int result = 0, temp;
    for (int i = len - 1; i >= 0; i--)
    {
        temp = (input[i] - '0') * (1 << (len - 1 - i));
        printf("%d\n", temp);
        result += temp;
    }

    return result;
}
