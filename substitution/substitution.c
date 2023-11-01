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
            // remember: dont program if you can barely look ahead
            norm = islower(plain[i]) ? 97 : 65;
            // holy shit, that took a long time: started with index table in mind and thus a mod 25
            c = tolower(((plain[i] % norm) % 25)[*(argv + 1)]);
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
