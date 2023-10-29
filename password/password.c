// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool contains_lower = false;
    bool contains_upper = false;
    bool contains_number = false;
    bool contains_symbol = false;
    char *p = password;
    while (*p)
    {
        if (*p > 64 && *p < 91)
            contains_upper = true;
        if (*p > 96 && *p < 123)
            contains_lower = true;
        if (*p > 47 && *p < 58)
            contains_number = true;
        if (*p > 32 && *p < 48)
            contains_symbol = true;
        p++;
    }
    return contains_lower && contains_upper && contains_number && contains_symbol;
}
