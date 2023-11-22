#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert_iter(string input);
int convert_rec(string input);

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
    printf("%i\n", convert_rec(input));
}

int convert_iter(string input)
{
    size_t len = strlen(input);
    int result = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        result += (input[i] - '0') * (int) powl(10, len - 1 - i);
    }

    return result;
}

int convert_rec(string input)
{
    size_t len = strlen(input);
    if (len == 0)
        return 0;

    int result = (input[len - 1] - '0');
    input[len - 1] = '\0';

    return result + 10 * convert_rec(input);
}
