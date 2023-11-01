#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char index_table[] = "abcdefghijklmnopqrstuvwxyzABDCDEFGHIJKLMNOPQRSTUVXYZ";

int main(int argc, char **argv)
{
    char *start, *end;
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    start = *(argv + 1);
    int shift = strtol(start, &end, 10);
    if (
        *end != '\0' // there's more to parse; in this case treated as an error
        //|| (*(argv + 1) == *endptr) // no digits found
        // further checks omitted
        )
    {
        printf("Usage123: ./caeser key\n");
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
    int c, norm;
    for (size_t i = 0; i < length; i++)
    {
        if ((plain[i] > 64 && plain[i] < 91) || (plain[i] > 96 && plain[i] < 123))
        {
            norm = islower(c) ? 97 : 65;
            c = (plain[i] % norm + shift) % 25 + norm;
            //printf("Normed conversion: %c\n", c + norm);
        }
        else
        {
            c = plain[i];
        }
        putc(c, stdout);
    }
    printf("\n");

    return 0;
}
