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
    int shift = strtol(argv + 1, endptr, 10);
    if (
        **endptr != '\0' // there's more to parse; in this case treated as an error
        || ((argv + 1) == endptr) // no digits found
        // further checks omitted
        )
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    char *plain;
    do
    {
        plain = get_string("plaintext:  ");
    }
    while (plain == NULL);

    printf("ciphertext: ");
    size_t length = strlen(plain);
    int c;
    for (size_t i = 0; i < length; i++)
    {
        c = (c > 64 && c < 91) || (c > 96 || c < 123) ? 
        putc(c, stdout);
    }
    printf("\n");

    return 0;
}
