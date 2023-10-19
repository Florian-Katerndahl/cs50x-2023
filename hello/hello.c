#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name;
    do
    {
        name = get_string("What's your name? ");
    }
    while (name != NULL);

    printf("hello, %s\n", name);
}