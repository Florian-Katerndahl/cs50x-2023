#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    if (strlen(*(argv + 1)) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int hist[26] = {0};
    int c;
    for (size_t i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./caeser key\n");
            return 1;
        }
        hist[(int) tolower(argv[1][i]) - 'a']++;
    }
    for (size_t i = 0; i < 26; i++)
    {
        if (hist[i] != 1)
        {
            printf("Usage: ./caeser key\n");
            return 1;
        }
    }

    char *plain;
    do
    {
        plain = get_string("plaintext:  ");
    }
    while (plain == NULL);

    printf("ciphertext: ");
    size_t length = strlen(plain);
    int norm, islowerc;
    for (size_t i = 0; i < length; i++)
    {
        if (isalpha(plain[i]))
        {
            islowerc = islower(plain[i]);
            norm = islowerc ? 97 : 65;
            c = ((plain[i] % norm) % 26)[argv[1]];
            c = islowerc ? tolower(c) : toupper(c);
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
